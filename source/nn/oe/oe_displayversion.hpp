#pragma once

#include <nn/nn_common.hpp>

namespace nn::oe {

    struct DisplayVersion {
        char mData[0x10];
    };

    void GetDisplayVersion(DisplayVersion*);
}