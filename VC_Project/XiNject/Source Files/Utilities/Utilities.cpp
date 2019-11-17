#include "../../Header Files/XiNject.h"

DWORD fnGetProcPidbyNameW(
	_In_ PCWSTR lpProcName
) {
	PROCESSENTRY32W pe32;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	pe32.dwSize = sizeof(pe32);

	do {
		if (!lstrcmpW(pe32.szExeFile, lpProcName)) {
			DWORD dwPID = pe32.th32ProcessID;

			CloseHandle(hSnap);
			return dwPID;
		}
	} while (Process32Next(hSnap, &pe32));

	CloseHandle(hSnap);
	return FALSE;
}