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
static constexpr int s_searchAssetCallTableByNameInlinedTwo = 0x00a3aa78;
static constexpr int s_searchAssetCallTableByNameInlinedThree = 0x00f85148;
static constexpr int s_searchAssetCallTableByNameInlinedThreeLabel = 0x00f852c4;
static constexpr int s_searchAssetCallTableByNameInlinedFour = 0x02295f0c;

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

// Custom implementation of the callback object, which passes through to the original.
struct CustomEventCallbackSLink : xlink2::IEventCallbackSLink
{
	xlink2::IEventCallbackSLink* m_Impl = nullptr;

#define BASE(...)                                                                                       \
    if (m_Impl != nullptr)                                                                              \
    {                                                                                                   \
        return m_Impl->__VA_ARGS__;                                                                     \
    }

    virtual ~CustomEventCallbackSLink()
    {
        if (m_Impl != nullptr)
        {
            m_Impl->~IEventCallbackSLink();
        }
        m_Impl = nullptr;
    }

    virtual int eventActivating(EventArg const &arg)
    {
        char buf[500];
        BASE(eventActivating(arg));
        return 0;
    }
    
    virtual void eventActivated(EventArg const &arg)
    {
        char buf[500];
        BASE(eventActivated(arg));
    }

    virtual bool soundPrePlay(EventArg const &arg)
    {
        char buf[500];
        BASE(soundPrePlay(arg));
        return false;
    }

    virtual void unk1(EventArg const &arg)
    {
        char buf[500];
        BASE(unk1(arg));
    }

    virtual void soundPlayed(EventArg const &arg)
    {
        char buf[500];
        BASE(soundPlayed(arg));
    }

    virtual void soundCalced(EventArg const &arg)
    {
        char buf[500];
        BASE(soundCalced(arg));
    }

	virtual int replaceAssetInfo(aal::AssetInfo* assetInfo, ReplaceAssetInfoArg const& arg)
	{
		char buf[500];

		// arg.mAssetName->mPtr = "Weapon_Sword_Metal_Equip02";
		PRINT("AssetName: %s", arg.mAssetName->mPtr);
		PRINT("mResAssetCallTable: %s", arg.mResAssetCallTable->mKeyName);
        BASE(replaceAssetInfo(assetInfo, arg));
		return 0;
	}
    
    virtual int unk2(EventArg const &arg)
    {
        char buf[500];
        BASE(unk2(arg));
        return 0;
    }

    virtual void unk3(EventArg const &arg)
    {
        char buf[500];
        BASE(unk3(arg));
    }

    virtual void unk4(EventArg const &arg)
    {
        char buf[500];
        BASE(unk4(arg));
    }

    virtual void unk5(EventArg const &arg)
    {
        char buf[500];
        BASE(unk5(arg));
    }

    virtual void unk6(EventArg const &arg)
    {
        char buf[500];
        BASE(unk6(arg));
    }

    virtual void unk7(EventArg const &arg)
    {
        char buf[500];
        BASE(unk7(arg));
    }

    virtual void unk8(EventArg const &arg)
    {
        char buf[500];
        BASE(unk8(arg));
    }

    virtual void unk9(EventArg const &arg)
    {
        char buf[500];
        BASE(unk9(arg));
    }
    
    virtual void unk10(EventArg const &arg)
    {
        char buf[500];
        BASE(unk10(arg));
    }
};

// Global Variables
static CustomEventCallbackSLink s_Callback {};
static HookedFuncType s_OriginalHookedFunc = nullptr;
static xlink2::ResAssetCallTable s_cachedResAssetCallTable {};

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


HOOK_DEFINE_TRAMPOLINE(emitImpl) {
	static void Callback(uintptr_t * param_1, xlink2::Locator* param_2, void* param_3, void* param_4) {
	    return Orig(param_1, param_2, param_3, param_4);
}
}
;

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

HOOK_DEFINE_TRAMPOLINE(searchAssetCallTableByName) {
	static bool Callback(uintptr_t self, xlink2::Locator* _locator, char* searchKeyName) {
	    char buf[500];


bool isValidKeyName = Orig(self, _locator, searchKeyName);

// Cache a ResAssetCallTable for future use
if (isValidKeyName && !s_cachedResAssetCallTable.mKeyName)
{
    PRINT("CSM: Caching ResAssetCallTable...")

    // Create a deep copy of _locator->mResAssetCallTable
    s_cachedResAssetCallTable = *_locator->mResAssetCallTable;

    // Allocate memory for the key name and copy it
    s_cachedResAssetCallTable.mKeyName = new char[strlen(_locator->mResAssetCallTable->mKeyName) + 1];
    strcpy(s_cachedResAssetCallTable.mKeyName, _locator->mResAssetCallTable->mKeyName);
}

if (!isValidKeyName && s_cachedResAssetCallTable.mKeyName)
{
	PRINT(searchKeyName)

    // Get a new keyname to use
    char* newKeyname = CombineChars("Custom:", searchKeyName);

	// Change the keyname of the cached call table
    strcpy(s_cachedResAssetCallTable.mKeyName, newKeyname);

	// Set modified ResAssetCallTable to the locator
	_locator->mResAssetCallTable = &s_cachedResAssetCallTable;
	isValidKeyName = true;
}

return isValidKeyName;
}
}
;

HOOK_DEFINE_INLINE(searchAssetCallTableByNameInlinedOne) {
	static void Callback(exl::hook::InlineCtx * ctx) {
	    char buf[100];
	    // for(int i = 0; i < 29; i++) {
	    //     PRINT("X%d: %lx", i, ctx->X[i]);
	    // }
	    // PRINT("FP: %lx", ctx->X[29]);
	    // PRINT("LR: %lx", ctx->X[30]);

	    // x0 is the result of  searchAssetCallTableByNameInlinedOne
	    bool isValidKeyName = ctx->X[0] == 0;
if (isValidKeyName)
{
	xlink2::ResAssetCallTable* resAssetCallTable = reinterpret_cast<xlink2::ResAssetCallTable*>(ctx->X[19]);
    if (resAssetCallTable)
    {
		return;
	}

    PRINT(resAssetCallTable->mKeyName);
}
}
}
;

// Unused Functions
HOOK_DEFINE_REPLACE(searchAssetCallTableByNameInlinedTwo) {
	static void Callback(uintptr_t param_1, char* param_2, char* param_3, uintptr_t param_4, uintptr_t param_5) {
	    char buf[500];
PRINT("searchAssetCallTableByNameInlinedTwo")
PRINT(param_2)
PRINT("================")

return;
}
}
;

HOOK_DEFINE_REPLACE(searchAssetCallTableByNameInlinedThree) {
	static void Callback(uintptr_t param_1, char* param_2, uintptr_t param_3, char** param_4, char** param_5, uintptr_t param_6, uint param_7) {
	    char buf[500];
PRINT("searchAssetCallTableByNameInlinedThree")
PRINT(param_2)
PRINT("================")

return;
}
}
;

HOOK_DEFINE_REPLACE(searchAssetCallTableByNameInlinedFour) {
	static void Callback(uintptr_t param_1, uintptr_t param_2, char* param_3, uintptr_t param_4, uintptr_t param_5) {
	    char buf[500];
PRINT("searchAssetCallTableByNameInlinedFour")
PRINT(param_3)
PRINT("================")

return;
}
}
;

extern "C" void exl_main(void* x0, void* x1)
{
	// Init Hooking system
	exl::hook::Initialize();

	char buf[500];
	PRINT("CSM: Loading Custom SLink Module...");

	// Install Function hooks
	// emitImpl::InstallAtOffset(s_emitImpl);
	// searchAssetCallTableByName::InstallAtOffset(s_searchAssetCallTableByNameOffset);
	// searchAssetCallTableByNameInlinedOne::InstallAtOffset(s_searchAssetCallTableByNameInlinedOne);

    // Unused
	// searchAssetCallTableByNameInlinedTwo::InstallAtOffset(s_searchAssetCallTableByNameInlinedTwo);
	// searchAssetCallTableByNameInlinedThree::InstallAtOffset(s_searchAssetCallTableByNameInlinedThree);
	// searchAssetCallTableByNameInlinedFour::InstallAtOffset(s_searchAssetCallTableByNameInlinedFour);

    // SLink System vtable hooking
	auto ptr = GetHookFuncPtr();
	s_OriginalHookedFunc = *ptr;
	*ptr = SLinkHookCallback;
}