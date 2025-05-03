#ifndef OPENCVDLL_H // include guard
#define OPENCVDLL_H
#endif

#include <fstream>'

#pragma hdrstop
#pragma argsused
#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall __cdecl

using namespace std;

class OpenCvApp
{
    public :
        //
        OpenCvApp();
        ~OpenCvApp();
        //
        const char*              GetOpenCvAppVersion();
        const char*              OpenCvReadImage();
        const char*              OpenCvReadImagePath(char* path);
        std::vector<std::string> detectShapes(const cv::Mat& inputImage) ; 
        //
        int                      ReadConfigFile();
     public :
        //
        map<string, string>      configMap;

};