//// Compiler/Linker       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//// Libraries             //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma comment(lib, "bcrypt.lib")

//// External Dependencies //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <bcrypt.h>
#include <TlHelp32.h>

//// Arrays/Sizes          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const WCHAR szCharSet[];
extern const SIZE_T ulCharSet;


//// Function Declarations //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CryptGenRandom Utilities //
INT fnCryptGenRandomNumber(
	VOID
);
PWSTR fnCryptGenRandomStringW(
	_In_opt_ HANDLE hHeap,
	_In_opt_ PWSTR  lpBuffer,
	_In_     INT    nBufferSize,
	_In_     PCWSTR lpCharSet,
	_In_     SIZE_T nCharSetSize
);

// Resource Utilities //
BOOL fnExtractResourceW(
	_In_ WORD   wResID,
	_In_ PCWSTR lpResType,
	_In_ PCWSTR lpFileName
);
PVOID fnLoadResourceW(
	_In_  WORD   wResID,
	_In_  PCWSTR lpResType,
	_Out_ PDWORD dwBufferSize
);
BOOL fnSaveResourceW(
	_In_ PCWSTR lpFileName,
	_In_ PVOID  lpBuffer,
	_In_ DWORD  dwBufferSize
);

// Utilities //
DWORD fnGetProcPidbyNameW(
	_In_ PCWSTR lpProcName
);