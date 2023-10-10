#pragma once 

#include "xlink.hpp"

// SLink Offsets -  1.2.1
static constexpr int s_SLinkInstanceOffset_v121 = 0x0471a578;
static constexpr int s_RootCallbackOffset_v121 = 0x11D8;
static constexpr int s_VtableHookOffset_v121 = 0x043C67D8;

// Function Offsets - 1.2.1
static constexpr int s_searchAssetCallTableByNameOffset_v121 = 0x00afd150;
static constexpr int s_searchAssetCallTableByNameInlinedOne_v121 = 0x009fff60;

// Unused Offsets
// static constexpr int s_emitImpl = 0x000afd244;
// static constexpr int s_searchAssetCallTableByNameInlinedTwo = 0x00a3aa78;
// static constexpr int s_searchAssetCallTableByNameInlinedThree = 0x00f85148;
// static constexpr int s_searchAssetCallTableByNameInlinedThreeLabel = 0x00f852c4;
// static constexpr int s_searchAssetCallTableByNameInlinedFour = 0x02295f0c;

// CSM Config
static constexpr char requiredPrefix[] = "CSM_";

// Global Variables
static xlink2::ResAssetCallTable cachedResAssetCallTable {};
static xlink2::ResAssetParam cachedResAssetParam;