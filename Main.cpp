#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>

using namespace std;

namespace {
	const int base = 16;
}

string string_reverse(string str) {
	for (int i = 0; i < str.length() / 2; i++) {
		swap(str[i], str[str.length() - i - 1]);
	}

	return str;
}
string file_hash(fstream & fs) {
	size_t m = 2468;
	stringstream res("9A4");

	char c;
	while (fs.get(c)) {
		m = ((m << 5) + m) + c;
	}

	while (m >= base) {
		int ost = m % base;
		m /= base;

		if (ost >= 10) {
			res << (char)(ost + 55);
		}
		else {
			res << ost;
		}
	}

	res << m;

	return string_reverse(res.str());
}

int main() {
	HANDLE hWrite, hRead;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	hRead = CreateFile(
		"testCase.txt",
		GENERIC_READ,
		FILE_SHARE_READ,
		&sa,
		OPEN_EXISTING,
		0,
		NULL
	);

	hWrite = CreateFile(
		"out.txt",
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		&sa,
		CREATE_ALWAYS,
		0,
		NULL
	);

	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	si.hStdInput = hRead;
	si.hStdOutput = hWrite;
	si.dwFlags = STARTF_USESTDHANDLES;

	CreateProcess("numberMethod.exe", NULL, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(hRead);
	CloseHandle(hWrite);

	fstream res("testResults.txt");
	fstream out("out.txt");

	if (file_hash(res) == file_hash(out))
		cout << "All test cases have been passed successfully." << endl;
	else
		cout << "There are some mistakes in out file." << endl;



	system("pause");
	return 0;
}