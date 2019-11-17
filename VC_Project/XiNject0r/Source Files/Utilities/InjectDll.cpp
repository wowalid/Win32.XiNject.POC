#include "../../Header Files/XiNject0r.h"

BOOL fnInjectDllRThreadW(
	_In_ PCWSTR lpDllName,
	_In_ DWORD  dwProcId
) {
	// Calculate the number of bytes needed for the DLL's pathname
	SIZE_T dwSize = (lstrlenW(lpDllName) + 1) * sizeof(WCHAR);

	// Get process handle passing in the process ID
	HANDLE hProc = OpenProcess(
		PROCESS_QUERY_INFORMATION |
		PROCESS_CREATE_THREAD |
		PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE,
		FALSE, dwProcId);
	if (!hProc) {
		return 1;
	}

	// Allocate space in the remote process for the pathname
	PVOID lpDllRemote = VirtualAllocEx(hProc, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (!lpDllRemote) {
		return 2;
	}

	// Copy the DLL's pathname to the remote process address space
	BOOL dwN = WriteProcessMemory(hProc, lpDllRemote, (PVOID)lpDllName, dwSize, NULL);
	if (!dwN) {
		return 3;
	}

	// Get the real address of LoadLibraryW in Kernel32.dll
	PTHREAD_START_ROUTINE pfnThread = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleW(L"Kernel32"), "LoadLibraryW");
	if (!pfnThread) {
		return 4;
	}

	// Create a remote thread that calls LoadLibraryW(DLLPathname)
	HANDLE hThread = CreateRemoteThread(hProc, NULL, NULL, pfnThread, lpDllRemote, NULL, NULL);
	if (!hThread) {
		return 5;
	}

	// Wait for the remote thread to terminate
	WaitForSingleObject(hThread, INFINITE);

	// Free the remote memory that contained the DLL's pathname and close Handles
	if (lpDllRemote) {
		VirtualFreeEx(hProc, lpDllRemote, 0, MEM_RELEASE);
	} if (hThread) {
		CloseHandle(hThread);
	} if (hProc) {
		CloseHandle(hProc);
	}

	return 0;
}