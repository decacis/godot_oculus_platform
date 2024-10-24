#ifndef __ANDROID__
#define OVRP_PUBLIC_FUNCTION OVRPL_PUBLIC_FUNCTION

/*************************************************************************************
 * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT *
 * 
 * Extension of the OVR_PlatformLoader.cpp from Oculus SDK 
 * (search for #pragma region OVR_PlatformLoader.cpp_*)
 * add extern void LoadFunctionsOther(ModuleHandleType hModule); above LoadFunctions
 * Extend LoadFunctions with LoadFunctionsOther(hLib) call. 
 *************************************************************************************/

#pragma region Imported OVR_PlatformLoader.cpp_SDK_v69
/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * Licensed under the Oculus SDK License Agreement (the "License");
 * you may not use the Oculus SDK except in compliance with the License,
 * which is provided at the time of installation or download, or which
 * otherwise accompanies this software in either electronic or hard copy form.
 *
 * You may obtain a copy of the License at
 *
 * https://developer.oculus.com/licenses/oculussdk/
 *
 * Unless required by applicable law or agreed to in writing, the Oculus SDK
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/************************************************************************************
 * Filename    :   OVR_PlatformLoader.cpp
 * Content     :   Platform DLL user library
 * Created     :   February 18, 2016
 ***********************************************************************************/

// Drop-in shim to load LibOVRPlatform
// This shim will perform signature verification on the platform library.
// If the library is properly signed and loaded, it will pass through
// the initialization call, and also pass through attempts to call
// a few other critical functions.

// The majority of this is code derived from LibOVR/Src/OVR_CAPIShim.c

#ifndef OVRPL_DISABLED

#if defined(_MSC_VER)
#pragma warning(push, 0)
#endif
#include <Windows.h>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#pragma comment(lib, "advapi32.lib")

#include "OVR_Platform.h"
#include "OVR_PlatformVersion.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996) // 'getenv': This function or variable may be unsafe.
#endif

//-----------------------------------------------------------------------------------
// ***** FilePathCharType, ModuleHandleType, ModuleFunctionType
//
// #define instead of typedef because debuggers (VC++, XCode) don't recognize typedef'd types as a
// string type.
#define FilePathCharType wchar_t
typedef HMODULE ModuleHandleType;
typedef FARPROC ModuleFunctionType;

#define ModuleHandleTypeNull ((ModuleHandleType)NULL)
#define ModuleFunctionTypeNull ((ModuleFunctionType)NULL)

//-----------------------------------------------------------------------------------
// ***** OVRPL_DECLARE_IMPORT
//
// Creates typedef and pointer declaration for a function of a given signature.
// The typedef is <FunctionName>Type, and the pointer is <FunctionName>Ptr.
//
// Example usage:
//     int MultiplyValues(float x, float y);  // Assume this function exists in an external shared
//     library. We don't actually need to redeclare it. OVRPL_DECLARE_IMPORT(int, MultiplyValues,
//     (float x, float y)) // This creates a local typedef and pointer for it.

#define OVRPL_DECLARE_IMPORT(ReturnValue, FunctionName, Arguments) \
	typedef ReturnValue(OVRP_CDECL *FunctionName##Type) Arguments; \
	static FunctionName##Type FunctionName##PLPtr = NULL;

//-----------------------------------------------------------------------------------
// ***** OVRPL_GETFUNCTION
//
// Loads <FunctionName>Ptr from <library> if not already loaded.
// Assumes a variable named <FunctionName>Ptr of type <FunctionName>Type exists which is called
// <FunctionName> in LibOVRPlatform.
//
// Example usage:
//     OVRPL_GETFUNCTION(module, MultiplyValues)
//     int result = MultiplyValuesPtr(3.f, 4.f);

#define OVRPL_GETFUNCTION(l, f)       \
	if (!f##PLPtr) {                  \
		union {                       \
			f##Type p1;               \
			ModuleFunctionType p2;    \
		} u;                          \
		u.p2 = GetProcAddress(l, #f); \
		f##PLPtr = u.p1;              \
	}

//-----------------------------------------------------------------------------------
// ***** OVR_MAX_PATH
//
#if !defined(OVR_MAX_PATH)
#define OVR_MAX_PATH _MAX_PATH
#endif

static size_t OVR_wstrlcat(wchar_t *dest, const wchar_t *src, size_t destsize) {
	const size_t d = destsize ? wcslen(dest) : 0;
	const size_t s = wcslen(src);
	const size_t t = s + d;

	if (t < destsize)
		memcpy(dest + d, src, (s + 1) * sizeof(*src));
	else {
		if (destsize) {
			memcpy(dest + d, src, ((destsize - d) - 1) * sizeof(*src));
			dest[destsize - 1] = 0;
		}
	}

	return t;
}

static bool OVR_GetOculusBaseDirectory(
		FilePathCharType *directoryPath,
		size_t directoryPathCapacity) {
	DWORD length = directoryPathCapacity;
	HKEY key = 0;
	// Query the 32bit key even if 64bit build
	LONG result = RegOpenKeyExW(
			HKEY_LOCAL_MACHINE, L"Software\\Oculus VR, LLC\\Oculus", 0, KEY_READ | KEY_WOW64_32KEY, &key);
	if (result != ERROR_SUCCESS) {
		return false;
	}

	result = RegGetValueW(
			key, NULL, L"Base", RRF_RT_REG_SZ | RRF_ZEROONFAILURE, NULL, (LPBYTE)directoryPath, &length);
	RegCloseKey(key);

	return result == ERROR_SUCCESS;
}

static bool IsHighIntegrityLevel() {
	// Allocate a fixed size buffer for the maximum possible size:
	// SID_AND_ATTRIBUTES can be the size of a SID + size of DWORD (for attributes).
	uint8_t mandatoryLabelBuffer[SECURITY_MAX_SID_SIZE + sizeof(DWORD)];
	DWORD bufferSize;
	HANDLE processToken;
	DWORD integrityLevel = SECURITY_MANDATORY_HIGH_RID;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_QUERY_SOURCE, &processToken) == 0) {
		return false;
	}

	if (GetTokenInformation(
				processToken,
				TokenIntegrityLevel,
				mandatoryLabelBuffer,
				sizeof(mandatoryLabelBuffer),
				&bufferSize) != 0) {
		TOKEN_MANDATORY_LABEL *mandatoryLabel = (TOKEN_MANDATORY_LABEL *)mandatoryLabelBuffer;
		const DWORD subAuthorityCount = *GetSidSubAuthorityCount(mandatoryLabel->Label.Sid);
		integrityLevel = *GetSidSubAuthority(mandatoryLabel->Label.Sid, subAuthorityCount - 1);
	}

	CloseHandle(processToken);
	return integrityLevel > SECURITY_MANDATORY_MEDIUM_RID;
}

static ModuleHandleType OVR_OpenLibrary(
		const FilePathCharType *libraryPath,
		ovrPlatformInitializeResult *outResult) {
	// In this case we thought we found a valid library at the location, so we'll load it, and if that
	// fails for some reason we'll mark it as an invalid file error.
	ModuleHandleType hModule = LoadLibraryW(libraryPath);

	if (hModule == ModuleHandleTypeNull) {
		*outResult = ovrPlatformInitialize_FileInvalid;
	} else {
		*outResult = ovrPlatformInitialize_Success;
	}
	return hModule;
}

void OVR_CloseLibrary(ModuleHandleType hLibrary) {
	if (hLibrary) {
		// We may need to consider what to do in the case that the library is in an exception state.
		// In a Windows C++ DLL, all global objects (including static members of classes) will be
		// constructed just before the calling of the DllMain with DLL_PROCESS_ATTACH and they will be
		// destroyed just after the call of the DllMain with DLL_PROCESS_DETACH. We may need to
		// intercept DLL_PROCESS_DETACH and have special handling for the case that the DLL is broken.
		FreeLibrary(hLibrary);
	}
}

// Returns a valid ModuleHandleType (e.g. Windows HMODULE) or returns ModuleHandleTypeNull (e.g.
// NULL). The caller is required to eventually call OVR_CloseLibrary on a valid return handle.
//
static ModuleHandleType OVR_FindLibraryPath(
		int requestedProductVersion,
		int requestedMajorVersion,
		ovrPlatformInitializeResult *outResult,
		FilePathCharType *libraryPath,
		size_t libraryPathCapacity) {
	ModuleHandleType moduleHandle;
	int printfResult;
	FilePathCharType developerDir[OVR_MAX_PATH] = { '\0' };
	FilePathCharType oculusInstallDir[OVR_MAX_PATH] = { '\0' };

#if defined(_WIN64)
	const char *pBitDepth = "64";
#else
	const char *pBitDepth = "32";
#endif

	(void)requestedProductVersion;

	moduleHandle = ModuleHandleTypeNull;
	if (libraryPathCapacity)
		libraryPath[0] = '\0';

#define OVR_FILE_PATH_SEPARATOR L"\\"

	if (!IsHighIntegrityLevel()) {
		size_t length;
		errno_t success = _wgetenv_s(&length, developerDir, _countof(developerDir), L"LIBOVR_DLL_DIR");
		if ((success == 0) && (length != 0) && (length < _countof(developerDir)) &&
				developerDir[length - 2] != OVR_FILE_PATH_SEPARATOR[0]) {
			OVR_wstrlcat(developerDir, OVR_FILE_PATH_SEPARATOR, _countof(developerDir));
		}
	}

	if (OVR_GetOculusBaseDirectory(oculusInstallDir, _countof(oculusInstallDir))) {
		size_t baseDirLength = wcslen(oculusInstallDir);

		// If missing a trailing path separator then append one.
		if ((baseDirLength > 0) && (baseDirLength < _countof(oculusInstallDir)) &&
				(oculusInstallDir[baseDirLength - 1] != OVR_FILE_PATH_SEPARATOR[0])) {
			baseDirLength =
					OVR_wstrlcat(oculusInstallDir, OVR_FILE_PATH_SEPARATOR, _countof(oculusInstallDir));
		}

#define OVR_RUNTIME_PATH L"Support\\oculus-runtime\\"

		if ((baseDirLength > 0) &&
				(baseDirLength + _countof(OVR_RUNTIME_PATH) < _countof(oculusInstallDir))) {
			baseDirLength = OVR_wstrlcat(oculusInstallDir, OVR_RUNTIME_PATH, _countof(oculusInstallDir));
		}
	}

	auto lastOpenResult = ovrPlatformInitialize_Uninitialized;

	{
		size_t i;

		// On Windows, only search the developer directory and the install path
		const FilePathCharType *directoryArray[2];
		directoryArray[0] = developerDir[0] != '\0' ? developerDir : NULL; // Developer directory
		directoryArray[1] = oculusInstallDir;

		for (i = 0; i < sizeof(directoryArray) / sizeof(directoryArray[0]); ++i) {
			if (directoryArray[i] != NULL) {
				printfResult = swprintf(
						libraryPath,
						libraryPathCapacity,
						L"%lsLibOVRPlatformImpl%hs_%d.dll",
						directoryArray[i],
						pBitDepth,
						requestedMajorVersion);

				if ((printfResult >= 0) && (printfResult < (int)libraryPathCapacity)) {
					auto openResult = ovrPlatformInitialize_Uninitialized;
					moduleHandle = OVR_OpenLibrary(libraryPath, &openResult);
					if (moduleHandle != ModuleHandleTypeNull) {
						*outResult = openResult;
						return moduleHandle;
					} else {
						lastOpenResult = openResult;
					}
				}
			}
		}
	}

	*outResult = lastOpenResult != ovrPlatformInitialize_Uninitialized
			? lastOpenResult
			: ovrPlatformInitialize_UnableToVerify;
	return moduleHandle;
}

OVRPL_DECLARE_IMPORT(
		ovrPlatformInitializeResult,
		ovr_PlatformInitializeWindows,
		(const char *appId));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_PlatformInitializeWindowsAsynchronous, (const char *appId));
OVRPL_DECLARE_IMPORT(
		ovrRequest,
		ovr_PlatformInitializeWithAccessToken,
		(ovrID appId, const char *accessToken));
OVRPL_DECLARE_IMPORT(
		ovrRequest,
		ovr_PlatformInitializeWithAccessTokenAndOptions,
		(ovrID appId,
				const char *accessToken,
				ovrKeyValuePair *configOptions,
				size_t numConfigOptions));
OVRPL_DECLARE_IMPORT(ovrMessage *, ovr_PopMessage, ());
OVRPL_DECLARE_IMPORT(void, ovr_PlatformInitializeStandaloneAccessToken, (const char *accessToken));
OVRPL_DECLARE_IMPORT(
		ovrRequest,
		ovr_Platform_InitializeStandaloneOculus,
		(const ovrOculusInitParams *params));

#pragma region OVR_PlatformLoader.cpp_LoadFunctionsOther
/*************************************************************************************
 * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT *
 * add extern void LoadFunctionsOther(ModuleHandleType hModule); above LoadFunctions *
 *************************************************************************************/
extern void LoadFunctionsOther(ModuleHandleType hModule);

static void LoadFunctions(ModuleHandleType hModule) {
	OVRPL_GETFUNCTION(hModule, ovr_PlatformInitializeWindows);
	OVRPL_GETFUNCTION(hModule, ovr_PlatformInitializeWindowsAsynchronous);
	OVRPL_GETFUNCTION(hModule, ovr_PlatformInitializeWithAccessToken);
	OVRPL_GETFUNCTION(hModule, ovr_PlatformInitializeWithAccessTokenAndOptions);
	OVRPL_GETFUNCTION(hModule, ovr_PopMessage);
	OVRPL_GETFUNCTION(hModule, ovr_PlatformInitializeStandaloneAccessToken);
	OVRPL_GETFUNCTION(hModule, ovr_Platform_InitializeStandaloneOculus);

	/*************************************************************************************
	 * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT * IMPORTANT *
	 * Extend LoadFunctions with LoadFunctionsOther(hLib) call.                          *
	 *************************************************************************************/
	LoadFunctionsOther(hModule);
}
#pragma endregion

static ovrPlatformInitializeResult InitializeResult = ovrPlatformInitialize_Uninitialized;

ovrPlatformInitializeResult loaderInitHelper(int productVersion, int majorVersion) {
	if (InitializeResult != ovrPlatformInitialize_Uninitialized) {
		return InitializeResult;
	}

	// Check to make sure the headers they're using (which automatically pass the version to this
	// function) match the version that this loader library was compiled under.
	if (productVersion != PLATFORM_PRODUCT_VERSION || majorVersion != PLATFORM_MAJOR_VERSION) {
		InitializeResult = ovrPlatformInitialize_VersionMismatch;
		return InitializeResult;
	}

	// See if the one we want has already been loaded by mirroring the OVR_FindLibraryPath name
	// generation but without the path
	FilePathCharType preLoadLibName[OVR_MAX_PATH];
	FilePathCharType preLoadFilePath[OVR_MAX_PATH];

#if defined(_WIN64)
	const char *pBitDepth = "64";
#else
	const char *pBitDepth = "32";
#endif

	swprintf(
			preLoadLibName,
			sizeof(preLoadLibName) / sizeof(preLoadLibName[0]),
			L"LibOVRPlatformImpl%hs_%d.dll",
			pBitDepth,
			PLATFORM_MAJOR_VERSION);
	auto hLibPreLoad = GetModuleHandleW(preLoadLibName);
	if (hLibPreLoad != NULL) {
		// Someone already loaded the module. Might be fine, just copy the path out so we can check it
		// later.
		GetModuleFileNameW(
				hLibPreLoad, preLoadFilePath, sizeof(preLoadFilePath) / sizeof(preLoadFilePath[0]));
	}

	FilePathCharType filePath[OVR_MAX_PATH];

	auto hLib = OVR_FindLibraryPath(
			PLATFORM_PRODUCT_VERSION,
			PLATFORM_MAJOR_VERSION,
			&InitializeResult,
			filePath,
			sizeof(filePath) / sizeof(filePath[0]));

	if (InitializeResult == ovrPlatformInitialize_Success) {
		if (hLibPreLoad != NULL && wcsicmp(filePath, preLoadFilePath) != 0) {
			// The pre-loaded module was on a different path than the validated library. Not a
			// particularly likely case, but if it happens we should fail, since the non-shimmed functions
			// could call into the wrong library.
			InitializeResult = ovrPlatformInitialize_PreLoaded;
			return InitializeResult;
		}

		LoadFunctions(hLib);
	}

	return InitializeResult;
}

OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_PlatformInitializeWindowsAsynchronousEx(
		const char *appId,
		ovrPlatformInitializeResult *outResult,
		int productVersion,
		int majorVersion) {
	ovrPlatformInitializeResult result = loaderInitHelper(productVersion, majorVersion);
	*outResult = result;

	if (result == ovrPlatformInitialize_Success) {
		return ovr_PlatformInitializeWindowsAsynchronousPLPtr(appId);
	}

	return 0;
}

OVRPL_PUBLIC_FUNCTION(ovrPlatformInitializeResult)
ovr_PlatformInitializeWindowsEx(const char *appId, int productVersion, int majorVersion) {
	ovrPlatformInitializeResult result = loaderInitHelper(productVersion, majorVersion);
	if (result == ovrPlatformInitialize_Success) {
		ovr_PlatformInitializeWindowsPLPtr(appId);
	}
	return result;
}

OVRPL_PUBLIC_FUNCTION(ovrMessage *)
ovr_PopMessage() {
	if (InitializeResult == ovrPlatformInitialize_Success) {
		return ovr_PopMessagePLPtr();
	}
	return nullptr;
}

// We also shim the standalone initializer just for consistency in debugging, basically a shorter
// version of the windows init since we don't care about safety
OVRPL_PUBLIC_FUNCTION(void)
ovr_PlatformInitializeStandaloneAccessToken(const char *accessToken) {
	if (InitializeResult != ovrPlatformInitialize_Uninitialized) {
		return;
	}

	InitializeResult = ovrPlatformInitialize_Success;

	FilePathCharType preLoadLibName[OVR_MAX_PATH];

#if defined(_WIN64)
	const char *pBitDepth = "64";
#else
	const char *pBitDepth = "32";
#endif

	swprintf(
			preLoadLibName,
			sizeof(preLoadLibName) / sizeof(preLoadLibName[0]),
			L"LibOVRPlatformImpl%hs_%d.dll",
			pBitDepth,
			PLATFORM_MAJOR_VERSION);
	auto hLibPreLoad = GetModuleHandleW(preLoadLibName);

	LoadFunctions(hLibPreLoad);
	ovr_PlatformInitializeStandaloneAccessTokenPLPtr(accessToken);
}

OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Platform_InitializeStandaloneOculusEx(
		const ovrOculusInitParams *params,
		ovrPlatformInitializeResult *outResult,
		int productVersion,
		int majorVersion) {
	if (params != nullptr && outResult != nullptr) {
		ovrPlatformInitializeResult result = loaderInitHelper(productVersion, majorVersion);
		*outResult = result;
		if (result == ovrPlatformInitialize_Success) {
			return ovr_Platform_InitializeStandaloneOculusPLPtr(params);
		}
	} else if (outResult != nullptr) {
		*outResult = ovrPlatformInitialize_Uninitialized;
	}
	return 0;
}

OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_PlatformInitializeWithAccessTokenEx(
		ovrID appId,
		const char *serviceAccessToken,
		ovrPlatformInitializeResult *outResult,
		int productVersion,
		int majorVersion) {
	if (outResult != nullptr) {
		ovrPlatformInitializeResult result = loaderInitHelper(productVersion, majorVersion);
		*outResult = result;
		if (result == ovrPlatformInitialize_Success) {
			return ovr_PlatformInitializeWithAccessTokenPLPtr(appId, serviceAccessToken);
		}
	}
	return 0;
}

#endif
#pragma endregion

OVRPL_DECLARE_IMPORT(bool, ovr_IsPlatformInitialized, ());
OVRPL_DECLARE_IMPORT(const char *, ovrPlatformInitializeResult_ToString, (ovrPlatformInitializeResult value));
OVRPL_DECLARE_IMPORT(ovrID, ovr_GetLoggedInUserID, ());
OVRPL_DECLARE_IMPORT(const char *, ovr_GetLoggedInUserLocale, ());
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Entitlement_GetIsViewerEntitled, ());
OVRPL_DECLARE_IMPORT(ovrMessageType, ovr_Message_GetType, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovrMessageType_ToString, (ovrMessageType value));
OVRPL_DECLARE_IMPORT(bool, ovr_Message_IsError, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(ovrErrorHandle, ovr_Message_GetError, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_Error_GetMessage, (const ovrErrorHandle obj));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Message_GetRequestID, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(ovrPlatformInitializeHandle, ovr_Message_GetPlatformInitialize, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(ovrPlatformInitializeResult, ovr_PlatformInitialize_GetResult, (const ovrPlatformInitializeHandle obj));
OVRPL_DECLARE_IMPORT(ovrAccountAgeCategory, ovr_UserAccountAgeCategory_GetAgeCategory, (const ovrUserAccountAgeCategoryHandle obj));
OVRPL_DECLARE_IMPORT(ovrUserAccountAgeCategoryHandle, ovr_Message_GetUserAccountAgeCategory, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_Message_GetString, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_User_GetLoggedInUser, ());
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_User_Get, (ovrID userID));
OVRPL_DECLARE_IMPORT(ovrUserHandle, ovr_Message_GetUser, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_User_GetDisplayName, (const ovrUserHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_User_GetOculusID, (const ovrUserHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_User_GetImageUrl, (const ovrUserHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_User_GetSmallImageUrl, (const ovrUserHandle obj));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_UserAgeCategory_Get, ());
OVRPL_DECLARE_IMPORT(bool, ovrID_FromString, (ovrID * outId, const char *inId));
OVRPL_DECLARE_IMPORT(bool, ovrID_ToString, (char *outParam, size_t bufferLength, ovrID id));
OVRPL_DECLARE_IMPORT(ovrID, ovr_User_GetID, (const ovrUserHandle obj));
OVRPL_DECLARE_IMPORT(void, ovr_FreeMessage, (ovrMessageHandle));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_AddCount, (const char *name, unsigned long long count));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_AddFields, (const char *name, const char *fields));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_Unlock, (const char *name));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_GetAllDefinitions, ());
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_GetAllProgress, ());
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_GetDefinitionsByName, (const char **names, int count));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_GetProgressByName, (const char **names, int count));
OVRPL_DECLARE_IMPORT(ovrAchievementDefinitionArrayHandle, ovr_Message_GetAchievementDefinitionArray, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(ovrAchievementProgressArrayHandle, ovr_Message_GetAchievementProgressArray, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(ovrAchievementProgressHandle, ovr_AchievementProgressArray_GetElement, (const ovrAchievementProgressArrayHandle obj, size_t index));
OVRPL_DECLARE_IMPORT(const char *, ovr_AchievementProgressArray_GetNextUrl, (const ovrAchievementProgressArrayHandle obj));
OVRPL_DECLARE_IMPORT(size_t, ovr_AchievementProgressArray_GetSize, (const ovrAchievementProgressArrayHandle obj));
OVRPL_DECLARE_IMPORT(bool, ovr_AchievementProgressArray_HasNextPage, (const ovrAchievementProgressArrayHandle obj));
OVRPL_DECLARE_IMPORT(ovrAchievementUpdateHandle, ovr_Message_GetAchievementUpdate, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_AchievementProgress_GetBitfield, (const ovrAchievementProgressHandle obj));
OVRPL_DECLARE_IMPORT(unsigned long long, ovr_AchievementProgress_GetCount, (const ovrAchievementProgressHandle obj));
OVRPL_DECLARE_IMPORT(bool, ovr_AchievementProgress_GetIsUnlocked, (const ovrAchievementProgressHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_AchievementProgress_GetName, (const ovrAchievementProgressHandle obj));
OVRPL_DECLARE_IMPORT(unsigned long long, ovr_AchievementProgress_GetUnlockTime, (const ovrAchievementProgressHandle obj));
OVRPL_DECLARE_IMPORT(bool, ovr_AchievementUpdate_GetJustUnlocked, (const ovrAchievementUpdateHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_AchievementUpdate_GetName, (const ovrAchievementUpdateHandle obj));
OVRPL_DECLARE_IMPORT(ovrAchievementDefinitionHandle, ovr_AchievementDefinitionArray_GetElement, (const ovrAchievementDefinitionArrayHandle obj, size_t index));
OVRPL_DECLARE_IMPORT(const char *, ovr_AchievementDefinitionArray_GetNextUrl, (const ovrAchievementDefinitionArrayHandle obj));
OVRPL_DECLARE_IMPORT(size_t, ovr_AchievementDefinitionArray_GetSize, (const ovrAchievementDefinitionArrayHandle obj));
OVRPL_DECLARE_IMPORT(bool, ovr_AchievementDefinitionArray_HasNextPage, (const ovrAchievementDefinitionArrayHandle obj));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_GetNextAchievementDefinitionArrayPage, (ovrAchievementDefinitionArrayHandle handle));
OVRPL_DECLARE_IMPORT(unsigned int, ovr_AchievementDefinition_GetBitfieldLength, (const ovrAchievementDefinitionHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_AchievementDefinition_GetName, (const ovrAchievementDefinitionHandle obj));
OVRPL_DECLARE_IMPORT(ovrAchievementType, ovr_AchievementDefinition_GetType, (const ovrAchievementDefinitionHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovrAchievementType_ToString, (ovrAchievementType value));
OVRPL_DECLARE_IMPORT(ovrAchievementType, ovrAchievementType_FromString, (const char *str));
OVRPL_DECLARE_IMPORT(unsigned long long, ovr_AchievementDefinition_GetTarget, (const ovrAchievementDefinitionHandle obj));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Achievements_GetNextAchievementProgressArrayPage, (ovrAchievementProgressArrayHandle handle));

OVRPL_DECLARE_IMPORT(ovrLaunchDetailsHandle, ovr_ApplicationLifecycle_GetLaunchDetails, ());
OVRPL_DECLARE_IMPORT(void, ovr_ApplicationLifecycle_LogDeeplinkResult, (const char *trackingID, ovrLaunchResult result));
OVRPL_DECLARE_IMPORT(const char *, ovr_LaunchDetails_GetDeeplinkMessage, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_LaunchDetails_GetDestinationApiName, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_LaunchDetails_GetLaunchSource, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(ovrLaunchType, ovr_LaunchDetails_GetLaunchType, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_LaunchDetails_GetLobbySessionID, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_LaunchDetails_GetMatchSessionID, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_LaunchDetails_GetTrackingID, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(ovrUserArrayHandle, ovr_LaunchDetails_GetUsers, (const ovrLaunchDetailsHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovrLaunchType_ToString, (ovrLaunchType value));
OVRPL_DECLARE_IMPORT(ovrLaunchType, ovrLaunchType_FromString, (const char *str));
OVRPL_DECLARE_IMPORT(ovrUserHandle, ovr_UserArray_GetElement, (const ovrUserArrayHandle obj, size_t index));
OVRPL_DECLARE_IMPORT(const char *, ovr_UserArray_GetNextUrl, (const ovrUserArrayHandle obj));
OVRPL_DECLARE_IMPORT(size_t, ovr_UserArray_GetSize, (const ovrUserArrayHandle obj));
OVRPL_DECLARE_IMPORT(bool, ovr_UserArray_HasNextPage, (const ovrUserArrayHandle obj));
OVRPL_DECLARE_IMPORT(ovrRequest, ovr_Application_GetVersion, ());
OVRPL_DECLARE_IMPORT(ovrApplicationVersionHandle, ovr_Message_GetApplicationVersion, (const ovrMessageHandle obj));
OVRPL_DECLARE_IMPORT(int, ovr_ApplicationVersion_GetCurrentCode, (const ovrApplicationVersionHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_ApplicationVersion_GetCurrentName, (const ovrApplicationVersionHandle obj));
OVRPL_DECLARE_IMPORT(int, ovr_ApplicationVersion_GetLatestCode, (const ovrApplicationVersionHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_ApplicationVersion_GetLatestName, (const ovrApplicationVersionHandle obj));
OVRPL_DECLARE_IMPORT(long long, ovr_ApplicationVersion_GetReleaseDate, (const ovrApplicationVersionHandle obj));
OVRPL_DECLARE_IMPORT(const char *, ovr_ApplicationVersion_GetSize, (const ovrApplicationVersionHandle obj));

void LoadFunctionsOther(ModuleHandleType hModule) {
	OVRPL_GETFUNCTION(hModule, ovr_IsPlatformInitialized);
	OVRPL_GETFUNCTION(hModule, ovrPlatformInitializeResult_ToString);
	OVRPL_GETFUNCTION(hModule, ovr_GetLoggedInUserID);
	OVRPL_GETFUNCTION(hModule, ovr_GetLoggedInUserLocale);
	OVRPL_GETFUNCTION(hModule, ovr_Entitlement_GetIsViewerEntitled);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetType);
	OVRPL_GETFUNCTION(hModule, ovrMessageType_ToString);
	OVRPL_GETFUNCTION(hModule, ovr_Message_IsError);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetError);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetRequestID);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetPlatformInitialize);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetUserAccountAgeCategory);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetUser);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetString);
	OVRPL_GETFUNCTION(hModule, ovr_Error_GetMessage);
	OVRPL_GETFUNCTION(hModule, ovr_PlatformInitialize_GetResult);
	OVRPL_GETFUNCTION(hModule, ovr_UserAccountAgeCategory_GetAgeCategory);
	OVRPL_GETFUNCTION(hModule, ovr_User_GetID);
	OVRPL_GETFUNCTION(hModule, ovr_User_GetLoggedInUser);
	OVRPL_GETFUNCTION(hModule, ovr_User_Get);
	OVRPL_GETFUNCTION(hModule, ovr_User_GetDisplayName);
	OVRPL_GETFUNCTION(hModule, ovr_User_GetOculusID);
	OVRPL_GETFUNCTION(hModule, ovr_User_GetImageUrl);
	OVRPL_GETFUNCTION(hModule, ovr_User_GetSmallImageUrl);
	OVRPL_GETFUNCTION(hModule, ovr_UserAgeCategory_Get);
	OVRPL_GETFUNCTION(hModule, ovrID_FromString);
	OVRPL_GETFUNCTION(hModule, ovrID_ToString);
	OVRPL_GETFUNCTION(hModule, ovr_FreeMessage);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_AddCount);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_AddFields);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_Unlock);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_GetAllDefinitions);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_GetAllProgress);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_GetDefinitionsByName);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_GetProgressByName);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetAchievementDefinitionArray);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetAchievementProgressArray);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgressArray_GetElement);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgressArray_GetNextUrl);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgressArray_GetSize);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgressArray_HasNextPage);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgress_GetBitfield);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgress_GetCount);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgress_GetIsUnlocked);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgress_GetName);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementProgress_GetUnlockTime);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetAchievementUpdate);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementUpdate_GetJustUnlocked);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementUpdate_GetName);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinitionArray_GetElement);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinitionArray_GetNextUrl);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinitionArray_GetSize);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinitionArray_HasNextPage);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_GetNextAchievementDefinitionArrayPage);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinition_GetBitfieldLength);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinition_GetName);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinition_GetType);
	OVRPL_GETFUNCTION(hModule, ovrAchievementType_ToString);
	OVRPL_GETFUNCTION(hModule, ovrAchievementType_FromString);
	OVRPL_GETFUNCTION(hModule, ovr_AchievementDefinition_GetTarget);
	OVRPL_GETFUNCTION(hModule, ovr_Achievements_GetNextAchievementProgressArrayPage);

	OVRPL_GETFUNCTION(hModule, ovr_ApplicationLifecycle_GetLaunchDetails);
	OVRPL_GETFUNCTION(hModule, ovr_ApplicationLifecycle_LogDeeplinkResult);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetDeeplinkMessage);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetDestinationApiName);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetLaunchSource);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetLaunchType);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetLobbySessionID);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetMatchSessionID);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetTrackingID);
	OVRPL_GETFUNCTION(hModule, ovr_LaunchDetails_GetUsers);
	OVRPL_GETFUNCTION(hModule, ovrLaunchType_ToString);
	OVRPL_GETFUNCTION(hModule, ovrLaunchType_FromString);
	OVRPL_GETFUNCTION(hModule, ovr_UserArray_GetElement);
	OVRPL_GETFUNCTION(hModule, ovr_UserArray_GetNextUrl);
	OVRPL_GETFUNCTION(hModule, ovr_UserArray_GetSize);
	OVRPL_GETFUNCTION(hModule, ovr_UserArray_HasNextPage);
	OVRPL_GETFUNCTION(hModule, ovr_Application_GetVersion);
	OVRPL_GETFUNCTION(hModule, ovr_Message_GetApplicationVersion);
	OVRPL_GETFUNCTION(hModule, ovr_ApplicationVersion_GetCurrentCode);
	OVRPL_GETFUNCTION(hModule, ovr_ApplicationVersion_GetCurrentName);
	OVRPL_GETFUNCTION(hModule, ovr_ApplicationVersion_GetLatestCode);
	OVRPL_GETFUNCTION(hModule, ovr_ApplicationVersion_GetLatestName);
	OVRPL_GETFUNCTION(hModule, ovr_ApplicationVersion_GetReleaseDate);
	OVRPL_GETFUNCTION(hModule, ovr_ApplicationVersion_GetSize);
}

OVRPL_PUBLIC_FUNCTION(bool)
ovr_IsPlatformInitialized() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_IsPlatformInitializedPLPtr();
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovrPlatformInitializeResult_ToString(ovrPlatformInitializeResult value) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrPlatformInitializeResult_ToStringPLPtr(value);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrID)
ovr_GetLoggedInUserID() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		auto rsp = ovr_GetLoggedInUserIDPLPtr();
		return rsp;
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_GetLoggedInUserLocale() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		auto rsp = ovr_GetLoggedInUserLocalePLPtr();
		return rsp;
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_User_GetLoggedInUser() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_User_GetLoggedInUserPLPtr();
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Entitlement_GetIsViewerEntitled() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Entitlement_GetIsViewerEntitledPLPtr();
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrMessageType)
ovr_Message_GetType(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetTypePLPtr(obj);
	}
	return ovrMessage_Unknown;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovrMessageType_ToString(ovrMessageType value) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrMessageType_ToStringPLPtr(value);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(bool)
ovr_Message_IsError(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_IsErrorPLPtr(obj);
	}
	return true;
}
OVRPL_PUBLIC_FUNCTION(ovrErrorHandle)
ovr_Message_GetError(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetErrorPLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Message_GetRequestID(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetRequestIDPLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrPlatformInitializeHandle)
ovr_Message_GetPlatformInitialize(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetPlatformInitializePLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(ovrUserAccountAgeCategoryHandle)
ovr_Message_GetUserAccountAgeCategory(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetUserAccountAgeCategoryPLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(ovrUserHandle)
ovr_Message_GetUser(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetUserPLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_Message_GetString(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetStringPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_Error_GetMessage(const ovrErrorHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Error_GetMessagePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrPlatformInitializeResult)
ovr_PlatformInitialize_GetResult(const ovrPlatformInitializeHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_PlatformInitialize_GetResultPLPtr(obj);
	}
	return ovrPlatformInitialize_InvalidCredentials;
}
OVRPL_PUBLIC_FUNCTION(ovrAccountAgeCategory)
ovr_UserAccountAgeCategory_GetAgeCategory(const ovrUserAccountAgeCategoryHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_UserAccountAgeCategory_GetAgeCategoryPLPtr(obj);
	}
	return ovrAccountAgeCategory_Unknown;
}
OVRPL_PUBLIC_FUNCTION(ovrID)
ovr_User_GetID(const ovrUserHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_User_GetIDPLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_User_Get(ovrID userID) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_User_GetPLPtr(userID);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_User_GetDisplayName(const ovrUserHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_User_GetDisplayNamePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_User_GetOculusID(const ovrUserHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_User_GetOculusIDPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_User_GetImageUrl(const ovrUserHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_User_GetImageUrlPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_User_GetSmallImageUrl(const ovrUserHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_User_GetSmallImageUrlPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_UserAgeCategory_Get() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_UserAgeCategory_GetPLPtr();
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(bool)
ovrID_FromString(ovrID *outId, const char *inId) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrID_FromStringPLPtr(outId, inId);
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(bool)
ovrID_ToString(char *outParam, size_t bufferLength, ovrID id) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrID_ToStringPLPtr(outParam, bufferLength, id);
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(void)
ovr_FreeMessage(ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_FreeMessagePLPtr(obj);
	}
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_AddCount(const char* name, unsigned long long count) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_AddCountPLPtr(name, count);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_AddFields(const char* name, const char* fields) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_AddFieldsPLPtr(name, fields);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_Unlock(const char* name) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_UnlockPLPtr(name);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_GetAllDefinitions() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_GetAllDefinitionsPLPtr();
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_GetAllProgress() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_GetAllProgressPLPtr();
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_GetDefinitionsByName(const char** names, int count) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_GetDefinitionsByNamePLPtr(names, count);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_GetProgressByName(const char** names, int count) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_GetProgressByNamePLPtr(names, count);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrAchievementDefinitionArrayHandle)
ovr_Message_GetAchievementDefinitionArray(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetAchievementDefinitionArrayPLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(ovrAchievementProgressArrayHandle)
ovr_Message_GetAchievementProgressArray(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetAchievementProgressArrayPLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(ovrAchievementProgressHandle)
ovr_AchievementProgressArray_GetElement(const ovrAchievementProgressArrayHandle obj, size_t index) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgressArray_GetElementPLPtr(obj, index);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_AchievementProgressArray_GetNextUrl(const ovrAchievementProgressArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgressArray_GetNextUrlPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(size_t)
ovr_AchievementProgressArray_GetSize(const ovrAchievementProgressArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgressArray_GetSizePLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(bool)
ovr_AchievementProgressArray_HasNextPage(const ovrAchievementProgressArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgressArray_HasNextPagePLPtr(obj);
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_AchievementProgress_GetBitfield(const ovrAchievementProgressHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgress_GetBitfieldPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(unsigned long long)
ovr_AchievementProgress_GetCount(const ovrAchievementProgressHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgress_GetCountPLPtr(obj);
	}
	return 0LL;
}
OVRPL_PUBLIC_FUNCTION(bool)
ovr_AchievementProgress_GetIsUnlocked(const ovrAchievementProgressHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgress_GetIsUnlockedPLPtr(obj);
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_AchievementProgress_GetName(const ovrAchievementProgressHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgress_GetNamePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(unsigned long long)
ovr_AchievementProgress_GetUnlockTime(const ovrAchievementProgressHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementProgress_GetUnlockTimePLPtr(obj);
	}
	return 0LL;
}
OVRPL_PUBLIC_FUNCTION(ovrAchievementUpdateHandle)
ovr_Message_GetAchievementUpdate(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetAchievementUpdatePLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(bool)
ovr_AchievementUpdate_GetJustUnlocked(const ovrAchievementUpdateHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementUpdate_GetJustUnlockedPLPtr(obj);
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_AchievementUpdate_GetName(const ovrAchievementUpdateHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementUpdate_GetNamePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrAchievementDefinitionHandle)
ovr_AchievementDefinitionArray_GetElement(const ovrAchievementDefinitionArrayHandle obj, size_t index) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinitionArray_GetElementPLPtr(obj, index);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_AchievementDefinitionArray_GetNextUrl(const ovrAchievementDefinitionArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinitionArray_GetNextUrlPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(size_t)
ovr_AchievementDefinitionArray_GetSize(const ovrAchievementDefinitionArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinitionArray_GetSizePLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(bool)
ovr_AchievementDefinitionArray_HasNextPage(const ovrAchievementDefinitionArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinitionArray_HasNextPagePLPtr(obj);
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_GetNextAchievementDefinitionArrayPage(ovrAchievementDefinitionArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_GetNextAchievementDefinitionArrayPagePLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(unsigned int)
ovr_AchievementDefinition_GetBitfieldLength(const ovrAchievementDefinitionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinition_GetBitfieldLengthPLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_AchievementDefinition_GetName(const ovrAchievementDefinitionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinition_GetNamePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrAchievementType)
ovr_AchievementDefinition_GetType(const ovrAchievementDefinitionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinition_GetTypePLPtr(obj);
	}
	return ovrAchievement_TypeUnknown;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovrAchievementType_ToString(ovrAchievementType value) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrAchievementType_ToStringPLPtr(value);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrAchievementType)
ovrAchievementType_FromString(const char *str) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrAchievementType_FromStringPLPtr(str);
	}
	return ovrAchievement_TypeUnknown;
}
OVRPL_PUBLIC_FUNCTION(unsigned long long)
ovr_AchievementDefinition_GetTarget(const ovrAchievementDefinitionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_AchievementDefinition_GetTargetPLPtr(obj);
	}
	return 0LL;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Achievements_GetNextAchievementProgressArrayPage(ovrAchievementProgressArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Achievements_GetNextAchievementProgressArrayPagePLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrLaunchDetailsHandle)
ovr_ApplicationLifecycle_GetLaunchDetails() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationLifecycle_GetLaunchDetailsPLPtr();
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(void)
ovr_ApplicationLifecycle_LogDeeplinkResult(const char *trackingID, ovrLaunchResult launchResult) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationLifecycle_LogDeeplinkResultPLPtr(trackingID, launchResult);
	}
	return;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_LaunchDetails_GetDeeplinkMessage(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetDeeplinkMessagePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_LaunchDetails_GetDestinationApiName(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetDestinationApiNamePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_LaunchDetails_GetLaunchSource(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetLaunchSourcePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrLaunchType)
ovr_LaunchDetails_GetLaunchType(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetLaunchTypePLPtr(obj);
	}
	return ovrLaunchType_Unknown;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_LaunchDetails_GetLobbySessionID(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetLobbySessionIDPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_LaunchDetails_GetMatchSessionID(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetMatchSessionIDPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_LaunchDetails_GetTrackingID(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetTrackingIDPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrUserArrayHandle)
ovr_LaunchDetails_GetUsers(const ovrLaunchDetailsHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_LaunchDetails_GetUsersPLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovrLaunchType_ToString(ovrLaunchType value) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrLaunchType_ToStringPLPtr(value);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(ovrLaunchType)
ovrLaunchType_FromString(const char *str) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovrLaunchType_FromStringPLPtr(str);
	}
	return ovrLaunchType_Unknown;
}
OVRPL_PUBLIC_FUNCTION(ovrUserHandle)
ovr_UserArray_GetElement(const ovrUserArrayHandle obj, size_t index) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_UserArray_GetElementPLPtr(obj, index);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_UserArray_GetNextUrl(const ovrUserArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_UserArray_GetNextUrlPLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(size_t)
ovr_UserArray_GetSize(const ovrUserArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_UserArray_GetSizePLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(bool)
ovr_UserArray_HasNextPage(const ovrUserArrayHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_UserArray_HasNextPagePLPtr(obj);
	}
	return false;
}
OVRPL_PUBLIC_FUNCTION(ovrRequest)
ovr_Application_GetVersion() {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Application_GetVersionPLPtr();
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(ovrApplicationVersionHandle)
ovr_Message_GetApplicationVersion(const ovrMessageHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_Message_GetApplicationVersionPLPtr(obj);
	}
	return nullptr;
}
OVRPL_PUBLIC_FUNCTION(int)
ovr_ApplicationVersion_GetCurrentCode(const ovrApplicationVersionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationVersion_GetCurrentCodePLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_ApplicationVersion_GetCurrentName(const ovrApplicationVersionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationVersion_GetCurrentNamePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(int)
ovr_ApplicationVersion_GetLatestCode(const ovrApplicationVersionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationVersion_GetLatestCodePLPtr(obj);
	}
	return 0;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_ApplicationVersion_GetLatestName(const ovrApplicationVersionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationVersion_GetLatestNamePLPtr(obj);
	}
	return "";
}
OVRPL_PUBLIC_FUNCTION(long long)
ovr_ApplicationVersion_GetReleaseDate(const ovrApplicationVersionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationVersion_GetReleaseDatePLPtr(obj);
	}
	return 0LL;
}
OVRPL_PUBLIC_FUNCTION(const char *)
ovr_ApplicationVersion_GetSize(const ovrApplicationVersionHandle obj) {
	ovrPlatformInitializeResult result = loaderInitHelper(PLATFORM_PRODUCT_VERSION, PLATFORM_MAJOR_VERSION);
	if (result == ovrPlatformInitialize_Success) {
		return ovr_ApplicationVersion_GetSizePLPtr(obj);
	}
	return "";
}
#endif