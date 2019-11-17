#include "../../Header Files/XiNject0r.h"

BOOL fnSetSePrivilege(
	_In_ BOOL bEnablePrivilege
) {
	TOKEN_PRIVILEGES tPriv;
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		tPriv.PrivilegeCount = 1;
		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tPriv.Privileges[0].Luid)) {
			if (bEnablePrivilege) {
				tPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			} else {
				tPriv.Privileges[0].Attributes = FALSE;
			}

			if (!AdjustTokenPrivileges(hToken, FALSE, &tPriv, NULL, NULL, NULL)) {
				if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
					return 3;
				}
			}
		} else {
			return 2;
		}
	} else {
		return 1;
	}

	return 0;
}