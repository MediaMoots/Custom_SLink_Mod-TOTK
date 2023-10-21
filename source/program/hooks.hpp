#pragma once

#include "config.hpp"
#include "keynameutils.hpp"
#include "lib.hpp"
#include "xlink.hpp"

namespace csm::hooks
{
////////////////////////////////////////// searchAssetCallTableByName ////////////////////////////////////////////

HOOK_DEFINE_TRAMPOLINE(searchAssetCallTableByName) {
	static bool Callback(uintptr_t self, xlink2::Locator* _locator, char* searchKeyName) {
	    char buf[500];

// Run the original function to get the result
bool isValidKeyName = Orig(self, _locator, searchKeyName);

// Check if didnt find a call table
if (!isValidKeyName && strstr(searchKeyName, requiredPrefix) && cachedResAssetCallTable.mParamAsAsset)
{
	PRINT("CSM: searchAssetCallTableByName | Caught Slink Key: %s", searchKeyName)

	// Replace the name
	csm::keynameutils::ReplaceRuntimeAssetName(&cachedResAssetCallTable, searchKeyName);

	// Set modified ResAssetCallTable to the locator
	*_locator->mResAssetCallTable = cachedResAssetCallTable;

	PRINT("CSM: searchAssetCallTableByName | Modded Slink Key: %s", searchKeyName)

	isValidKeyName = true;
}

return isValidKeyName;
}
}
;

////////////////////////////////////////// searchAssetCallTableByNameInlinedOne ////////////////////////////////////////////

HOOK_DEFINE_INLINE(searchAssetCallTableByNameInlinedOne) {
	static void Callback(exl::hook::InlineCtx * ctx) {
	    char buf[500];

// x0 is the result of searchAssetCallTableByNameInlinedOne
bool isValidKeyName = ctx->X[0] == 0;

// x2 is searchKeyName, param_2
char* searchKeyName = reinterpret_cast<char*>(ctx->X[2]);

// If didnt find a call table and key contains our prefix, do logic
if (!isValidKeyName && strstr(searchKeyName, requiredPrefix) && cachedResAssetCallTable.mKeyName)
{
	PRINT("CSM: searchAssetCallTableByNameInlinedOne | Caught SLink Key: %s", searchKeyName)

	// Replace the name
	csm::keynameutils::ReplaceRuntimeAssetName(&cachedResAssetCallTable, searchKeyName);

	// Swap the pointer in x19 to be our modded asset call table
	ctx->X[19] = reinterpret_cast<uint64_t>(&cachedResAssetCallTable);

	// Allow the function to continue
	ctx->X[0] = 0;

	PRINT("CSM: searchAssetCallTableByNameInlinedOne | Modded SLink Key: %s", searchKeyName)
}
}
}
;

// Unused Function Hooks
HOOK_DEFINE_TRAMPOLINE(emitImpl) {
	static void Callback(uintptr_t * param_1, xlink2::Locator* locator, void* param_3, void* param_4) {
	    return Orig(param_1, locator, param_3, param_4);
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
}
