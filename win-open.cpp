
#include <iostream>
#include <windows.h>
#include <shellapi.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: open file" << std::endl;

        return 1;
    }

    LPCSTR filePath = argv[1];

    auto result = (INT_PTR) ShellExecuteA(
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
        msg = "File not found.";
        break;
    case SE_ERR_ACCESSDENIED:
        msg = "Access denied.";
        break;
    case SE_ERR_NOASSOC:
    case SE_ERR_ASSOCINCOMPLETE:
        msg = "Cannot find a program associated with this file.";
        break;
    default:
        msg = "Could not open the file.";
    }

    if (msg != nullptr) {
        std::cerr << msg << std::endl;
    }

    return 2;
}

