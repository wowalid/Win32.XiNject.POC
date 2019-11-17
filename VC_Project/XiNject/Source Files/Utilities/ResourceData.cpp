#include "../../Header Files/XiNject.h"

const WCHAR szCharSet[] = {
	L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	L"abcdefghijklmnopqrstuvwxyz"
	L"1234567890"
};
const SIZE_T ulCharSet = (sizeof(szCharSet) - sizeof(WCHAR)) / sizeof(WCHAR);