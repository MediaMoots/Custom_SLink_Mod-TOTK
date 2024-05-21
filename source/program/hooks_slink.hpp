#pragma once

#include "binaryoffsethelper.hpp"
#include "config.hpp"
#include "lib.hpp"
#include "utils.hpp"
#include "xlink.hpp"

namespace csm::hooks_slink
{
// Get pointer to the callback object pointer in the SLink system.
static xlink2::IEventCallbackSLink** GetRootEventCallbackPtr()
{
	switch (csm::helpers::GetAppVersionIndex())
	{
	case 0: // 1.0.0
		return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset_v100, s_RootCallbackOffset_v100>();
	case 1: // 1.1.0
		return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset_v110, s_RootCallbackOffset_v110>();
	case 2: // 1.1.1
		return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset_v111, s_RootCallbackOffset_v111>();
	case 3: // 1.1.2
		return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset_v112, s_RootCallbackOffset_v112>();
	case 4: // 1.2.0
		return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset_v120, s_RootCallbackOffset_v120>();
	case 5: // 1.2.1
		return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset_v121, s_RootCallbackOffset_v121>();
	default: // Default to latest version
		return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink*, s_SLinkInstanceOffset_v121, s_RootCallbackOffset_v121>();
	}
}

// Get pointer to a function pointer within a vtable. This is in TOTK's sound manager and it registers the SLink root callback.
using HookedFuncType = void (*)(uintptr_t, uintptr_t);
static HookedFuncType* GetHookFuncPtr()
{
	switch (csm::helpers::GetAppVersionIndex())
	{
	case 0: // 1.0.0
		return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset_v100>();
	case 1: // 1.1.0
		return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset_v110>();
	case 2: // 1.1.1
		return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset_v111>();
	case 3: // 1.1.2
		return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset_v112>();
	case 4: // 1.2.0
		return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset_v120>();
	case 5: // 1.2.1
		return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset_v121>();
	default: // Default to latest version
		return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset_v121>();
	}
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

	virtual int replaceAssetInfo(aal::AssetInfo* assetInfo, ReplaceAssetInfoArg& arg)
	{
		char buf[500];

		// If CSM_ is in key name, change the asset name
		bool isCSMCall = strstr(arg.mResAssetCallTable->mKeyName, requiredPrefix);
		if (isCSMCall)
		{
			PRINT("CSM: replaceAssetInfo | CSM SLink Name: %s", arg.mResAssetCallTable->mKeyName);

			PRINT("CSM: replaceAssetInfo | Original Asset Name: %s", arg.mAssetName->mPtr);

			// Make a new cachedAssetName var and copy that to the mAssetName
			sead::SafeString cachedAssetName;
			cachedAssetName.mPtr = new char[strlen(arg.mResAssetCallTable->mKeyName) + 1];
			strncpy(cachedAssetName.mPtr, arg.mResAssetCallTable->mKeyName, strlen(arg.mResAssetCallTable->mKeyName) + 1);

			*arg.mAssetName = cachedAssetName;

			PRINT("CSM: replaceAssetInfo | Modded Asset Name: %s", arg.mAssetName->mPtr);
		}

		// GroupName offsets | Index 2
		// SystemDefault = 450297
		// PlayerVoice = 392072
		// DemoDefault = 121443
		// Player = 385960

		// Priority Offsets | Index 13
		// 1 = 4

		// Bone Offsets | Index 16
		// Lip_U = 295237

		// Volume Offsets | Index 3

		if (arg.mResAssetCallTable->IsAsset() && !cachedResAssetCallTable.mParamAsAsset
		    && arg.mResAssetCallTable->mParamAsAsset->GetNthValue(2)->mValue == 450297)
		{
			cachedResAssetCallTable = *arg.mResAssetCallTable;

			// Create cachedResAssetParam only once
			if (cachedResAssetParam == nullptr)
			{
				auto sizeOfNewResAssetParam = xlink2::ResAssetParam::CalculateSize(arg.mResAssetCallTable->mParamAsAsset->GetCount());
				cachedResAssetParam = (xlink2::ResAssetParam*)malloc(sizeOfNewResAssetParam);
				std::memcpy(cachedResAssetParam, arg.mResAssetCallTable->mParamAsAsset, sizeOfNewResAssetParam);

				// Change values

				// Change Group Name to DemoDefault
				cachedResAssetParam->GetNthValue(2)->mValue = 121443;

				// Set Bone = Lip_U
				xlink2::ResParam newResParam = xlink2::ResParam();
				newResParam.mType = xlink2::ValueReferenceType::String;
				newResParam.mValue = 295237;
				xlink2::ResAssetParam::AddNthValue(cachedResAssetParam, 16, newResParam);

				// Change Priority to 1
				cachedResAssetParam->GetNthValue(13)->mValue = 4;

				// Disable volume param
				xlink2::ResAssetParam::RemoveNthValue(cachedResAssetParam, 3);
			}

			// Set param pointer
			cachedResAssetCallTable.mParamAsAsset = cachedResAssetParam;

			PRINT("CSM: replaceAssetInfo | Updating Presets with: %s", arg.mResAssetCallTable->mKeyName)
		}

		// if (arg.mResAssetCallTable->IsAsset() && arg.mResAssetCallTable->mParamAsAsset && strstr(arg.mResAssetCallTable->mKeyName, "mc"))
		// {
		// 	PRINT("CSM: replaceAssetInfo | SLink Name: %s", arg.mResAssetCallTable->mKeyName);

		// 	PRINT("CSM: replaceAssetInfo | Param Count: %d", arg.mResAssetCallTable->mParamAsAsset->GetCount());

		// 	if (arg.mResAssetCallTable->mParamAsAsset->GetCount() >= 4)
		// 	{
		// 		PRINT("CSM: replaceAssetInfo | Bitfield: %d", cachedResAssetCallTable.mParamAsAsset->mBitfield);
		// 		PRINT("CSM: replaceAssetInfo | Param 2 Type: %d", cachedResAssetCallTable.mParamAsAsset->GetNthValue(2)->mType);
		// 		PRINT("CSM: replaceAssetInfo | Param 2 Value: %d", cachedResAssetCallTable.mParamAsAsset->GetNthValue(2)->mValue);
		// 		PRINT("CSM: replaceAssetInfo | Param 16 Type: %d", cachedResAssetCallTable.mParamAsAsset->GetNthValue(16)->mType);
		// 		PRINT("CSM: replaceAssetInfo | Param 16 Value: %d", cachedResAssetCallTable.mParamAsAsset->GetNthValue(16)->mValue);

		// 		PRINT("CSM: replaceAssetInfo | Param 0 Type: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(0)->mType);
		// 		PRINT("CSM: replaceAssetInfo | Param 0 Value: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(0)->mValue);
		// 		PRINT("CSM: replaceAssetInfo | Param 1 Type: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(1)->mType);
		// 		PRINT("CSM: replaceAssetInfo | Param 1 Value: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(1)->mValue);
		// 		PRINT("CSM: replaceAssetInfo | Param 2 Type: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(2)->mType);
		// 		PRINT("CSM: replaceAssetInfo | Param 2 Value: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(2)->mValue);
		// 		PRINT("CSM: replaceAssetInfo | Param 3 Type: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(3)->mType);
		// 		PRINT("CSM: replaceAssetInfo | Param 3 Value: %d", arg.mResAssetCallTable->mParamAsAsset->GetNthValue(3)->mValue);
		// 	}
		// }

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
}