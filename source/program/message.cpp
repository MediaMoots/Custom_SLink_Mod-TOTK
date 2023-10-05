#include "lib.hpp"
#include <source_location>
#include <program/xlink.hpp>

#define PRINT(...)                                         \
    {                                                      \
        int len = snprintf(buf, sizeof(buf), __VA_ARGS__); \
        svcOutputDebugString(buf, len);                    \
    }

static constexpr int s_SLinkInstanceOffset = 0x0471a578;
static constexpr int s_RootCallbackOffset = 0x11D8;
static constexpr int s_VtableHookOffset = 0x043C67D8;

/* Get pointer to the callback object pointer in the SLink system. */
static xlink2::IEventCallbackSLink **GetRootEventCallbackPtr()
{
    return exl::util::pointer_path::FollowSafe<xlink2::IEventCallbackSLink *, s_SLinkInstanceOffset, s_RootCallbackOffset>();
}

/* Get pointer to a function pointer within a vtable. This is in SplSoundMgr and it registers the SLink root callback. */
using HookedFuncType = void (*)(uintptr_t, uintptr_t);
static HookedFuncType *GetHookFuncPtr()
{
    return exl::util::pointer_path::FollowSafe<HookedFuncType, s_VtableHookOffset>();
}

/* Our custom implementation of the callback object, which passes through to the original. */
struct CustomEventCallbackSLink : xlink2::IEventCallbackSLink
{

    xlink2::IEventCallbackSLink *m_Impl = nullptr;

#define BASE(...)                                                                                       \
    PRINT("%s: %s", std::source_location::current().function_name(), arg.mResAssetCallTable->mKeyName); \
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
        // BASE(eventActivating(arg));
        return 0;
    }
    virtual void eventActivated(EventArg const &arg)
    {
        char buf[500];
        // BASE(eventActivated(arg));
    }
    virtual bool soundPrePlay(EventArg const &arg)
    {
        char buf[500];
        // BASE(soundPrePlay(arg));
        return false;
    }
    virtual void unk1(EventArg const &arg)
    {
        char buf[500];
        // PRINT("unk1");
        // BASE(unk1(arg));
    }
    virtual void soundPlayed(EventArg const &arg)
    {
        char buf[500];
        //BASE(soundPlayed(arg));
    }
    virtual void soundCalced(EventArg const &arg)
    {
        char buf[500];
        // BASE(soundCalced(arg));
    }
    virtual int replaceAssetInfo(aal::AssetInfo *assetInfo, ReplaceAssetInfoArg const &arg)
    {
        char buf[500];

        // arg.mAssetName->mPtr = "Weapon_Sword_Metal_Equip02";
        PRINT("AssetName: %s", arg.mAssetName->mPtr);
        PRINT("mResAssetCallTable: %s", arg.mResAssetCallTable->mKeyName);
        //BASE(replaceAssetInfo(assetInfo, arg));
        return 0;
    }
    virtual int unk2(EventArg const &arg)
    {
        char buf[500];
        // PRINT("unk2");
        //BASE(unk2(arg));
        return 0;
    }
    virtual void unk3(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk3");
        // BASE(unk3(arg));
    }
    virtual void unk4(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk4");
        // BASE(unk4(arg));
    }
    virtual void unk5(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk5");
        // BASE(unk5(arg));
    }
    virtual void unk6(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk6");
        // BASE(unk6(arg));
    }
    virtual void unk7(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk7");
        // BASE(unk7(arg));
    }
    virtual void unk8(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk8");
        // BASE(unk8(arg));
    }
    virtual void unk9(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk9");
        // BASE(unk9(arg));
    }
    virtual void unk10(EventArg const &arg)
    {
        char buf[500];
        PRINT("unk10");
        // BASE(unk10(arg));
    }
};