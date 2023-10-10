#include "lib.hpp"
#include "slink_hooks.hpp"
#include "config.hpp"
#include "hooks.hpp"
#include "xlink.hpp"
#include "utils.hpp"

extern "C" void exl_main(void* x0, void* x1)
{
	// Init Hooking system
	exl::hook::Initialize();

	char buf[500];
	PRINT("CSM: Loading Custom SLink Mod...");

	// Install Function hooks
	csm::hooks::searchAssetCallTableByName::InstallAtOffset(s_searchAssetCallTableByNameOffset_v121);
	csm::hooks::searchAssetCallTableByNameInlinedOne::InstallAtOffset(s_searchAssetCallTableByNameInlinedOne_v121);

	// Unused Hooks
	// emitImpl::InstallAtOffset(s_emitImpl);
	// csm::searchAssetCallTableByNameInlinedTwo::InstallAtOffset(s_searchAssetCallTableByNameInlinedTwo);
	// csm::searchAssetCallTableByNameInlinedThree::InstallAtOffset(s_searchAssetCallTableByNameInlinedThree);
	// csm::searchAssetCallTableByNameInlinedFour::InstallAtOffset(s_searchAssetCallTableByNameInlinedFour);

	// SLink System vtable hooking
	auto ptr = csm::slink_hooks::GetHookFuncPtr();
	csm::slink_hooks::s_OriginalHookedFunc = *ptr;
	*ptr = csm::slink_hooks::SLinkHookCallback;
}