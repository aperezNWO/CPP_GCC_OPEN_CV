/////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////

/*


0) stable dist files with no qt

    https://github.com/thommyho/Cpp-OpenCV-Windows-PreBuilts

1) exe with no qt files works only on mingwin/x64/mingin/bin directory
2) exe with qt works only on qt\bin dir.
3) Generate and test static dll on "test folder" with no dependencies

*/

/////////////////////////////////////////////////////////

/*

g++ -o OpenCvTest.exe OpenCvTest.cpp -lkernel32

*/

#include <iostream>
#include <windows.h>

// Function pointer type for the DLL function
typedef const char* (__stdcall *OpenCvReadImageFunc)();

int main() {
    // Load the DLL
    HMODULE hDll = LoadLibrary("OpenCvDll.dll");
    if (!hDll) {
        std::cerr << "Failed to load DLL!" << std::endl;
        return 1;
    }

    // Get the address of the exported function
    OpenCvReadImageFunc OpenCvReadImage = (OpenCvReadImageFunc)GetProcAddress(hDll, "OpenCvReadImage");
    if (!OpenCvReadImage) {
        std::cerr << "Failed to find OpenCvReadImage in DLL!" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    // Call the function
    const char* result = OpenCvReadImage();
    std::cout << "Result: " << result << std::endl;

    // Free the DLL
    FreeLibrary(hDll);

    return 0;
}
