#include "Console.h"
#include "Vars.h"

string RandExe(string::size_type length)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#%^&*()";

	thread_local static mt19937 rg{ random_device{}() };
	thread_local static uniform_int_distribution<string::size_type> pick(0, sizeof(chrs) - 2);

	string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s + ".exe";
}

std::string path()
{
	char shitter[_MAX_PATH]; // defining the path
	GetModuleFileNameA(NULL, shitter, _MAX_PATH); // getting the path
	return std::string(shitter); //returning the path
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	char title[256];
	GetWindowText(hwnd, title, sizeof(title));
	if (strlen(title) > 0) {  // Only log windows with titles
		Log(title);
	}
	return TRUE;  // Continue enumeration
}

void Start() {
	rndmTitle();
	SetConsoleSize();
	//rename(path().c_str(), RandExe(15).c_str());
}


void StartCheat() {
	SetConsoleTitleW(L"Chrome Browser.exe");
	//EnumWindows(EnumWindowsProc, 0); //Fortnite (protected by FGuard)
	Log("Waiting for Fortnite from Nova Launcher");
	while (hwnd == NULL) {
		hwnd = FindWindowA(0, GameName);
		Sleep(100);
	}
	pid = Mem::GetProcId(ExecutableName);
	baseaddress = Mem::GetModuleBaseAddress(pid, ExecutableName);

	Log("Found Fortnite\n PID: " + to_string(pid) + "\n Base Address: " + to_string(static_cast<uint64_t>(baseaddress)));



	while (true) {
		Sleep(10);
	}
}

int main()
{
	Start();
Beginning:
	system("cls");
	Log("Welcome to Rj's Loader", 2);
	Log("Please select an option");
	Log("---------------------------------");
	Log("[0] Exit");
	Log("[1] Start Cheeto");
	Log("[2] Blue Screen");
	
	int option;
	cin >> option;

	switch (option) {
	case 1:
		system("cls");
		Log("Starting Cheeto", 2);
		StartCheat();
	case 2:
		system("cls");
		Log("Blue Screening", 5);
		Sleep(1000);
		//BlueScreen();
		goto Beginning;

	case 5:

	case 0:
		system("cls");
		Log("Exiting");
		Sleep(900);
		exit(0);
	default:
		Log("Invalid input...", 7);
		Sleep(1500);
		goto Beginning;
	}
}