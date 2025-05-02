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



/*

/////////////////////////////////////////////////////////
// MSYS
/////////////////////////////////////////////////////////

g++ -o  OpenCvTest.exe OpenCvTest.cpp 


*/

#include <iostream>
#include <windows.h>

// Define the function signature from the DLL
typedef const char* (__stdcall *OpenCvReadImageFunc)();

int main() {
    // Load the DLL
    HINSTANCE hDll = LoadLibraryW(L"OpenCvDll.dll");

    if (hDll == nullptr) {
        std::cerr << "Error: Could not load OpenCvDll.dll" << std::endl;
        return 1;
    }

    std::cout << "OpenCvDll.dll loaded successfully." << std::endl;

    // Get the address of the exported function
    OpenCvReadImageFunc openCvReadImage = (OpenCvReadImageFunc)GetProcAddress(hDll, "OpenCvReadImage");

    if (openCvReadImage == nullptr) {
        std::cerr << "Error: Could not find function 'OpenCvReadImage' in the DLL." << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    std::cout << "Function 'OpenCvReadImage' found." << std::endl;

    // Call the function from the DLL
    const char* result = openCvReadImage();

    // Print the result
    std::cout << "Result from OpenCvReadImage: " << result << std::endl;

    // Free the DLL
    FreeLibrary(hDll);
    std::cout << "OpenCvDll.dll unloaded." << std::endl;

    return 0;
}
