#pragma once

#include "config.hpp"
#include "lib.hpp"
#include "xlink.hpp"
#include <random>

namespace csm::keynameutils
{

enum class KeyNameTypes : u8
{
	Default = 0,
	Random = 1
};

template <typename T>
T RandomRange(T range_from, T range_to)
{
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<T> distr(range_from, range_to);
	return distr(generator);
}

static KeyNameTypes GetTypeFromKeyname(const char* keyName)
{
	if (strstr(keyName, typeRandomPrefix)) // Type Random
	{
		return KeyNameTypes::Random;
	}
	else // Type Default
	{
		return KeyNameTypes::Default;
	}
}

char* GetFileNameFromKeyName(const char* keyName)
{
	int underscoreCount = 0;
	const char* start = nullptr;

	while (*keyName)
	{
		if (*keyName == '_')
		{
			underscoreCount++;
			if (underscoreCount == 3)
			{
				start = keyName + 1;
			}
		}
		keyName++;
	}

	if (start == nullptr)
	{
		// No third underscore found, return nullptr or an appropriate value
		return nullptr;
	}

	return strdup(start); // Allocate and return a copy of the substring
}

static int GetTypeValueIntFromKeyName(const char* keyName)
{
	int underscoreCount = 0;
	int number = 0;
	bool isParsingNumber = false;

	while (*keyName)
	{
		if (*keyName == '_')
		{
			underscoreCount++;
			if (underscoreCount == 2)
			{
				isParsingNumber = true;
			}
		}
		else if (isParsingNumber && std::isdigit(*keyName))
		{
			number = number * 10 + (*keyName - '0');
		}
		else if (isParsingNumber)
		{
			// Stop parsing if a non-digit character is encountered after the second underscore
			break;
		}
		keyName++;
	}

	return number;
}

static char* GetRandomKeyName(char* keyName)
{
	// Get keyName index info
	int keyNameIndex = RandomRange(0, GetTypeValueIntFromKeyName(keyName));
	std::string keyNameIndexStr = "_" + std::to_string(keyNameIndex);

	// Get keyName file name
	const char* keyNameFileName = GetFileNameFromKeyName(keyName);

	// Calculate the required memory size for newKeyName
	size_t totalLength = strlen(requiredPrefix) + strlen(keyNameIndexStr.c_str()) + strlen(keyNameFileName) + 1;

	// Allocate memory for newKeyName and initialize with a null-terminator
	char* newKeyName = new char[totalLength];
	newKeyName[0] = '\0';

	// Concatenate the components
	strcat(newKeyName, requiredPrefix);
	strcat(newKeyName, keyNameFileName);
	strcat(newKeyName, keyNameIndexStr.c_str());

	return newKeyName;
}

static void ReplaceRuntimeAssetName(xlink2::ResAssetCallTable* resAssetCallTable, char* keyName)
{
	char* keyNameToUse = nullptr;

	// Modify the key name
	switch (GetTypeFromKeyname(keyName))
	{
	case KeyNameTypes::Random:
		keyNameToUse = GetRandomKeyName(keyName);

		// If not found, use defult key
		if (!keyNameToUse)
		{
			goto DEFAULT_KEYNAME;
		}
		break;
	case KeyNameTypes::Default:
	DEFAULT_KEYNAME:
		keyNameToUse = keyName;
		break;
	}

	resAssetCallTable->mKeyName = new char[strlen(keyNameToUse) + 1];
	strncpy(resAssetCallTable->mKeyName, keyNameToUse, strlen(keyNameToUse) + 1);
}
}