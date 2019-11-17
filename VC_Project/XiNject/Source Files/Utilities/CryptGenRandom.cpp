#include "../../Header Files/XiNject.h"

INT fnCryptGenRandomNumber(VOID) {
	INT nRN;
	if (BCryptGenRandom(NULL, (PBYTE)& nRN, sizeof(nRN), BCRYPT_USE_SYSTEM_PREFERRED_RNG)) {
		return FALSE;
	}

	return nRN & 0x7fffffff;
}

PWSTR fnCryptGenRandomStringW(
	_In_opt_ HANDLE hHeap,
	_In_opt_ PWSTR  lpBuffer,
	_In_     INT    nBufferSize,
	_In_     PCWSTR lpCharSet,
	_In_     SIZE_T nCharSetSize
) {
	if (!lpBuffer) {
		if (hHeap) {
			lpBuffer = (PWSTR)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, nBufferSize + 1);
		}
	} if (lpBuffer) {
		ZeroMemory(lpBuffer, (nBufferSize + 1) * sizeof(WCHAR));

		for (INT i = 0; i < nBufferSize; i++) {
			lpBuffer[i] = lpCharSet[fnCryptGenRandomNumber() % nCharSetSize];
		}

		return lpBuffer;
	} else {
		return nullptr;
	}
}