
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include "win-open.h"

/*
Opens a file using the associated program.

Return: 0 if successful, 1 otherwise.
*/
int open_file(LPCSTR filePath)
{
    auto result = (INT_PTR)ShellExecuteA(
        NULL,
        "open",
        filePath,
        NULL,
        NULL,
        SW_SHOWNORMAL
    );

    if (result > 32) {
        return 0;  //All good
    }

    const char* msg = NULL;

    switch (result) {
    case ERROR_FILE_NOT_FOUND:
    case ERROR_PATH_NOT_FOUND:
        msg = "File not found";
        break;
    case SE_ERR_ACCESSDENIED:
        msg = "Access denied";
        break;
    case SE_ERR_NOASSOC:
    case SE_ERR_ASSOCINCOMPLETE:
        msg = "Cannot find a program associated with this file";
        break;
    default:
        msg = "Could not open the file";
    }

    if (msg != nullptr) {
        std::cerr << msg << ": " << filePath << ". Error: " << result << std::endl;
    }

    return 1;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: open files..." << std::endl;

        return 1;
    }

    int num_failures = 0;

    for (int i = 1; i < argc; ++i) {
        LPCSTR filePath = argv[i];

        num_failures += open_file(filePath);
    }

    return num_failures;
}

