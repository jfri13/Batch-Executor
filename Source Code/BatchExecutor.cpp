/*
 * Title: Batch Executor
 * Language: C++
 * Version: 1.0
 */
#include <iostream>
#include <Windows.h>
#include <locale>
#include <io.h>
using namespace std;

int main()
{
	char fullpath[MAX_PATH] {};
    GetModuleFileNameA(nullptr, fullpath, MAX_PATH);

	char convert_ext[4] = "BAT";

	int fullpath_index = sizeof(fullpath) / sizeof(char);
	int last_index = 0;
	int last_period_index = 0;
	int last_backslash_index = 0;

	for (int i = MAX_PATH; i > 0; i--) {
		if (fullpath[i - 1] != NULL && last_index == 0) {
			last_index = i;
		}
		else if (fullpath[i - 1] == '.' && last_period_index == 0) {
			last_period_index = i;
		}
		else if (fullpath[i - 1] == '\\' && last_backslash_index == 0) {
			last_backslash_index = i;
		}
		if (last_index != 0 && last_period_index != 0 && last_backslash_index != 0) {
			break;
		}
	}
	for (int i = 0; i < sizeof(convert_ext) / sizeof(char) - 1; i++) {
		fullpath[last_period_index + i] = convert_ext[i];
	}

	//파일이 있다면 IF FILE EXISTS
	if (_access(fullpath, 0) == 0) {
		last_index += 3;
		char* batFullpath = new char[last_index] {'\"', };
		strcat_s(batFullpath, last_index, fullpath);
		strcat_s(batFullpath, last_index, "\"");

		system(batFullpath); //실행부 RUN BATCH FILE
		delete[] batFullpath;
	}
	//에러메세지 ERROR MESSAGE
	else {
		char* path = new char[last_backslash_index] {};
		char* filename = new char[last_index - last_backslash_index + 1] {};

		for (int i = 0; i < last_index; i++) {
			if (i < last_backslash_index - 1) {
				path[i] = fullpath[i];
			}
			else if (i > last_backslash_index - 1) {
				filename[i - last_backslash_index] = fullpath[i];
			}
		}

		LANGID winId = GetUserDefaultUILanguage();
		//한글
		if ((winId & 0xff) == LANG_KOREAN) {
			cout << "\"" << path << "\"에 \"" << filename << "\"이 없습니다." << endl;
			system("PAUSE");
			delete[] path;
			delete[] filename;
			exit(0);
		}
		//English
		cout << "There is no \"" << filename << "\" in \"" << path << "\"." << endl;
		system("PAUSE");
		delete[] path;
		delete[] filename;
	}
}
