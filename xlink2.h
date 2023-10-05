struct xlink2::IUser;
struct xlink2::PropertyDefinition;
struct sead::hostio::Node;
struct xlink2::Locator;
struct sead::Viewport;
struct sead::DebugFontMgrJis1Nvn;
struct sead::DrawContext;
struct sead::Heap;
struct sead::Projection;
struct sead::FontBase;
struct sead::TextWriter;
struct aal::Emitter;
struct aal::Listener;
struct aal::Shape;
struct xlink2::Event;
struct xlink2::ResourceAccessor;
struct xlink2::UserResourceELink;
struct xlink2::System;
struct xlink2::ParamDefineTable;
struct xlink2::User;
struct xlink2::ModelAssetConnection;
struct xlink2::UserResource;
struct xlink2::AssetExecutor;
struct xlink2::ContainerBase;
struct xlink2::ErrorMgr;
struct xlink2::EditorBuffer;
struct xlink2::ResourceBuffer;
struct xlink2::TriggerCtrl;
struct xlink2::ILockProxy;
struct sead::UnitHeap;
struct sead::Camera;
struct xlink2::HoldMgr;
struct xlink2::SequenceContainer;
struct sead::SafeStringBase;
struct sead::BufferedSafeStringBase;
struct sead::Vector3f;
struct sead::Vector3;
struct xlink2::ResUserHeader;
struct sead::SafeStringBase_vtbl;
struct sead::Matrix34;
struct sead::IDisposer_vtbl;
struct sead::RuntimeTypeInfo::Interface;
struct sead::hostio::Node_vtbl;
struct sead::Camera_vtbl;
struct sead::FontBase_vtbl;
struct xlink2::IUser_vtbl;
struct xlink2::ILockProxy_vtbl;
struct xlink2::Event_vtbl;
struct xlink2::ResAssetCallTable;
struct xlink2::UserInstance_vtbl;
struct xlink2::ContainerBase_vtbl;
struct xlink2::System_vtbl;
struct xlink2::ResParam;
struct xlink2::ResourceAccessor_vtbl;
struct xlink2::UserResource_vtbl;
struct xlink2::UserResourceParam;
struct xlink2::CommonResourceParam;
struct xlink2::ResActionTrigger;
struct xlink2::UserInstanceParam;
struct xlink2::ResTriggerOverwriteParam;
struct xlink2::Locator_vtbl;
struct sead::FreeList::Node;
struct xlink2::ParamDefine;
struct xlink2::ResProperty;
struct xlink2::ResAction;
struct xlink2::ResActionSlot;
struct xlink2::ResCallTable;
struct xlink2::ResPropertyTrigger;
struct xlink2::ResAlwaysTrigger;
struct xlink2::ResRandomCallTable;
struct xlink2::CurvePointTable;
struct xlink2::ResAssetParamTable;
struct xlink2::TriggerCtrlParam;
struct xlink2::ModelTriggerConnection;
struct xlink2::AssetExecutor_vtbl;
struct aal::IUnifiable_vtbl;
struct aal::NamedObj_vtbl;
struct xlink2::ResCurveCallTable;
struct struct_v24;
struct xlink2::ParamDefineTableHeader;
struct struct_v8_4;
struct struct_v20;
struct struct_v10_2;
struct sead::Projection_vtbl;
struct xlink2::TriggerCtrl_vtbl;

/* 4471 */
struct sead::ListNode
{
  sead::ListNode *mPrev;
  sead::ListNode *mNext;
};

/* 14508 */
typedef int s32;

/* 4472 */
struct __attribute__((packed)) sead::ListImpl
{
  sead::ListNode mStartEnd;
  s32 mCount;
};

/* 15059 */
struct __cppobj sead::OffsetList : sead::ListImpl
{
  s32 mIndex;
};

/* 5227 */
struct __attribute__((aligned(8))) xlink2::TriggerCtrlMgr
{
  int field_0;
  xlink2::TriggerCtrlParam *mParamsByResMode[2];
  uint mActionTriggeredBitfield;
};

/* 16057 */
enum xlink2::UserInstance::State : __int8
{
  xlink2::UserInstance::State_UsingEditor = 0x1,
  xlink2::UserInstance::State_Sleeping = 0x2,
  xlink2::UserInstance::State_4 = 0x4,
};

/* 16569 */
struct sead::BufferOfstruct_v10_2
{
  s32 mCount;
  struct_v10_2 *mBuffer;
};

/* 5212 */
struct __attribute__((aligned(8))) xlink2::UserInstance
{
  xlink2::UserInstance_vtbl *__vftable /*VFT*/;
  sead::OffsetList mEventList;
  xlink2::UserInstanceParam *mParamsByResMode[2];
  xlink2::User *mUser;
  xlink2::IUser *field_38;
  const sead::Matrix34 *mRootMtx;
  char field_48;
  const sead::Vector3 *mRootPos;
  sead::Vector3 *mScale;
  float field_60;
  _QWORD mValueChangedBitfield;
  float *mPropertyValueArray;
  xlink2::TriggerCtrlMgr mTriggerCtrlMgr;
  void *mUserData;
  _BYTE gapA0[48];
  xlink2::UserInstance::State mState;
  _QWORD field_D8;
  sead::BufferOfstruct_v10_2 field_E0;
};

/* 15135 */
enum xlink2::ResMode
{
  xlink2_ResMode_Normal = 0x0,
  xlink2_ResMode_Editor = 0x1,
};

/* 15112 */
struct /*VFT*/ __attribute__((aligned(8))) xlink2::UserInstance_vtbl
{
  __int64 (__fastcall *makeDebugStringEvent)(xlink2::UserInstance *__hidden this, sead::BufferedSafeStringBase *, const sead::SafeStringBase *);
  __int64 (__fastcall *dtor1)(xlink2::UserInstance *__hidden this);
  __int64 (__fastcall *dtor2)(xlink2::UserInstance *__hidden this);
  __int64 (__fastcall *getDefaultGroup)(const xlink2::UserInstance *__hidden this);
  __int64 (__fastcall *onPostCalc_)(xlink2::UserInstance *__hidden this);
  __int64 (__fastcall *onReset_)(xlink2::UserInstance *__hidden this);
  __int64 (__fastcall *onDestroy_)(xlink2::UserInstance *__hidden this);
  xlink2::UserInstanceParam *(__fastcall *allocInstanceParam_)(xlink2::UserInstance *__hidden this, sead::Heap *);
  void (__fastcall *freeInstanceParam_)(xlink2::UserInstance *, xlink2::UserInstanceParam *, xlink2::ResMode);
  void (__fastcall *onSetupInstanceParam_)(xlink2::UserInstance *, xlink2::ResMode, sead::Heap *);
  void (__fastcall *initModelAssetConnection_)(xlink2::UserInstance *, xlink2::ResMode, const xlink2::ParamDefineTable *, sead::Heap *__struct_ptr);
  bool (__fastcall *doEventActivatingCallback_)(xlink2::UserInstance *__hidden this, const xlink2::Locator *);
  __int64 (__fastcall *doEventActivatedCallback_)(xlink2::UserInstance *__hidden this, const xlink2::Locator *, xlink2::Event *);
};

/* 15619 */
struct sead::BufferOfxlink2::ModelAssetConnection
{
  s32 mCount;
  xlink2::ModelAssetConnection *mBuffer;
};

/* 16065 */
struct sead::BufferOfstruct_v8_4
{
  s32 mCount;
  struct_v8_4 *mBuffer;
};

/* 4473 */
struct __attribute__((aligned(8))) sead::PtrArrayImpl
{
  s32 mCount;
  _DWORD mLength;
  void **mPtr;
};

/* 16055 */
struct sead::BufferOfstruct_v24
{
  s32 mCount;
  struct_v24 *mBuffer;
};

/* 15136 */
struct __attribute__((aligned(8))) xlink2::UserInstanceParam
{
  sead::BufferOfxlink2::ModelAssetConnection mModelAssetConnectionBuffer;
  sead::BufferOfstruct_v8_4 mRandomHistory;
  char field_20;
  sead::PtrArrayImpl field_28;
  sead::BufferOfstruct_v24 field_38;
};

/* 15265 */
typedef unsigned __int16 uint16_t;

/* 14516 */
typedef uint16_t u16;

/* 14515 */
typedef uint8_t u8;

/* 5228 */
struct __attribute__((aligned(8))) xlink2::User
{
  _QWORD field_0;
  _QWORD field_8;
  const char *mName;
  xlink2::UserResource *mUserResource;
  sead::OffsetList mUserInstanceList;
  _QWORD mHeap;
  uint field_40;
  u16 mPropertyDefinitionTableCount;
  __int16 mActionSlotCount;
  const xlink2::PropertyDefinition **mPropertyDefinitionTable;
  const char **mActionSlot;
  u8 field_58;
};

/* 5 */
struct xlink2::IUser
{
  xlink2::IUser_vtbl *__vftable /*VFT*/;
};

/* 14537 */
struct sead::Matrix34
{
  float m[3][4];
};

/* 14368 */
struct sead::Vector3
{
  float x;
  float y;
  float z;
};

/* 16067 */
struct sead::BufferOfstruct_v20
{
  s32 mCount;
  struct_v20 *mBuffer;
};

/* 15319 */
struct sead::BufferOfxlink2::ModelTriggerConnection
{
  s32 mCount;
  xlink2::ModelTriggerConnection *mBuffer;
};

/* 15317 */
struct __attribute__((aligned(8))) xlink2::TriggerCtrlParam
{
  sead::BufferOfstruct_v20 field_0;
  sead::BufferOfxlink2::ModelTriggerConnection mPropertyTriggerConnections;
  sead::BufferOfxlink2::ModelTriggerConnection mAlwaysTriggerConnections;
  sead::PtrArrayImpl mActionTriggerArry;
  sead::PtrArrayImpl mPropertyTriggerArry;
  sead::PtrArrayImpl mPropertyTriggerCtrls;
  xlink2::TriggerCtrl *field_60;
  sead::PtrArrayImpl mAllTriggerCtrls;
};

/* 14306 */
struct __attribute__((aligned(8))) sead::SafeStringBase
{
  sead::SafeStringBase_vtbl *__vftable /*VFT*/;
  char *mPtr;
};

/* 14341 */
struct __cppobj __attribute__((packed)) __attribute__((aligned(4))) sead::BufferedSafeStringBase : sead::SafeStringBase
{
  uint mLength;
};

/* 14462 */
struct __cppobj __attribute__((aligned(8))) sead::FixedSafeString128 : sead::BufferedSafeStringBase
{
  char mData[128];
};

/* 16568 */
struct __attribute__((aligned(4))) struct_v10_2
{
  sead::FixedSafeString128 mKeyName;
  _BYTE mTriggerType;
  int field_9C;
};

/* 8061 */
struct __attribute__((aligned(8))) sead::IDisposer
{
  sead::IDisposer_vtbl *__vftable /*VFT*/;
  sead::Heap *mHeap;
  _DWORD size;
  _QWORD mFreeSize;
};

/* 14361 */
enum sead::Heap::HeapDirection
{
  HeapDirection_Reverse = 0x0,
  HeapDirection_Forward = 0x1,
};

/* 14893 */
struct nn::os::ThreadType;

/* 15123 */
struct nn::os::detail::InternalCriticalSectionImplByHorizon
{
  uint field_0;
};

/* 15125 */
struct nn::os::detail::InternalCriticalSection
{
  nn::os::detail::InternalCriticalSectionImplByHorizon impl;
};

/* 15127 */
struct nn::os::detail::InternalCriticalSectionStorage
{
  nn::os::detail::InternalCriticalSection storage;
};

/* 15128 */
union nn::os::MutexType::$B8F3897512A55A5D3977AA8F742F121D
{
  int32_t _mutexImage[1];
  nn::os::detail::InternalCriticalSectionStorage _mutex;
};

/* 15129 */
struct nn::os::MutexType
{
  uint8_t _state;
  bool _isRecursive;
  int _lockLevel;
  int _nestCount;
  nn::os::ThreadType *_ownerThread;
  union
  {
    int32_t _mutexImage[1];
    nn::os::detail::InternalCriticalSectionStorage _mutex;
  };
};

/* 7462 */
struct sead::CriticalSection
{
  sead::IDisposer mDisposer;
  nn::os::MutexType mMutex;
};

/* 4509 */
struct __cppobj sead::Heap : sead::IDisposer
{
  sead::SafeStringBase mName;
  u64 *thunk;
  sead::ListNode *mStart;
  size_t mSize;
  sead::Heap *mParent;
  sead::OffsetList mChildren;
  sead::ListNode mListNode;
  sead::OffsetList mDisposerList;
  sead::Heap::HeapDirection mHeapDirection;
  sead::CriticalSection mMutex;
  __int16 mFlags;
  u16 mTag;
  char mAllocMode;
  char mFindFreeBlockMode;
};

/* 5223 */
struct __attribute__((aligned(8))) xlink2::ParamDefineTable
{
  _DWORD mNumAllParams;
  int mNumTotalAssetParams;
  _DWORD mNumTrigger;
  xlink2::ParamDefine *mUserParams;
  xlink2::ParamDefine *mAssetParams;
  xlink2::ParamDefine *mTriggerParams;
  int mStringTable;
  int mNumUserAssetParams;
  int mNumStandardAssetParams;
  int mNumNonUserParams;
  int mNumUserParams;
  _DWORD mTotalSize;
  bool mSetup;
};

/* 15140 */
enum xlink2::TriggerType
{
  xlink2_TriggerType_Action = 0x0,
  xlink2_TriggerType_Property = 0x1,
  xlink2_TriggerType_Always = 0x2,
};

/* 460 */
struct __attribute__((aligned(8))) xlink2::Locator
{
  xlink2::Locator_vtbl *__vftable /*VFT*/;
  const xlink2::ResAssetCallTable *mResAssetCallTable;
  char field_10;
  xlink2::TriggerType mType;
};

/* 15145 */
struct __attribute__((aligned(8))) xlink2::BoneMtx
{
  const sead::Matrix34 *field_0;
  _BYTE field_8;
};

/* 5206 */
struct __attribute__((aligned(4))) xlink2::Event
{
  xlink2::Event_vtbl *__vftable /*VFT*/;
  _DWORD field_8;
  void *field_10;
  int field_18;
  int field_1C;
  uint mEventId;
  xlink2::UserInstance *mUserInstance;
  const xlink2::ResAssetCallTable *mResAssetCallTable;
  xlink2::TriggerType mTriggerType;
  xlink2::ResTriggerOverwriteParam *mResTriggerOverwriteParam;
  xlink2::BoneMtx mBoneMtx;
  xlink2::ContainerBase *mContainer;
  sead::OffsetList mAliveAssetExecutorList;
  sead::OffsetList mAssetExecutorList;
  float field_90;
  char mGroup;
};

/* 5231 */
struct __attribute__((aligned(8))) xlink2::ModelAssetConnection
{
  _QWORD __vftable;
  const sead::Matrix34 *mRootMtx;
  char field_10;
};

/* 16064 */
struct struct_v8_4
{
  int mOldIndex;
  int mNewIndex;
};

/* 16054 */
struct __attribute__((aligned(8))) struct_v24
{
  _DWORD field_0;
  aal::Emitter *mEmitter;
  _BYTE byte10;
};

/* 5232 */
struct __attribute__((aligned(8))) xlink2::UserResource
{
  xlink2::UserResource_vtbl *__vftable /*VFT*/;
  xlink2::User *mUser;
  xlink2::ResMode mResMode;
  xlink2::UserResourceParam *mParams[2];
};

/* 14396 */
struct __cppobj __attribute__((aligned(8))) sead::FixedSafeString64 : sead::BufferedSafeStringBase
{
  char mData[64];
};

/* 16051 */
enum xlink2::PropertyType
{
  xlink2_PropertyType_Enum = 0x0,
  xlink2_PropertyType_S32 = 0x1,
  xlink2_PropertyType_F32 = 0x2,
  xlink2_PropertyType_End = 0x3,
};

/* 44 */
struct __attribute__((aligned(4))) xlink2::PropertyDefinition
{
  __int64 __vftable;
  sead::FixedSafeString64 mUserName;
  xlink2::PropertyType mType;
  char field_64;
};

/* 7530 */
struct xlink2::ToolConnectionContext;

/* 15106 */
struct xlink2::IUser_vtbl
{
  sead::Matrix34 *(__fastcall *getBoneWorldMtxPtr)(xlink2::IUser *__hidden this, const char *);
  char *(__fastcall *getActionSlotName)(xlink2::IUser *__hidden this, int);
  sead::Camera *(__fastcall *getDebugDrawCamera)(xlink2::IUser *__hidden this);
  __int64 (__fastcall *getDebugDrawProjection)(xlink2::IUser *__hidden this);
  __int64 (__fastcall *_ZNK2Lp3Sys10XLinkIUser16getDebugUserNameEv)(xlink2::IUser **__hidden this);
  __int64 (__fastcall *getUserInformation)(xlink2::IUser *__hidden this);
  _QWORD (__cdecl *_ZNK2Lp3Sys10XLinkIUser20getReservedAssetNameEPN6xlink221ToolConnectionContextE)(xlink2::IUser **__hidden this, xlink2::ToolConnectionContext *);
  int (__fastcall *getNumBone)(xlink2::IUser *__hidden this);
  const char *(__fastcall *getBoneName)(xlink2::IUser *__hidden this, int);
  __int64 (__fastcall *_ZNK2Lp3Sys10XLinkIUser12getNumActionEi)(xlink2::IUser **__hidden this, int);
  __int64 (__fastcall *_ZNK2Lp3Sys10XLinkIUser13getActionNameEii)(xlink2::IUser **__hidden this, int, int);
  __int64 (__fastcall *_ZN2Lp3Sys10XLinkIUser13captureScreenEPKc)(xlink2::IUser **__hidden this, const char *);
  float (__fastcall *getSortKey)(xlink2::IUser *, const sead::Vector3 *);
  __int64 (__fastcall *_ZNK2Lp3Sys10XLinkIUser21getAutoInputMtxSourceEv)(xlink2::IUser **__hidden this);
  __int64 (__fastcall *_ZNK6xlink25IUser24getMtxCorrectingDrawBoneEv)(xlink2::IUser *__hidden this);
};

/* 16066 */
struct __attribute__((aligned(8))) struct_v20
{
  void *field_0;
  _BYTE field_8;
  _QWORD field_10;
  _DWORD field_18;
  __attribute__((aligned(8))) __int16 field_20;
  __int16 field_22;
};

/* 15139 */
struct __attribute__((aligned(8))) xlink2::Handle
{
  xlink2::Event *mEvent;
  _DWORD mEventId;
};

/* 15318 */
struct __attribute__((aligned(8))) xlink2::ModelTriggerConnection
{
  xlink2::BoneMtx mRootMatrix;
  xlink2::Handle mHandle;
  __int16 mGlobalPropertyIdx;
  char field_22;
  char field_23;
};

/* 5245 */
struct __attribute__((aligned(8))) xlink2::TriggerCtrl
{
  xlink2::TriggerCtrl_vtbl *__vftable /*VFT*/;
  xlink2::UserInstance *mUserInstance;
  sead::BufferOfxlink2::ModelTriggerConnection *mModelTriggerConnections;
};

/* 14501 */
struct /*VFT*/ sead::SafeStringBase_vtbl
{
  void (__cdecl *dtor)(sead::SafeStringBase *);
  void (__cdecl *dtor2)(sead::SafeStringBase *);
  void (__cdecl *operatorEq)(sead::SafeStringBase *, sead::SafeStringBase *);
  void (__thiscall *assureTerminationImpl_)(const sead::SafeStringBase *);
};

/* 14578 */
struct /*VFT*/ __attribute__((aligned(8))) sead::IDisposer_vtbl
{
  void (__fastcall *dtor1)(sead::IDisposer *this);
  void (__fastcall *dtor2)(sead::IDisposer *this);
};

/* 16047 */
enum xlink2::AssetParamType
{
  xlink2_AssetParamType_Int = 0x0,
  xlink2_AssetParamType_Float = 0x1,
  xlink2_AssetParamType_Bool = 0x2,
  xlink2_AssetParamType_String = 0x4,
  xlink2_AssetParamType_5 = 0x5,
};

/* 15287 */
struct xlink2::ParamDefine
{
  u32 mName;
  xlink2::AssetParamType mType;
  u32 mDefaultValue;
};

/* 15144 */
struct /*VFT*/ xlink2::Locator_vtbl
{
  xlink2::Locator *(__fastcall *reset)(xlink2::Locator *result);
  _QWORD (__cdecl *_ZN6xlink27Locator14setTriggerInfoENS_11TriggerTypeEPNS_24ResTriggerOverwriteParamENS_7BoneMtxE)(xlink2::Locator *__hidden this, xlink2::TriggerType, xlink2::ResTriggerOverwriteParam *, xlink2::BoneMtx);
  xlink2::TriggerType (__fastcall *getTriggerType)(const xlink2::Locator *__hidden this);
  xlink2::ResTriggerOverwriteParam *(__fastcall *getTriggerOverwriteParam)(const xlink2::Locator *__hidden this);
  xlink2::BoneMtx (__fastcall *getOverwriteBoneMtx)(const xlink2::Locator *__hidden this);
};

/* 15111 */
struct __attribute__((aligned(4))) xlink2::ResAssetCallTable
{
  uint mKeyNamePos;
  __int16 mAssetId;
  u16 mFlag;
  int mDuration;
  uint mParentIndex;
  __int16 mEnumIndex;
  char mIsSolved;
  int mKeyNameHash;
  unsigned int mParamStartPos;
  uint mConditionPos;
};

/* 15110 */
struct /*VFT*/ xlink2::Event_vtbl
{
  __int64 (__fastcall *dtor1)(xlink2::Event *__hidden this);
  __int64 (__fastcall *dtor2)(xlink2::Event *__hidden this);
  bool (__fastcall *initializeImpl_)(xlink2::Event *__hidden this);
  __int64 (__fastcall *doFinalize_)(xlink2::Event *__hidden this);
  __int64 (__fastcall *callEventCreateCallback_)(xlink2::Event *__hidden this);
  __int64 (__fastcall *callEventDestroyCallback_)(xlink2::Event *__hidden this);
  __int64 (__fastcall *fixDelayParam_)(xlink2::Event *__hidden this);
};

/* 15141 */
struct xlink2::ResTriggerOverwriteParam
{
  u32 mMask;
  u32 mReferences[];
};

/* 16717 */
union ContainerAssetExeuctorUnion
{
  xlink2::ContainerBase *mContainer;
  xlink2::AssetExecutor *mAssetExecutor;
};

/* 5240 */
struct __attribute__((packed)) __attribute__((aligned(4))) xlink2::ContainerBase
{
  xlink2::ContainerBase_vtbl *__vftable /*VFT*/;
  const xlink2::ResAssetCallTable *mResAssetCallTable;
  xlink2::Event *mEvent;
  ContainerAssetExeuctorUnion mCurrent;
  xlink2::ContainerBase *mNextContainer;
  int mDurationCountdown;
};

/* 5001 */
struct __attribute__((aligned(8))) aal::SoundParam
{
  _QWORD __vftable;
  float mVolume;
  float mVolumeByDevice[1];
  float mBusVolumeByDevice[1];
  float field_14;
  float field_18;
  float field_1C;
  float mPitch;
  float mLfe;
  float mLpf;
  int mBiquadType;
  float mBiquadValue;
  int mAngle;
  float mSpread;
};

/* 14610 */
typedef unsigned __int64 ulong;

/* 5098 */
struct __attribute__((aligned(8))) aal::SpatialCalculator::Setting
{
  sead::Matrix34 *field_0;
  const sead::Vector3 *mVelocity;
  _QWORD mAttenuator;
  float mDopplerFactor;
  float mSoundSourceSize;
  aal::Shape *mShape;
  _WORD field_28;
  ushort mListenerBitFlag;
  ulong mUserParam;
};

/* 5104 */
struct __attribute__((aligned(8))) aal::SpatialSetting
{
  _QWORD __vftable;
  sead::Matrix34 mActorMtx;
  sead::Vector3 mVelocity;
  bool mPositioned;
  bool mPositionFollow;
  _BYTE field_46;
  aal::SpatialCalculator::Setting mCalculator;
};

/* 4997 */
struct __attribute__((aligned(8))) aal::Emitter
{
  _QWORD __vftable;
  bool mInitialized;
  aal::SoundParam mParam;
  sead::OffsetList *mSoundSourceList;
  sead::CriticalSection field_58;
  _QWORD qword98;
  _QWORD qwordA0;
  aal::SpatialSetting mSpacialSetting;
  _QWORD qword128;
  _QWORD qword130;
  int field_138;
  char field_13C;
  sead::SafeStringBase *mName;
};

/* 15117 */
struct /*VFT*/ xlink2::UserResource_vtbl
{
  __int64 (__fastcall *field_0)(xlink2::UserResourceELink *__hidden this);
  __int64 (__fastcall *_ZN6xlink217UserResourceELinkD0Ev)(xlink2::UserResource *__hidden this);
  xlink2::ResourceAccessor *(__fastcall *getAccessor)(xlink2::UserResource *__hidden this);
  xlink2::ResourceAccessor *(__fastcall *getAccessorPtr)(xlink2::UserResource *__hidden this);
  xlink2::System *(__fastcall *getSystem)(xlink2::UserResource *__hidden this);
  xlink2::UserResourceParam *(__fastcall *allocResourceParam_)(xlink2::UserResource *__hidden this, sead::Heap *);
  void (__fastcall *freeResourceParam_)(xlink2::UserResource *, xlink2::UserResourceParam *);
  __int64 (__fastcall *onSetupResourceParam_)(xlink2::UserResource *, xlink2::UserResourceParam *, const xlink2::ParamDefineTable *, sead::Heap *);
};

/* 15120 */
struct __attribute__((aligned(8))) xlink2::UserBinParam
{
  xlink2::ResUserHeader *mResUserHeader;
  uint *mLocalPropertyRefArry;
  xlink2::ResParam *mUserParamArry;
  u16 *mSortedAssetIdTable;
  xlink2::ResAssetCallTable *mAssetCallTable;
  _DWORD mContainerTableLower;
  xlink2::ResActionSlot *mResActionSlotTable;
  xlink2::ResAction *mActionTable;
  const xlink2::ResActionTrigger *mActionTriggerTable;
  xlink2::ResProperty *mPropertyTable;
  xlink2::ResPropertyTrigger *mResPropertyTriggerTable;
  xlink2::ResAlwaysTrigger *mResAlwaysTriggerTable;
};

/* 14941 */
typedef unsigned __int8 uchar;

/* 16059 */
struct sead::BufferOfuchar
{
  s32 mCount;
  uchar *mBuffer;
};

/* 15367 */
struct sead::BufferOfxlink2::ResCallTable
{
  u32 mCount;
  xlink2::ResCallTable *mBuffer;
};

/* 16058 */
struct sead::BufferOfBool
{
  s32 mCount;
  bool *mBuffer;
};

/* 15118 */
struct __attribute__((aligned(8))) xlink2::UserResourceParam
{
  const xlink2::CommonResourceParam *mCommonResourceParam;
  xlink2::UserBinParam mUserBinParam;
  sead::BufferOfuchar mPropertyNameIndexToPropertyIndex;
  sead::BufferOfxlink2::ResCallTable mCallTableArry;
  sead::BufferOfBool mActionTriggerBools;
  ulong mPropertyAssignedBitfield;
  xlink2::ResourceAccessor *field_A0;
  bool mSetup;
};

/* 7466 */
struct sead::Camera
{
  sead::Camera_vtbl *__vftable /*VFT*/;
  sead::Matrix34 mMatrix;
};

/* 16679 */
struct /*VFT*/ xlink2::TriggerCtrl_vtbl
{
  void (__cdecl *calc)(xlink2::TriggerCtrl *);
  void (__cdecl *dtor1)(xlink2::TriggerCtrl *);
  void (__cdecl *dtor2)(xlink2::TriggerCtrl *);
};

/* 15113 */
struct /*VFT*/ xlink2::ContainerBase_vtbl
{
  __int64 (__fastcall *dtor1)(xlink2::ContainerBase *__hidden this);
  __int64 (__fastcall *dtor2)(xlink2::SequenceContainer *__hidden this);
  int (__cdecl *initialize)(xlink2::ContainerBase *this, const xlink2::Event *, const xlink2::ResAssetCallTable *);
  __int64 (__fastcall *destroy)(xlink2::ContainerBase *__hidden this);
  bool (__fastcall *start)(xlink2::ContainerBase *__hidden this);
  bool (__fastcall *calc)(xlink2::ContainerBase *__hidden this);
  __int64 (__fastcall *fadeBySystem)(xlink2::ContainerBase *__hidden this);
  __int64 (__fastcall *fade)(xlink2::ContainerBase *__hidden this, int);
  __int64 (__fastcall *kill)(xlink2::ContainerBase *__hidden this);
  bool (__fastcall *killOneTimeEvent)(xlink2::ContainerBase *__hidden this);
};

/* 5234 */
struct __attribute__((aligned(8))) xlink2::AssetExecutor
{
  xlink2::AssetExecutor_vtbl *__vftable /*VFT*/;
  xlink2::ResAssetCallTable *field_8;
  __int64 field_10;
  xlink2::Event *field_18;
  xlink2::UserInstance *mUserInstance;
  const xlink2::ResAssetCallTable *mAssetCallTable;
  _DWORD field_30;
  float field_34;
  xlink2::ResTriggerOverwriteParam *mTriggerOverwriteParam;
  xlink2::BoneMtx mBoneMtx;
};

/* 5073 */
struct __attribute__((aligned(8))) aal::NamedObj
{
  aal::NamedObj_vtbl *__vftable /*VFT*/;
  sead::SafeStringBase mName;
};

/* 5096 */
struct aal::IUnifiable
{
  aal::IUnifiable_vtbl *__vftable /*VFT*/;
};

/* 15530 */
enum aal::ShapeParamBitfield : unsigned __int8
{
  aal_ShapeParamBitfield_SetBasePositionByActor = 0x1,
  aal_ShapeParamBitfield_RotateByActor = 0x2,
  aal_ShapeParamBitfield_UseCameraMtxForAngle = 0x4,
};

/* 5135 */
struct __cppobj aal::Shape : aal::NamedObj
{
  aal::IUnifiable mUnifiable;
  char char20;
  __attribute__((aligned(16))) _QWORD qword30;
  _BYTE gap38[24];
  _QWORD qword50;
  _BYTE gap58[24];
  _QWORD qword70;
  _BYTE gap78[24];
  _QWORD qword90;
  __attribute__((aligned(16))) __int64 nodeThunk;
  _QWORD qwordA8;
  _QWORD qwordB0;
  sead::Matrix34 field_B8;
  sead::Vector3 mOffset;
  aal::ShapeParamBitfield mTypeBitfield;
  sead::OffsetList mSpacialCalcList;
  sead::CriticalSection mMutex;
};

/* 5208 */
struct __attribute__((aligned(8))) xlink2::ResourceAccessor
{
  xlink2::ResourceAccessor_vtbl *__vftable /*VFT*/;
  xlink2::ResUserHeader *mResUserHeader;
  xlink2::UserResource *mUserResource;
  xlink2::System *mSystem;
};

/* 5207 */
struct __cppobj xlink2::ResourceAccessorELink : xlink2::ResourceAccessor
{
};

/* 5209 */
struct __cppobj xlink2::UserResourceELink : xlink2::UserResource
{
  _BYTE field_28;
  xlink2::ResourceAccessorELink mResourceAccessor;
};

/* 4567 */
struct __attribute__((aligned(4))) sead::Random
{
  uint mCtx[4];
};

/* 5226 */
struct __attribute__((aligned(8))) xlink2::DebugOperationParam
{
  _DWORD field_0;
  float field_4;
  float field_8;
  _DWORD field_C;
  _DWORD field_10;
  _DWORD field_14;
  _DWORD field_18;
  _DWORD field_1C;
  sead::FixedSafeString64 field_20;
  sead::FixedSafeString64 field_78;
  sead::FixedSafeString64 field_D0;
  sead::FixedSafeString128 field_128;
  sead::FixedSafeString128 field_1C0;
  int field_258;
  sead::FixedSafeString64 field_260;
  int field_2B8;
  __int16 field_2BC;
  sead::FixedSafeString128 field_2C0;
};

/* 5216 */
struct __attribute__((aligned(8))) xlink2::System
{
  xlink2::System_vtbl *__vftable /*VFT*/;
  xlink2::ResourceBuffer *mResourceBuffer;
  sead::OffsetList mUserList;
  int field_28;
  int mEventPoolNum;
  _DWORD field_30;
  _DWORD mCurrEventId;
  _BYTE field_38;
  uint mMaxGlobalPropertyValues;
  const xlink2::PropertyDefinition **mGlobalPropertyDefinitions;
  float *mGlobalPropertyValues;
  ulong mGlobalPropertyValueUsedBitfield;
  _BYTE field_58;
  xlink2::ErrorMgr *mErrorMgr;
  xlink2::HoldMgr *mHoldMgr;
  _DWORD field_70;
  bool mCallEnable;
  sead::Heap *mUserHeap;
  float field_80;
  sead::PtrArrayImpl mGlobalPropertyTriggerUserList;
  sead::Random mRnd;
  sead::UnitHeap *mXLinkContainerHeap;
  sead::UnitHeap *mXLinkAssetExecutorHeap;
  sead::Heap *mPrimaryHeap;
  xlink2::EditorBuffer *mEditorBuffer;
  _DWORD mTick;
  float dwordCC;
  __int64 field_D0;
  float field_D8;
  int field_DC;
  int field_E0;
  int field_E4;
  _QWORD field_E8;
  _QWORD field_F0;
  int field_F8;
  xlink2::DebugOperationParam field_100;
  xlink2::DebugOperationParam field_458;
  char field_7B0;
  int field_7B4;
  int field_7B8;
  __int64 field_7C0;
  xlink2::UserInstance *mDrawTargetInstance;
  char field_7D0;
};

/* 15119 */
struct __attribute__((aligned(8))) xlink2::CommonResourceParam
{
  int mNumResParam;
  int mNumResAssetParam;
  int mNumResTriggerOverwriteParam;
  int mNumLocalPropertyNameRefTable;
  int mNumLocalPropertyEnumNameRefTable;
  int mNumDirectValueTable;
  int mNumRandomTable;
  int mNumCurveTable;
  int mNumCurvePointTable;
  xlink2::ResAssetParamTable *mResAssetParamTable;
  int mTriggerOverwriteParamTableLower;
  uint *mLocalPropertyNameRefTable;
  uint *mLocalPropertyEnumNameRefTable;
  uint *mDirectValueTable;
  xlink2::ResRandomCallTable *mRandomTable;
  xlink2::ResCurveCallTable *mCurveTable;
  xlink2::CurvePointTable *mCurvePointTable;
  int mConditionTableLower;
  int mExRegionLower;
  _DWORD mNameTableLower;
};

/* 14372 */
struct __attribute__((aligned(4))) xlink2::ResUserHeader
{
  unsigned int mIsSetup;
  unsigned int mNumLocalProperty;
  unsigned int mNumCallTable;
  uint mNumAsset;
  unsigned int mNumRandomContainer;
  unsigned int mNumResActionSlot;
  unsigned int mNumResAction;
  unsigned int mNumResActionTrigger;
  unsigned int mNumResProperty;
  unsigned int mNumResPropertyTrigger;
  unsigned int mNumResAlwaysTrigger;
  unsigned int mTriggerTablePos;
};

/* 15115 */
struct __attribute__((packed)) xlink2::ResParam
{
  unsigned __int8 mType : 8;
  __int32 mValue : 24;
};

/* 15291 */
struct __attribute__((aligned(4))) xlink2::ResActionSlot
{
  int mName;
  ushort mActionStartIdx;
  __int16 mActionEndIdx;
};

/* 15290 */
struct __attribute__((aligned(4))) xlink2::ResAction
{
  int mName;
  int mTriggerStartIdx;
  int mTriggerEndIdx;
};

/* 15121 */
struct xlink2::ResActionTrigger
{
  uint mGuId;
  uint mAssetCtbPos;
  uint mStartFrame;
  uint mEndFrame;
  ushort mFlag;
  __int16 mOverwriteHash;
  int mOverwriteParamPos;
};

/* 15289 */
struct xlink2::ResProperty
{
  u32 mWatchPropertyNamePos;
  u32 mIsGlobal;
  u32 mTriggerStartIdx;
  u32 mTriggerEndIdx;
};

/* 15294 */
struct xlink2::ResPropertyTrigger
{
  unsigned int mGuId;
  unsigned int mAssetCtbPos;
  unsigned int mCondition;
  unsigned __int16 mFlag;
  __int16 mOverwriteHash;
  unsigned int mOverwritePos;
};

/* 15295 */
struct xlink2::ResAlwaysTrigger
{
  unsigned int mGuId;
  unsigned int mAssetCtb;
  unsigned __int16 mFlag;
  __int16 mOverwriteHash;
  unsigned int mOverwriteParamPos;
};

/* 15292 */
struct xlink2::ResCallTable
{
  ushort mEnumValue;
  uchar mFlags;
  char field_3;
};

/* 14581 */
struct __cppobj /*VFT*/ sead::RuntimeTypeInfo::Interface_vtbl
{
  bool (__cdecl *checkDerivedRuntimeTypeInfo)(sead::RuntimeTypeInfo::Interface *, sead::RuntimeTypeInfo::Interface *const);
  void *(__cdecl *getRuntimeTypeInfo)(sead::RuntimeTypeInfo::Interface *);
};

/* 14982 */
struct __cppobj sead::Camera_vtbl : sead::RuntimeTypeInfo::Interface_vtbl
{
  void (__cdecl *dtor1)(sead::Camera *);
  void (__cdecl *dtor2)(sead::Camera *);
  void (__cdecl *doUpdateMatrix)(sead::Camera *, sead::Matrix34 *);
};

/* 7531 */
struct __cppobj __attribute__((aligned(4))) xlink2::SequenceContainer : xlink2::ContainerBase
{
  int mSequenceIndex;
};

/* 15369 */
struct /*VFT*/ xlink2::AssetExecutor_vtbl
{
  __int64 (__fastcall *field_0)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *_ZN6xlink218AssetExecutorELinkD0Ev)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *calc)(xlink2::AssetExecutor *this);
  bool (__fastcall *isAssetValid)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *fade)(xlink2::AssetExecutor *__hidden this, int);
  bool (__fastcall *kill)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *requestReEmit)(xlink2::AssetExecutor *__hidden this, bool);
  bool (__fastcall *isRequestReEmit)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *fadeBySystem)(xlink2::AssetExecutor *__hidden this);
  bool (__fastcall *isLoopEvent)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *_ZN6xlink218AssetExecutorELink14dumpDebugPrintEv)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *activateImpl_)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *onDestroy_)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *onResetOverwriteParam_)(xlink2::AssetExecutor *__hidden this);
  __int64 (__fastcall *_ZN6xlink218AssetExecutorELink11onFinalize_Ev)(xlink2::AssetExecutor *__hidden this);
};

/* 15517 */
struct /*VFT*/ aal::NamedObj_vtbl
{
  void (__cdecl *dtor1)(aal::NamedObj *);
  void (__cdecl *dtor2)(aal::NamedObj *);
  void (__cdecl *setObjName)(aal::NamedObj *, const sead::SafeStringBase *);
};

/* 15513 */
struct /*VFT*/ aal::IUnifiable_vtbl
{
  void (__cdecl *dtor1)(aal::IUnifiable *);
  void (__cdecl *dtor2)(aal::IUnifiable *);
  void *(__cdecl *calcUnifiablePosition)(aal::IUnifiable *, const aal::Listener *, sead::Vector3 *, sead::Vector3 *);
};

/* 15116 */
struct /*VFT*/ xlink2::ResourceAccessor_vtbl
{
  __int64 (__fastcall *dtor)(xlink2::ResourceAccessor *__hidden this);
  __int64 (__fastcall *_ZN6xlink221ResourceAccessorSLinkD0Ev)(xlink2::ResourceAccessor *__hidden this);
  _QWORD (__cdecl *_ZNK6xlink221ResourceAccessorSLink12isBlankAssetERKNS_17ResAssetCallTableE)(xlink2::ResourceAccessor *__hidden this, const xlink2::ResAssetCallTable *);
  const char *(__fastcall *getBoneName)(xlink2::ResourceAccessor *__hidden this, unsigned int);
  bool (__fastcall *isBoneNameOverwritten)(xlink2::ResourceAccessor *__hidden this, unsigned int);
  const char *(__fastcall *getOverwriteBoneName)(xlink2::ResourceAccessor *__hidden this, unsigned int);
  bool (__cdecl *isAutoOneTimeFade)(xlink2::ResourceAccessor *__hidden this, const xlink2::ResAssetCallTable *);
  _QWORD (__cdecl *_ZNK6xlink221ResourceAccessorSLink16isForceLoopAssetERKNS_17ResAssetCallTableE)(xlink2::ResourceAccessor *__hidden this, const xlink2::ResAssetCallTable *);
  float (__cdecl *getDelayWithOverwrite)(xlink2::ResourceAccessor *__hidden this, const xlink2::ResAssetCallTable *, unsigned int, const xlink2::UserInstance *);
  float (__cdecl *getDuration)(xlink2::ResourceAccessor *__hidden this, const xlink2::ResAssetCallTable *, const xlink2::UserInstance *);
  __int64 (__fastcall *getTriggerOverwriteParamId_)(xlink2::ResourceAccessor *__hidden this, unsigned int);
  _QWORD (__cdecl *getAssetBitFlag_)(xlink2::ResourceAccessor *__hidden this, const xlink2::ResAssetCallTable *);
};

/* 15114 */
struct /*VFT*/ xlink2::System_vtbl
{
  __int64 (__fastcall *field_0)(sead::hostio::Node *__hidden this);
  __int64 (__fastcall *_ZNK6xlink26System15drawInformationEPN4sead11DrawContextEPNS1_10TextWriterE)(xlink2::System *__hidden this, sead::DrawContext *, sead::TextWriter *);
  _QWORD (__cdecl *_ZNK6xlink26System17drawInformation3DEPN4sead11DrawContextERKNS1_6CameraERKNS1_10ProjectionERKNS1_8ViewportEf)(xlink2::System *__hidden this, sead::DrawContext *, const sead::Camera *, const sead::Projection *, const sead::Viewport *, float);
  xlink2::UserResource *(__cdecl *createUserResource)(xlink2::System *, xlink2::User *, sead::Heap *);
  __int64 (__fastcall *_ZN6xlink211SystemELink11allocHandleEPN4sead4HeapE)(xlink2::System **__hidden this, sead::Heap *);
  __int64 (__fastcall *getUserParamNum)(xlink2::System *__hidden this);
  sead::SafeStringBase *(__fastcall *getModuleName)(xlink2::System *__hidden this);
  xlink2::AssetExecutor *(__fastcall *allocAssetExecutor)(xlink2::System *__hidden this, xlink2::Event *);
  xlink2::ILockProxy *(__fastcall *getModuleLockObj)(xlink2::System *__hidden this);
  uint (__fastcall *getResourceVersion)(xlink2::System *__hidden this);
  __int64 (__fastcall *_ZN6xlink211SystemELinkD2Ev)(xlink2::System **this);
  __int64 (__fastcall *_ZN6xlink211SystemELinkD0Ev)(xlink2::System **this);
  xlink2::Event *(__fastcall *getEventFromPool_)(xlink2::System *__hidden this, unsigned int);
  __int64 (__fastcall *_ZNK6xlink211SystemELink19preDrawInformation_EPN4sead10TextWriterE)(xlink2::System **__hidden this, sead::TextWriter *);
  __int64 (__fastcall *_ZNK6xlink211SystemELink20postDrawInformation_EPN4sead10TextWriterE)(xlink2::System **__hidden this, sead::TextWriter *);
  __int64 (__fastcall *_ZNK6xlink211SystemELink28drawInformationSystemDetail_EPN4sead10TextWriterE)(xlink2::System **__hidden this, sead::TextWriter *);
  __int64 (__fastcall *_ZNK6xlink211SystemELink21drawInformationEvent_EPN4sead10TextWriterE)(xlink2::System **__hidden this, sead::TextWriter *);
  _QWORD (__cdecl *_ZNK6xlink26System23drawInformationEmitter_EPNS_12UserInstanceEPN4sead11DrawContextEPNS3_10TextWriterERKNS3_6CameraERKNS3_10ProjectionERKNS3_8ViewportE)(xlink2::System *__hidden this, xlink2::UserInstance *, sead::DrawContext *, sead::TextWriter *, const sead::Camera *, const sead::Projection *, const sead::Viewport *);
};

/* 14370 */
struct __cppobj __attribute__((aligned(4))) xlink2::RomResourceParam : xlink2::CommonResourceParam
{
  _QWORD mDataPtr;
  uint *mUserDataHashes;
  uint *mUserOffsets;
  int mNumUser;
  bool mSetup;
};

/* 5244 */
struct __attribute__((aligned(8))) xlink2::ResourceBuffer
{
  _QWORD __vftable;
  xlink2::RomResourceParam mRomResourceParam;
  xlink2::ParamDefineTable mParamDefineTable;
};

/* 16070 */
struct __cppobj sead::FixedSafeString320 : sead::BufferedSafeStringBase
{
  char mData[320];
};

/* 14466 */
struct __cppobj __attribute__((aligned(8))) sead::FixedSafeString256 : sead::BufferedSafeStringBase
{
  char mData[256];
};

/* 16069 */
struct __attribute__((aligned(8))) struct_v3_3
{
  int field_0;
  __attribute__((aligned(8))) sead::FixedSafeString320 mUserName;
  __attribute__((aligned(8))) sead::FixedSafeString256 mMessage;
  __attribute__((aligned(8))) int field_278;
};

/* 5241 */
struct __attribute__((aligned(8))) xlink2::ErrorMgr
{
  int field_0;
  struct_v3_3 field_8[32];
  int mErrorDispFrame;
  _QWORD field_5010;
  const xlink2::System *mSystem;
  int field_5020[4];
  int field_5030[40];
  sead::CriticalSection field_50D0;
};

/* 15249 */
struct sead::FreeList
{
  sead::FreeList::Node *mFree;
  void *mWork;
};

/* 15252 */
struct __cppobj sead::ObjList : sead::ListImpl
{
  sead::FreeList mFreeList;
  s32 mMaxNum;
};

/* 16012 */
struct xlink2::HoldMgr::HoldAssetInfo
{
  xlink2::Handle mHandle;
  xlink2::UserInstance *mUserInstance;
  int field_18;
  sead::ListNode mListNode;
};

/* 7529 */
struct __attribute__((aligned(8))) xlink2::HoldMgr
{
  _QWORD __vftable;
  xlink2::System *mSystem;
  sead::CriticalSection mMutex;
  sead::ObjList mHoldAssetInfoList;
  xlink2::HoldMgr::HoldAssetInfo field_80[128];
  _BYTE field_1880;
};

/* 5941 */
struct __cppobj sead::UnitHeap : sead::Heap
{
  _QWORD qwordE0;
  _QWORD qwordE8;
  _QWORD qwordF0;
  _QWORD qwordF8;
  _QWORD qword100;
};

/* 5243 */
struct __attribute__((aligned(8))) xlink2::EditorBuffer
{
  _QWORD __vftable;
  xlink2::System *mSystem;
  sead::Heap *mHeap;
  sead::OffsetList mEditorResourceParamList;
  uchar *field_30;
  _DWORD field_38;
  sead::FixedSafeString64 field_40;
  xlink2::ParamDefineTable *mParamDefineTable;
  xlink2::ParamDefineTableHeader *field_A0;
};

/* 15300 */
struct xlink2::ResAssetParamTable
{
  u64 mMask;
  u32 mReferences[];
};

/* 15298 */
struct xlink2::ResRandomCallTable
{
  float mMinValue;
  float mMaxValue;
};

/* 16041 */
struct xlink2::ResCurveCallTable
{
  ushort mCurvePointStartPos;
  ushort mNumPoint;
  ushort mCurveType;
  ushort mIsPropGlobal;
  uint mPropName;
  int mPropIdx;
  ushort mLocalPropertyNameIdx;
  ushort mPadding;
};

/* 15299 */
struct xlink2::CurvePointTable
{
  float mX;
  float mY;
};

/* 14580 */
struct sead::RuntimeTypeInfo::Interface
{
  sead::RuntimeTypeInfo::Interface_vtbl *__vftable /*VFT*/;
};

/* 14459 */
struct __cppobj sead::FixedSafeString32 : sead::BufferedSafeStringBase
{
  char mData[32];
  u32 t;
};

/* 15528 */
struct __cppobj aal::FixedNamedObj32 : aal::NamedObj
{
  sead::FixedSafeString32 mFixedStr;
};

/* 5092 */
struct __attribute__((aligned(8))) aal::Cone
{
  _QWORD __vftable;
  sead::Matrix34 field_8;
  float field_38;
  float field_3C;
  float field_40;
  float field_44;
  float field_48;
  float field_4C;
};

/* 5070 */
struct __attribute__((aligned(8))) aal::ListenerDirectivity
{
  _QWORD __vftable;
  _BYTE field_8;
  aal::Cone mCone;
  float field_60;
  float field_64;
  float field_68;
  float field_6C;
  float field_70;
  float field_74;
  _BYTE field_78;
};

/* 5072 */
struct aal::ListenerPoser;

/* 5069 */
struct __cppobj __attribute__((aligned(8))) aal::Listener : aal::FixedNamedObj32
{
  _QWORD thunk;
  float mVolume;
  float mDeviceVolume[1];
  float mLpf;
  float mBiquadValue;
  aal::ListenerDirectivity mDirectivity;
  _BYTE field_E8;
  float m2DPanPower;
  _BYTE field_F0;
  aal::ListenerPoser *mPoser;
  sead::Matrix34 field_100;
  sead::Matrix34 mListenerMtx;
  sead::Matrix34 field_160;
  float field_190;
  float field_194;
  float field_198;
  sead::Vector3 mVelocity;
  _BYTE field_1A8;
  _DWORD field_1AC;
};

/* 198 */
struct sead::hostio::Node
{
  sead::hostio::Node_vtbl *__vftable /*VFT*/;
};

/* 14414 */
struct $59B84E82DB0FC8318FFA33E972FC0CD9
{
  char _x0[160];
};

/* 14415 */
typedef struct $59B84E82DB0FC8318FFA33E972FC0CD9 NVNcommandBuffer;

/* 16729 */
struct nn::gfx::detail::CommandBufferImpl
{
  NVNcommandBuffer mImpl;
  __int64 field_A0;
  __int64 field_A8;
  __int64 field_B0;
  NVNcommandBuffer *field_B8;
  __int64 field_C0;
  __int64 field_C8;
  __int64 field_D0;
  __int64 field_D8;
  __int64 field_E0;
};

/* 4505 */
struct __attribute__((aligned(8))) sead::DrawContext
{
  _QWORD __vftable;
  nn::gfx::detail::CommandBufferImpl mCommandBuffer;
};

/* 14369 */
struct sead::Vector2
{
  float x;
  float y;
};

/* 4555 */
struct sead::Color4f
{
  float r;
  float g;
  float b;
  float a;
};

/* 14997 */
struct __attribute__((aligned(4))) sead::BoundBox2
{
  sead::Vector2 mMin;
  sead::Vector2 mMax;
};

/* 4566 */
struct __attribute__((aligned(8))) sead::TextWriter
{
  __int64 __vftable;
  sead::Viewport *mViewport;
  sead::Projection *mProjection;
  sead::Camera *mCamera;
  sead::FontBase *mFont;
  sead::Vector2 mCursor;
  sead::Vector2 mScale;
  sead::Color4f mColor;
  sead::BoundBox2 field_48;
  float field_58;
  int field_5C;
  char16_t *mFormatBuffer;
  int mFormatBufferLength;
  bool mDoFontBeginEnd;
  sead::DrawContext *mDrawCtx;
};

/* 14687 */
struct sead::Matrix44
{
  float mData[4][4];
};

/* 4560 */
struct __cppobj sead::Projection
{
  sead::Projection_vtbl *__vftable /*VFT*/;
  bool mDirty;
  bool mDeviceDirty;
  sead::Matrix44 mMatrix;
  sead::Matrix44 mDeviceMatrix;
  int mDevicePosture;
  float mDeviceZScale;
  float mDeviceZOffset;
};

/* 2717 */
struct __attribute__((aligned(8))) sead::Viewport
{
  uint __vftable;
  __attribute__((aligned(8))) float mMinX;
  float mMinY;
  float mMaxX;
  float mMaxY;
  _DWORD mDevicePosture;
};

/* 5452 */
struct xlink2::ILockProxy
{
  xlink2::ILockProxy_vtbl *__vftable /*VFT*/;
};

/* 15248 */
struct sead::FreeList::Node
{
  sead::FreeList::Node *mNext;
};

/* 16061 */
struct xlink2::ParamDefineTableHeader
{
  _DWORD mTotalSize;
  unsigned int mNumTotalUserParams;
  unsigned int mNumTotalAssetParams;
  _DWORD mNumUserAssetParams;
  _DWORD mNumTriggerParams;
  xlink2::ParamDefine mParams[];
};

/* 14589 */
struct /*VFT*/ sead::hostio::Node_vtbl
{
  void *(__cdecl *getNodeClassType)(sead::hostio::Node *);
};

/* 14425 */
struct NVNprogram
{
  char data[192];
};

/* 14424 */
struct NVNtexture
{
  char data[192];
};

/* 14427 */
struct NVNmemoryPool
{
  char data[256];
};

/* 14426 */
struct NVNbuffer
{
  char data[48];
};

/* 4565 */
struct sead::FontBase
{
  sead::FontBase_vtbl *__vftable /*VFT*/;
  sead::IDisposer mDisposer;
  NVNprogram mProgram;
  NVNtexture mTexture;
  _QWORD mTextureHandle;
  NVNmemoryPool mTexMemPool;
  NVNmemoryPool mShaderMemPool;
  NVNmemoryPool mWorkingMemPool;
  NVNbuffer mShaderBuffer;
};

/* 16631 */
struct /*VFT*/ sead::Projection_vtbl
{
  void (__cdecl *dtor1)(sead::Projection *__hidden this);
  void (__cdecl *dtor2)(sead::Projection *__hidden this);
  float (__cdecl *getNear)(sead::Projection *__hidden this);
  float (__cdecl *getFar)(sead::Projection *__hidden this);
  float (__cdecl *getFovy)(sead::Projection *__hidden this);
  float (__cdecl *getAspect)(sead::Projection *__hidden this);
  void (__cdecl *getOffset)(sead::Projection *__hidden this, sead::Vector2 *offset);
  void (__cdecl *updateAttributesForDirectProjection)(sead::Projection *__hidden this);
  u32 (__cdecl *getProjectionType)(sead::Projection *__hidden this);
  void (__cdecl *doUpdateMatrix)(sead::Projection *__hidden this, sead::Matrix44 *mtx);
  void (__cdecl *doUpdateDeviceMatrix)(sead::Projection *__hidden this, sead::Matrix44 *, const sead::Matrix44 *, int);
  void (__cdecl *doScreenPosToCameraPosTo)(sead::Projection *__hidden this, sead::Vector3 *, const sead::Vector3f *);
};

/* 15109 */
struct __attribute__((aligned(8))) xlink2::ILockProxy_vtbl
{
  void *dtor1;
  void *dtor2;
  void (__fastcall *lock)(xlink2::ILockProxy *);
  void (__fastcall *unlock)(xlink2::ILockProxy *);
};

/* 14999 */
struct /*VFT*/ sead::FontBase_vtbl
{
  __int64 (__fastcall *field_0)(sead::FontBase *__hidden this);
  __int64 (__fastcall *_ZN4sead19DebugFontMgrJis1NvnD0Ev)(sead::FontBase *__hidden this);
  float (__fastcall *getHeight)(sead::FontBase *__hidden this);
  float (__fastcall *getWidth)(sead::FontBase *__hidden this);
  float (__fastcall *getCharWidth)(sead::FontBase *__hidden this, char16_t);
  __int64 (__fastcall *_ZNK4sead19DebugFontMgrJis1Nvn11getEncodingEv)(sead::FontBase *__hidden this);
  __int64 (__fastcall *getMaxDrawNum)(sead::FontBase *__hidden this);
  sead::DebugFontMgrJis1Nvn *(__fastcall *begin)(sead::FontBase *result, sead::DrawContext *a2);
  _QWORD (__cdecl *end)(sead::FontBase *__hidden this, sead::DrawContext *);
  sead::DebugFontMgrJis1Nvn *(__fastcall *print)(sead::FontBase *this, sead::DrawContext *, const sead::Projection *, const sead::Camera *, const sead::Matrix34 *, const sead::Color4f *, const void *, int);
};

/* 14360 */
struct sead::Vector3f
{
  float x;
  float y;
  float z;
};

/* 4500 */
struct __cppobj sead::DebugFontMgrJis1Nvn : sead::FontBase
{
  unsigned int mTableLength;
  _DWORD field_4E4;
  _QWORD mTablePtr;
  NVNbuffer nvnBuffer;
  _QWORD buffer;
  _DWORD field_528;
  _DWORD field_52C;
  _BYTE field_530;
};

