
#include <iostream>
#include <windows.h>
#include <shellapi.h>

bool IsRegularFile(LPCSTR path) {
    DWORD dwAttrib = GetFileAttributesA(path);

    // 1. Check if the path exists at all
    if (dwAttrib == INVALID_FILE_ATTRIBUTES) {
        return false;
    }

    // 2. Ensure it is not a directory
    if (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) {
        return false;
    }

    // Optional: Exclude system/device files if necessary
    // if (dwAttrib & FILE_ATTRIBUTE_DEVICE) return false;

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: open file" << std::endl;

        return 1;
    }

    LPCSTR filePath = argv[1];

    if (IsRegularFile(filePath)) {
        HINSTANCE result = ShellExecuteA(
            NULL,
            "open",
            filePath,
            NULL,
            NULL,
            SW_SHOWNORMAL
        );

        if ((INT_PTR) result <= 32) {
            std::cerr << "Application failed to launch. Error: " << (INT_PTR)result << std::endl;

            return 2;
        }
    }
    else {
        std::cerr << "Error: File does not exist or is a directory." << std::endl;

        return 3;
    }

    return 0;
}

