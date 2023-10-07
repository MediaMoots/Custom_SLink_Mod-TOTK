#pragma once

#include <stdint.h>
#include <bit>
#include "types.h"

namespace sead {

    struct BitFlagUtil {
        static constexpr int CountOnBit64(ulong x) {
            return std::popcount(x);
        }


        static constexpr int CountRightOnBit64(ulong x, int bit) {
            ulong mask = ((1ul << bit) - 1) | (1ul << bit);
            return CountOnBit64(x & mask);
        }
    };

    template<typename T>
    struct SafeStringBase {
        T* mPtr;
    };
    using SafeString = SafeStringBase<char>;
}

namespace aal {
    struct AssetInfo;
    struct Handle;
}

namespace xlink2 {
    
    struct UserInstanceSLink;
    struct AssetExecutorSLink;
    struct EventSLink;

    enum class ValueReferenceType : u8 {
        Direct = 0,
        String = 1,
        Curve = 2,
    };

    struct __attribute__((packed)) ResParam {
        int mValue : 24;
        ValueReferenceType mType;
    };

    struct ResAssetParam {
        ulong mBitfield;

        inline int GetCount() {
            return std::popcount(mBitfield);
        }

        inline ResParam* GetValues() {
            return reinterpret_cast<ResParam*>(this + 1);
        }

        inline bool IsValueDefault(int n) {
            return (mBitfield & (1ul << n)) == 0;
        }

        inline ResParam* GetNthValue(int n) {
            return &GetValues()[sead::BitFlagUtil::CountRightOnBit64(mBitfield, n) - 1];
        }
    };

    struct ResContainerParam;
    struct ResCondition;

    struct ResAssetCallTable {
        char* mKeyName;
        ushort mAssetId;
        ushort mFlag;
        int mDuration;
        int mParentIndex;
        ushort mEnumIndex;
	    bool mIsSolved;
        int KeyNameHash;
        union {
            ResAssetParam* mParamAsAsset;
            ResContainerParam* mParamAsContainer;
        };
        ResCondition* mCondition;

        inline bool IsContainer() const { return static_cast<bool>(mFlag & 1); }
        inline bool IsAsset() const { return !IsContainer(); } 
    };

    struct IEventCallbackSLink {
        struct EventArg {
            UserInstanceSLink* mUserInterface;
            aal::Handle* mAalHandle;
            ResAssetCallTable const* mResAssetCallTable;
            AssetExecutorSLink* mExecutor;
            EventSLink* mEvent;
        };

        struct ReplaceAssetInfoArg {
            sead::SafeString* mAssetName;
            UserInstanceSLink* mUserInstance;
		    EventSLink* mEvent;
            int unk2;
            ResAssetCallTable const* mResAssetCallTable;
	    };

        virtual ~IEventCallbackSLink() {}

        virtual int eventActivating(EventArg const&) { return 0; }
        virtual void eventActivated(EventArg const&) {}
        virtual bool soundPrePlay(EventArg const&) { return false; }
        virtual void unk1(EventArg const&) {}
        virtual void soundPlayed(EventArg const&) {}
        virtual void soundCalced(EventArg const&) {}
        virtual int replaceAssetInfo(aal::AssetInfo*, ReplaceAssetInfoArg &) { return 0; }
        virtual int unk2(EventArg const&) { return 0; }
        virtual void unk3(EventArg const&) {}
        virtual void unk4(EventArg const&) {}
        virtual void unk5(EventArg const&) {}
        virtual void unk6(EventArg const&) {}
        virtual void unk7(EventArg const&) {}
        virtual void unk8(EventArg const&) {}
        virtual void unk9(EventArg const&) {}
        virtual void unk10(EventArg const&) {}
    };

    struct Locator{
        ResAssetCallTable* mResAssetCallTable;
        char* field_10;
        int mType = 0;
    };
}