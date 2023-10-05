#pragma once

#include <optional>
#include <string.h>
#include <math.h>
#include <nn.hpp>
#include <lib.hpp>
#include <string.h>

namespace exlnk
{

    namespace version
    {

        enum Type
        {
            VERSION_121 = 121
        };

        namespace
        {
            constexpr bool IsCharNumeric(char c)
            {
                return 0 <= (c - '0') && (c - '0') <= 9;
            }
        }

        constexpr bool IsValid(Type version)
        {
            return version == VERSION_121;
        }

        constexpr bool ParseVersion(Type *output, const char *string, int length)
        {
            constexpr int SegmentCount = 3;
            constexpr int SegmentSize = 2;                              /* One digit and seperator */
            constexpr int MinLength = (SegmentSize * SegmentCount) - 1; /* Last segment doesn't have a seperator after it. */
            constexpr char SeperatorChar = '.';

            /* If the string is shorter than minimum, this is invalid. */
            if ((length - 1) < MinLength)
                return false;

            int power = static_cast<int>(std::pow(10, SegmentCount - 1));
            int version = 0;
            for (int i = 0; i < SegmentCount; i++)
            {
                const char *segment = &string[i * SegmentSize];

                /* If the character isn't numeric, this is an invalid version. */
                if (!IsCharNumeric(segment[0]))
                {
                    return false;
                }

                /* If we are not on the last segment, check if there's a valid seperator char. */
                if (i != SegmentCount - 1)
                {
                    if (segment[1] != SeperatorChar)
                    {
                        return false;
                    }
                }

                /* Place in the digit with the current power. */
                version += (segment[0] - '0') * power;
                /* Move one digit down. */
                power /= 10;
            }

            *output = static_cast<Type>(version);
            return true;
        }
    }

#define PRINT(...)                                         \
    {                                                      \
        int len = snprintf(buf, sizeof(buf), __VA_ARGS__); \
        svcOutputDebugString(buf, len);                    \
    }

    inline version::Type GetVersion()
    {
        static std::optional<version::Type> cachedVersion{};
        /* If we already have a cached value, return that. */
        if (cachedVersion.has_value())
            return *cachedVersion;

        /* Try to get and parse the version from the OS. */
        version::Type version{};
        nn::oe::DisplayVersion display{};

        char buf[500];
        PRINT("Break 1");

        nn::oe::GetDisplayVersion(&display);

         PRINT(display.mData);

        if (!version::ParseVersion(&version, display.mData, strnlen(display.mData, sizeof(display.mData))))
        {
            PRINT("Break 3");
            EXL_ABORT(0x1);
        }

        PRINT("Parsing version");

        /* Cache value then return it. */
        *cachedVersion = version;
        return version;
    }

    inline bool IsSupportedVersion()
    {
        return version::IsValid(GetVersion());
    }
}