#pragma once

#include <stdint.h>
#include <bit>
#include "types.h"
#include "utils.hpp"

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

        static constexpr size_t CalculateSize(int count) {
            return sizeof(ResAssetParam) + (sizeof(ResParam) * count);
        } 

        static void SetNthBitfieldValue(xlink2::ResAssetParam*& resAssetParam, int index, bool clearValue)
        {
            if (clearValue)
            {
                ulong mask = 1ul << index;
                resAssetParam->mBitfield = resAssetParam->mBitfield & (~mask);
                return;
            }
            else
            {
                // Calculate the new bitfield by setting the bit at the specified index to 1
                ulong newBit = 1ul << index; // New bit
                resAssetParam->mBitfield = resAssetParam->mBitfield | newBit;
                return;
            }
		}

        static void AddNthValue(xlink2::ResAssetParam*& resAssetParam, int index, const xlink2::ResParam& newValue) 
        {
            // Valid Check
            if (index < 0) {
                return;
            }

            // Calculate the new size, which includes space for the new ResParam
            size_t newSize = resAssetParam->CalculateSize(resAssetParam->GetCount() + 1);

            // Allocate memory for the new block
            xlink2::ResAssetParam* newResAssetParam = (xlink2::ResAssetParam*)malloc(newSize);

            // Copy the existing data before the insertion point
            std::memcpy(newResAssetParam, resAssetParam, sizeof(xlink2::ResAssetParam) + sizeof(xlink2::ResParam) * index);

            // Set bitfield value at index
		    SetNthBitfieldValue(newResAssetParam, index, false);

		    // Calculate the index in the ResParam array
            int resParamIndex = 0;
            ulong bitfield = newResAssetParam->mBitfield;
            while (index > 0) {
                if (bitfield & 1ul) {
                    resParamIndex++;
                }
                bitfield >>= 1;
                index--;
            }

		    // Set the new ResParam at the calculated index
            xlink2::ResParam* newResParam = &newResAssetParam->GetValues()[resParamIndex];
            *newResParam = newValue;

            // Copy the remaining existing data after the insertion point
            std::memcpy(
                &newResAssetParam->GetValues()[resParamIndex + 1],
                &resAssetParam->GetValues()[resParamIndex],
                sizeof(xlink2::ResParam) * (resAssetParam->GetCount() - resParamIndex)
            );

            // Replace the old resAssetParam with the new one
            free(resAssetParam); // Free the old memory
            resAssetParam = newResAssetParam; // Update the pointer
        }

        static void RemoveNthValue(xlink2::ResAssetParam*& resAssetParam, int indexToRemove) 
        {
            if (indexToRemove < 0) {
                return;
            }

            // Calculate the new size, which excludes space for the removed ResParam
            size_t newSize = resAssetParam->CalculateSize(resAssetParam->GetCount() - 1);

            // Allocate memory for the new block
            xlink2::ResAssetParam* newResAssetParam = (xlink2::ResAssetParam*)malloc(newSize);

            // Copy the existing data before the removed element
            std::memcpy(newResAssetParam, resAssetParam, sizeof(xlink2::ResAssetParam) + sizeof(xlink2::ResParam) * indexToRemove);

            // Calculate the index in the ResParam array
            int resParamIndex = 0;
            ulong bitfield = newResAssetParam->mBitfield;
		    int tempindexToRemove = indexToRemove;
		    while (tempindexToRemove > 0) {
                if (bitfield & 1ul) {
                    resParamIndex++;
                }
                bitfield >>= 1;
                tempindexToRemove--;
            }

            // Copy the remaining existing data after the removed element
            std::memcpy(
                &newResAssetParam->GetValues()[resParamIndex],
                &resAssetParam->GetValues()[resParamIndex + 1],
                sizeof(xlink2::ResParam) * (resAssetParam->GetCount() - resParamIndex - 1)
            );

            // Update the mBitfield
            SetNthBitfieldValue(newResAssetParam, indexToRemove, true);

            // Replace the old resAssetParam with the new one
            free(resAssetParam); // Free the old memory
            resAssetParam = newResAssetParam; // Update the pointer
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