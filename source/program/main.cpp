#include "lib.hpp"

#include "program/message.cpp"

#include <program/version.hpp>

#include <program/xlink.hpp>

static CustomEventCallbackSLink s_Callback {};
static HookedFuncType s_OriginalHookedFunc = nullptr;

static void Callback(uintptr_t _this, uintptr_t unk)
{
	/* Call the original function. */
	s_OriginalHookedFunc(_this, unk);

	char buf[500];

	PRINT("callback!")

	/* Try get the SLink root event callback object. */
	auto callbackPtr = GetRootEventCallbackPtr();
	PRINT("RootCallbackPtr: %lx", reinterpret_cast<uintptr_t>(callbackPtr));

	/* If the object exists, attempt to hook into it. */
	if (callbackPtr != nullptr)
	{
		auto callback = *callbackPtr;
		PRINT("RootCallback: %lx", reinterpret_cast<uintptr_t>(callback));

		/* Give the original callback object to ours, then make ours the one to use. */
		s_Callback.m_Impl = callback;
		*callbackPtr = &s_Callback;
	}

	/* Restore vtable entry. */
	*GetHookFuncPtr() = s_OriginalHookedFunc;
}

static constexpr int s_emitImpl = 0x000afd244;
static constexpr int s_searchAssetCallTableByNameOffset = 0x00afd150;
static constexpr int s_searchAssetCallTableByNameInlinedOne = 0x009ffe64;
static constexpr int s_searchAssetCallTableByNameInlinedTwo = 0x00a3aa78;
static constexpr int s_searchAssetCallTableByNameInlinedThree = 0x00f85148;
static constexpr int s_searchAssetCallTableByNameInlinedThreeLabel = 0x00f852c4;
static constexpr int s_searchAssetCallTableByNameInlinedFour = 0x02295f0c;

HOOK_DEFINE_REPLACE(emitImpl) {
	static void Callback(uintptr_t param_1, xlink2::Locator* param_2, void* param_3, void* param_4) {

	    // If is elink, skip
	    if ((*(uint*)(param_1 + 0x18) & 0x800) != 0) {
	        return;
}

char buf[500];

if (param_2 && param_2->mResAssetCallTable)
{
	// PRINT("Valid Locator Found")
	// PRINT(param_2 -> mResAssetCallTable -> mKeyName)
	// param_2 -> mResAssetCallTable -> mKeyName = "Custom";
}

// char buf[500];
// PRINT("emitImpl")
// if (param_2 && param_2->field_10 && param_2->mResAssetCallTable->IsAsset())
// {
//     PRINT("Valid Locator Found")
//     int stringTableOffset = param_2->mResAssetCallTable->mParamAsAsset->GetNthValue(1)->mValue;
//     PRINT()
// }
}
}
;

static xlink2::ResAssetCallTable mResAssetCallTableCopy;

HOOK_DEFINE_REPLACE(searchAssetCallTableByName) {
	static bool Callback(uintptr_t self, xlink2::Locator* locator, char* searchKeyName) {
	    char buf[500];

int iVar1;
uint uVar2;
int iVar3;
int iVar4;
long lVar5;
long lVar6;
int iVar7;
int iVar8;
xlink2::ResAssetCallTable* searchResult;

uVar2 = *(uint*)(self + 0x18);
if (uVar2 < 2)
{
	lVar5 = *(long*)(self + (ulong)uVar2 * 8 + 0x20);
}
else
{
	lVar5 = *(long*)(self + 0x20);
}
if ((lVar5 != 0) && (*(char*)(lVar5 + 0xb0) != '\0'))
{
	if (1 < uVar2)
	{
		uVar2 = 0;
	}
	lVar5 = *(long*)(self + (ulong)uVar2 * 8 + 0x20);
	iVar8 = *(int*)(*(long*)(lVar5 + 8) + 8);
	if (iVar8 != 0)
	{
		lVar6 = *(long*)(lVar5 + 0x28);
		iVar7 = iVar8 + -1;
		if (0 < iVar8 && lVar6 != 0)
		{
			lVar5 = *(long*)(lVar5 + 0x20);
			iVar8 = 0;
			do {
				iVar1 = iVar7 + iVar8;
				if (iVar1 < 0)
				{
					iVar1 = iVar1 + 1;
				}
				iVar1 = iVar1 >> 1;
				searchResult = (xlink2::ResAssetCallTable*)(lVar6 + (ulong) * (ushort*)(lVar5 + (long)iVar1 * 2) * 0x30);
				iVar4 = strcmp(searchKeyName, searchResult->mKeyName);
				if (iVar4 == 0) goto FOUND_ITEM;
				iVar3 = iVar1 + -1;
				if (0 < iVar4)
				{
					iVar8 = iVar1 + 1;
					iVar3 = iVar7;
				}
				iVar7 = iVar3;
			} while (iVar8 <= iVar7);
		}
	}
}
searchResult = (xlink2::ResAssetCallTable*)0x0;
FOUND_ITEM : locator->mResAssetCallTable = searchResult;

if (locator && locator->mResAssetCallTable)// && strstr(locator->mResAssetCallTable->mKeyName, "Equip"))
{
	// PRINT("Valid Locator Found")
	mResAssetCallTableCopy = *locator->mResAssetCallTable;
	mResAssetCallTableCopy.mKeyName = "Custom";
	locator->mResAssetCallTable = &mResAssetCallTableCopy;
}

return true;
// return searchResult != (uintptr_t * ) 0x0;
}
}
;

HOOK_DEFINE_REPLACE(searchAssetCallTableByNameInlinedOne) {
	static void Callback(uintptr_t param_1, char* param_2, uintptr_t param_3, uintptr_t param_4) {
	    // char buf[500];

	    // PRINT("searchAssetCallTableByNameInlinedOne")
	    // PRINT(param_2)
	    // PRINT("================")

	    return;
}
}
;

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
	char buf[500];
	PRINT("loaded");
	// if(!exlnk::IsSupportedVersion()) {
	//     PRINT("not epic");
	//     return;
	// }

	// emitImpl::InstallAtOffset(s_emitImpl);
	searchAssetCallTableByName::InstallAtOffset(s_searchAssetCallTableByNameOffset);
	// searchAssetCallTableByNameInlinedOne::InstallAtOffset(s_searchAssetCallTableByNameInlinedOne);
	// searchAssetCallTableByNameInlinedTwo::InstallAtOffset(s_searchAssetCallTableByNameInlinedTwo);
	// searchAssetCallTableByNameInlinedThree::InstallAtOffset(s_searchAssetCallTableByNameInlinedThree);
	// searchAssetCallTableByNameInlinedFour::InstallAtOffset(s_searchAssetCallTableByNameInlinedFour);

	/* Temporarily modify a vtable entry to call our func. */
	auto ptr = GetHookFuncPtr();
	s_OriginalHookedFunc = *ptr;
	*ptr = Callback;
}