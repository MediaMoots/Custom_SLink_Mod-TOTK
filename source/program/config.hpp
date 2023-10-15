#pragma once 

#include "xlink.hpp"

// To Find VtableHookOffset - Search for GameSound

// SLink Offsets -  All
static constexpr int s_SLinkInstanceOffset_v100 = 0x0463f758;
static constexpr int s_SLinkInstanceOffset_v110 = 0x0471cc98;
static constexpr int s_SLinkInstanceOffset_v111 = 0x04724bb8;
static constexpr int s_SLinkInstanceOffset_v112 = 0x04717098;
static constexpr int s_SLinkInstanceOffset_v120 = 0x0470b4f8;
static constexpr int s_SLinkInstanceOffset_v121 = 0x0471a578;

static constexpr int s_RootCallbackOffset_v100 = 0x11D8;
static constexpr int s_RootCallbackOffset_v110 = 0x11D8;
static constexpr int s_RootCallbackOffset_v111 = 0x11D8;
static constexpr int s_RootCallbackOffset_v112 = 0x11D8;
static constexpr int s_RootCallbackOffset_v120 = 0x11D8;
static constexpr int s_RootCallbackOffset_v121 = 0x11D8;

static constexpr int s_VtableHookOffset_v100 = 0x042f9aa8;
static constexpr int s_VtableHookOffset_v110 = 0x043c92c0;
static constexpr int s_VtableHookOffset_v111 = 0x043d1238;
static constexpr int s_VtableHookOffset_v112 = 0x043c33e8;
static constexpr int s_VtableHookOffset_v120 = 0x043b77d8;
static constexpr int s_VtableHookOffset_v121 = 0x043C67D8;

// Function Offsets - All
static constexpr int s_searchAssetCallTableByNameOffsets[] = {
                0x00ac1d28, // 1.0.0
                0x00b27f54, // 1.1.0
                0x00b3bcbc, // 1.1.1
                0x00b1a49c, // 1.1.2
                0x00a5e3b8, // 1.2.0
                0x00afd150, // 1.2.1
            };

static constexpr int s_searchAssetCallTableByNameInlinedOneOffsets[] = {
                0x0097a17c, // 1.0.0
                0x00809fdc, // 1.1.0
                0x00755d44, // 1.1.1
                0x00838268, // 1.1.2
                0x00968670, // 1.2.0
                0x009fff60, // 1.2.1
            };

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