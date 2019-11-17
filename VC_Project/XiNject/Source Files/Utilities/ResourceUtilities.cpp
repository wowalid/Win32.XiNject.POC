#include "../../Header Files/XiNject.h"

BOOL fnExtractResourceW(
	_In_ WORD   wResID,
	_In_ PCWSTR lpResType,
	_In_ PCWSTR lpFileName
) {
	DWORD dwBuffersize;
	PVOID lpBuffer = fnLoadResourceW(wResID, lpResType, &dwBuffersize);
	if (lpBuffer && dwBuffersize) {
		if (fnSaveResourceW(lpFileName, lpBuffer, dwBuffersize)) {
			return TRUE;
		}
	}

	return FALSE;
}

PVOID fnLoadResourceW(
	_In_  WORD   wResID,
	_In_  PCWSTR lpResType,
	_Out_ PDWORD dwBufferSize
) {
	*dwBufferSize = NULL;
	HRSRC hResInfo = FindResourceW(NULL, MAKEINTRESOURCE(wResID), lpResType);
	if (hResInfo) {
		HGLOBAL hResData = LoadResource(NULL, hResInfo);
		if (hResData) {
			PVOID lpBuffer = LockResource(hResData);
			if (!lpBuffer) {
				return nullptr;
			}

			*dwBufferSize = SizeofResource(NULL, hResInfo);
			if (!*dwBufferSize) {
				return nullptr;
			}

			return lpBuffer;
		}
	}

	return nullptr;
}

BOOL fnSaveResourceW(
	_In_ PCWSTR lpFileName,
	_In_ PVOID  lpBuffer,
	_In_ DWORD  dwBufferSize
) {
	HANDLE hFile = CreateFileW(lpFileName, GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	if (hFile) {
		DWORD dwNOBW;
		if (WriteFile(hFile, lpBuffer, dwBufferSize, &dwNOBW, NULL)) {
			CloseHandle(hFile);
			return TRUE;
		} else {
			CloseHandle(hFile);
			return FALSE;
		}
	} else {
		return FALSE;
	}
}