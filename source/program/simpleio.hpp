#pragma once

#include "lib.hpp"

static_assert(sizeof(long int) == 0x8);
void OutputDebug(const char *path, const char *output, bool new_line = true);

void ReadFileFixed(const char *path, void *in_out_file, u32 size);

void OutputFile(const char *path, void *output, size_t output_len);


#define RESULT_ASSERT_PRINT(expression, output) \
    { \
        const u32 result = (expression); \
        if (result != 0) { \
            ::OutputDebug("sd:/result_assert.txt", output); \
        } \
    }
#define ASSERT_PRINT(expression, output) \
    { \
        const u32 result = (expression); \
        if (result == false) { \
            ::OutputDebug("sd:/assert_assert.txt", output); \
        } \
    }
