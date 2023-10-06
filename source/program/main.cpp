#include "func_ptrs.hpp"
#include "lib.hpp"
#include <program/xlink.hpp>

// unkXXX == Unknown

// Defines
#define PRINT(...)                                         \
	{                                                      \
		int len = snprintf(buf, sizeof(buf), __VA_ARGS__); \
		svcOutputDebugString(buf, len);                    \
	}

// SLink Offsets -  1.2.1
static constexpr int s_SLinkInstanceOffset = 0x0471a578;
static constexpr int s_RootCallbackOffset = 0x11D8;
static constexpr int s_VtableHookOffset = 0x043C67D8;

// Function Offsets - 1.2.1
static constexpr int s_emitImpl = 0x000afd244;
static constexpr int s_searchAssetCallTableByNameOffset = 0x00afd150;
static constexpr int s_searchAssetCallTableByNameInlinedOne = 0x009fff60;

// Unused Offsets
// static constexpr int s_searchAssetCallTableByNameInlinedTwo = 0x00a3aa78;
// static constexpr int s_searchAssetCallTableByNameInlinedThree = 0x00f85148;
// static constexpr int s_searchAssetCallTableByNameInlinedThreeLabel = 0x00f852c4;
// static constexpr int s_searchAssetCallTableByNameInlinedFour = 0x02295f0c;

// Global Variables
static xlink2::ResAssetCallTable newResAssetCallTable {};
static xlink2::ResAssetCallTable newResAssetCallTableInlined {};
char requiredPrefix[] = "CSM_";
char presetSLinkKey[] = "button_decide";
char senderTag[] = "CSM:";
uintptr_t presetSLinkUser;

// SLink Helper Functions

// Get pointer to the callback object pointer in the SLink system.
static xlink2::IEventCallbackSLink** GetRootEventCallbackPtr()
{
	return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset, s_RootCallbackOffset>();
}

// Get pointer to a function pointer within a vtable. This is in TOTK's sound manager and it registers the SLink root callback.
using HookedFuncType = void (*)(uintptr_t, uintptr_t);
static HookedFuncType* GetHookFuncPtr()
{
	return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset>();
}

// Helper functions

// Combine 2 char* to a single char*
static char* CombineChars(char* char1, char* char2)
{
	// Prepare variables
	size_t len1 = strlen(char1);
	size_t len2 = strlen(char2);
	size_t combinedLength = len1 + len2;

	// Allocate memory for the new combined string
	char* newKeyname = new char[combinedLength + 1];

	// Copy the custom prefix into the new buffer
	strcpy(newKeyname, char1);

	// Concatenate the existing string to the end of the custom prefix
	strcat(newKeyname, char2);

	return newKeyname;
}

// Custom implementation of the callback object, which passes through to the original.
struct CustomEventCallbackSLink : xlink2::IEventCallbackSLink
{
	xlink2::IEventCallbackSLink* m_Impl = nullptr;

#define BASE(...)                   \
	if (m_Impl != nullptr)          \
	{                               \
		return m_Impl->__VA_ARGS__; \
	}

	virtual ~CustomEventCallbackSLink()
	{
		if (m_Impl != nullptr)
		{
			m_Impl->~IEventCallbackSLink();
		}
		m_Impl = nullptr;
	}

	virtual int eventActivating(EventArg const& arg)
	{
		BASE(eventActivating(arg));
		return 0;
	}

	virtual void eventActivated(EventArg const& arg)
	{
		BASE(eventActivated(arg));
	}

	virtual bool soundPrePlay(EventArg const& arg)
	{
		BASE(soundPrePlay(arg));
		return false;
	}

	virtual void unk1(EventArg const& arg)
	{
		BASE(unk1(arg));
	}

	virtual void soundPlayed(EventArg const& arg)
	{
		BASE(soundPlayed(arg));
	}

	virtual void soundCalced(EventArg const& arg)
	{
		BASE(soundCalced(arg));
	}

	virtual int replaceAssetInfo(aal::AssetInfo* assetInfo, ReplaceAssetInfoArg const& arg)
	{
		char buf[500];

		// If CSM_ is in key name, change the asset name
		if (strstr(arg.mResAssetCallTable->mKeyName, requiredPrefix))
		{
			PRINT("CSM: replaceAssetInfo | CSM SLink Name: %s", arg.mResAssetCallTable->mKeyName);
			strcpy(arg.mAssetName->mPtr, arg.mResAssetCallTable->mKeyName);
		}

		BASE(replaceAssetInfo(assetInfo, arg));
		return 0;
	}

	virtual int unk2(EventArg const& arg)
	{
		BASE(unk2(arg));
		return 0;
	}

	virtual void unk3(EventArg const& arg)
	{
		BASE(unk3(arg));
	}

	virtual void unk4(EventArg const& arg)
	{
		BASE(unk4(arg));
	}

	virtual void unk5(EventArg const& arg)
	{
		BASE(unk5(arg));
	}

	virtual void unk6(EventArg const& arg)
	{
		BASE(unk6(arg));
	}

	virtual void unk7(EventArg const& arg)
	{
		BASE(unk7(arg));
	}

	virtual void unk8(EventArg const& arg)
	{
		BASE(unk8(arg));
	}

	virtual void unk9(EventArg const& arg)
	{
		BASE(unk9(arg));
	}

	virtual void unk10(EventArg const& arg)
	{
		BASE(unk10(arg));
	}
};

// Global SLink Variables
static CustomEventCallbackSLink s_Callback {};
static HookedFuncType s_OriginalHookedFunc = nullptr;

static void SLinkHookCallback(uintptr_t _this, uintptr_t unk)
{
	// Call the original function.
	s_OriginalHookedFunc(_this, unk);

	char buf[500];

	PRINT("CSM: SLink Hooked!")

	// Try get the SLink root event callback object.
	auto callbackPtr = GetRootEventCallbackPtr();
	PRINT("CSM: RootCallbackPtr: %lx", reinterpret_cast<uintptr_t>(callbackPtr));

	// If the object exists, attempt to hook into it.
	if (callbackPtr != nullptr)
	{
		auto callback = *callbackPtr;
		PRINT("CSM: RootCallback: %lx", reinterpret_cast<uintptr_t>(callback));

		// Give the original callback object to ours, then make ours the one to use.
		s_Callback.m_Impl = callback;
		*callbackPtr = &s_Callback;
	}

	// Restore vtable entry.
	*GetHookFuncPtr() = s_OriginalHookedFunc;
}

// Function Hooks

HOOK_DEFINE_TRAMPOLINE(searchAssetCallTableByName) {
	static bool Callback(uintptr_t self, xlink2::Locator* _locator, char* searchKeyName) {
	    char buf[500];

// Catch any sender keys
char* realSearchKeyName = searchKeyName;
bool skipUpdate = false;
if (strstr(searchKeyName, senderTag))
{
	realSearchKeyName = strtok(realSearchKeyName, ":");
	realSearchKeyName = strtok(NULL, ":");
	skipUpdate = true;
}

// Run the original function to get the result
bool isValidKeyName = Orig(self, _locator, realSearchKeyName);

// Update Presets
if (isValidKeyName && strstr(realSearchKeyName, presetSLinkKey) && !skipUpdate)
{
	PRINT("CSM: searchAssetCallTableByName | %s", realSearchKeyName)
	presetSLinkUser = self;
	PRINT("CSM: Updating SLink Preset")
}

// Check if didnt find a call table
if (!isValidKeyName && strstr(searchKeyName, requiredPrefix) && !skipUpdate)
{
	PRINT("CSM: searchAssetCallTableByName | %s", searchKeyName)

	// Try to find existing call table
	if (!Orig(presetSLinkUser, _locator, presetSLinkKey))
	{
		return isValidKeyName;
	}

	// Create a deep copy of _locator->mResAssetCallTable
	newResAssetCallTable = *_locator->mResAssetCallTable;

	// Change the keyname of the cached call table
	newResAssetCallTable.mKeyName = new char[strlen(searchKeyName) + 1];
	strcpy(newResAssetCallTable.mKeyName, searchKeyName);

	// Set modified ResAssetCallTable to the locator
	_locator->mResAssetCallTable = &newResAssetCallTable;

	isValidKeyName = true;
}

return isValidKeyName;
}
}
;

HOOK_DEFINE_INLINE(searchAssetCallTableByNameInlinedOne) {
	static void Callback(exl::hook::InlineCtx * ctx) {
	    char buf[500];

// x0 is the result of searchAssetCallTableByNameInlinedOne
bool isValidKeyName = ctx->X[0] == 0;

// x2 is searchKeyName, param_2
char* searchKeyName = reinterpret_cast<char*>(ctx->X[2]);

// If didnt find a call table and key contains our prefix, do logic
if (!isValidKeyName && strstr(searchKeyName, requiredPrefix))
{
	PRINT("CSM: searchAssetCallTableByNameInlinedOne | %s", searchKeyName)

	xlink2::Locator locator;
	if (!presetSLinkUser || !searchAssetCallTableByNameFun(presetSLinkUser, &locator, CombineChars(senderTag, presetSLinkKey)))
	{
		PRINT("CSM: Preset Load Failed")
		return;
	}

	// Create a deep copy of _locator->mResAssetCallTable
	newResAssetCallTableInlined = *locator.mResAssetCallTable;

	// Change the keyname of the cached call table
	newResAssetCallTableInlined.mKeyName = new char[strlen(CombineChars(requiredPrefix, searchKeyName)) + 1];
	strcpy(newResAssetCallTableInlined.mKeyName, CombineChars(requiredPrefix, searchKeyName));

	// Swap the pointer in x19 to be our modded asset call table
	ctx->X[19] = reinterpret_cast<uint64_t>(&newResAssetCallTableInlined);

	// Allow the function to continue
	ctx->X[0] = 0;
	PRINT("CSM: searchAssetCallTableByNameInlinedOne | Complete!")
}
}
}
;

// Unused Function Hooks
HOOK_DEFINE_TRAMPOLINE(emitImpl) {
	static void Callback(uintptr_t * param_1, xlink2::Locator* param_2, void* param_3, void* param_4) {
	    char buf[500];
return Orig(param_1, param_2, param_3, param_4);
}
}
;

HOOK_DEFINE_REPLACE(searchAssetCallTableByNameInlinedTwo) {
	static void Callback(uintptr_t param_1, char* param_2, char* param_3, uintptr_t param_4, uintptr_t param_5) {
	    return;
}
}
;

HOOK_DEFINE_REPLACE(searchAssetCallTableByNameInlinedThree) {
	static void Callback(uintptr_t param_1, char* param_2, uintptr_t param_3, char** param_4, char** param_5, uintptr_t param_6, uint param_7) {
	    return;
}
}
;

HOOK_DEFINE_REPLACE(searchAssetCallTableByNameInlinedFour) {
	static void Callback(uintptr_t param_1, uintptr_t param_2, char* param_3, uintptr_t param_4, uintptr_t param_5) {
	    return;
}
}
;

extern "C" void exl_main(void* x0, void* x1)
{
	// Init Hooking system
	exl::hook::Initialize();

	char buf[500];
	PRINT("CSM: Loading Custom SLink Mod...");

	// Install Function hooks
	searchAssetCallTableByName::InstallAtOffset(s_searchAssetCallTableByNameOffset);
	searchAssetCallTableByNameInlinedOne::InstallAtOffset(s_searchAssetCallTableByNameInlinedOne);

	// Unused
	// emitImpl::InstallAtOffset(s_emitImpl);
	// searchAssetCallTableByNameInlinedTwo::InstallAtOffset(s_searchAssetCallTableByNameInlinedTwo);
	// searchAssetCallTableByNameInlinedThree::InstallAtOffset(s_searchAssetCallTableByNameInlinedThree);
	// searchAssetCallTableByNameInlinedFour::InstallAtOffset(s_searchAssetCallTableByNameInlinedFour);

	// SLink System vtable hooking
	auto ptr = GetHookFuncPtr();
	s_OriginalHookedFunc = *ptr;
	*ptr = SLinkHookCallback;
}