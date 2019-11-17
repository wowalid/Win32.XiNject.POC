#include "../../XiNject/Header Files/XiNject.h"

INT __stdcall wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PWSTR     lpCmdLine,
	_In_     INT       nShowCmd
) {
	INT nArgs;
	PWSTR* szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (!szArglist) {
		return EXIT_FAILURE;
	}
	HANDLE hHeap = GetProcessHeap();
	if (!hHeap) {
		return EXIT_FAILURE;
	}

	WCHAR szCd[MAX_PATH];
	if (!GetCurrentDirectoryW(MAX_PATH, szCd)) {
		return EXIT_FAILURE;
	}
	WCHAR szMfn[MAX_PATH];
	if (!GetModuleFileNameW(NULL, szMfn, MAX_PATH)) {
		return EXIT_FAILURE;
	}

	if ((nArgs > 1) && (!lstrcmpW(szArglist[1], L" "))) {

	}

	return EXIT_SUCCESS;
}