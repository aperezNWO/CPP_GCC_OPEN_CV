/////////////////////////////////////////////////////////
// MSYS MINGW64
/////////////////////////////////////////////////////////

/*

g++ -o  OpenCvTest.exe OpenCvTest.cpp 

*/

#include <iostream>
#include <windows.h>

// Define the function signature from the DLL
typedef const char* (__stdcall *OpenCvReadImageFunc)();
typedef const char* (__stdcall *GetOpenCvAPIVersionFunc)();

int main() {
    // Load the DLL
    HINSTANCE hDll = LoadLibraryW(L"OpenCvDll.dll");

    if (hDll == nullptr) {
        std::cerr << "Error: Could not load OpenCvDll.dll" << std::endl;
        return 1;
    }

    std::cout << "OpenCvDll.dll loaded successfully." << std::endl;

    //////////////////////////////////////////////////////////////
    // OpenCvReadImage
    //////////////////////////////////////////////////////////////
 
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

    //////////////////////////////////////////////////////////////
    // GetOpenCvAPIVersionFunc
    //////////////////////////////////////////////////////////////
 
    GetOpenCvAPIVersionFunc getOpenCvAPIVersion = (GetOpenCvAPIVersionFunc)GetProcAddress(hDll, "GetOpenCvAPIVersion");

    if (getOpenCvAPIVersion == nullptr) {
        std::cerr << "Error: Could not find function 'GetOpenCvAPIVersion' in the DLL." << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    std::cout << "Function 'GetOpenCvAPIVersion' found." << std::endl;

    // Call the function from the DLL
    const char* openCVAPIVersion = getOpenCvAPIVersion();

    // Print result
    std::cout << "Result from 'GetOpenCvAPIVersion': " << openCVAPIVersion << std::endl;

    ////////////////////////////////////////////////////////////
    // Free the DLL
    ////////////////////////////////////////////////////////////
    FreeLibrary(hDll);
    std::cout << "OpenCvDll.dll unloaded." << std::endl;

    return 0;
}
