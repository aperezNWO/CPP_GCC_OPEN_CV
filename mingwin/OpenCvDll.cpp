
///////////////////////////////////////////////////////////////////
// Application CPP_GCC_OPEN_CV v[1.0.1]
///////////////////////////////////////////////////////////////////
/*
    1) Toolchain :  MSYS MINGW64 

    2) pacman -S mingw-w64-x86_64-opencv

    3) Path to Generated Files:
        a) C:\msys64\mingw64\bin
        b) C:\msys64\mingw64\include\opencv2

    4) Dynamic ompilation Command  [STATIC IS NOT POSSIBLE] :

    cd /c/Users/pablo.perez/dev/cpp/CPP_GCC_OPEN_CV/src/mingwin

    g++ -shared -m64 -o OpenCvDll.dll OpenCvDll.cpp OpenCvDll.def \
        -I/mingw64/include/opencv2 \
            -Wl,--start-group $(pkg-config --cflags  --libs opencv4)  -Wl,--end-group \
            -lopencv_gapi -lz -llibjpeg -llibpng -lopengl32 -lglu32 -lgdi32 -luser32 -lole32 -lopencv_ccalib -lopencv_cvv   -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_stitching  -lopencv_alphamat  -lopencv_aruco -lopencv_bgsegm  -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_ovis -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_signal -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core -lpthread

    5) CMAKE

        md build && cd build

        // dos / powershell

        cmake -G "MinGW Makefiles" ^
            -DCMAKE_C_COMPILER="C:/msys64/mingw64/bin/gcc.exe" ^
            -DCMAKE_CXX_COMPILER="C:/msys64/mingw64/bin/g++.exe" ^
            ..

        // msys

        cmake -G "MinGW Makefiles" \
            -DCMAKE_C_COMPILER="C:/msys64/mingw64/bin/gcc.exe" \
            -DCMAKE_CXX_COMPILER="C:/msys64/mingw64/bin/g++.exe" \
            ..

        mingw32-make


    6) CMAKE -> INTEGRACION CONTINUA

        A) (MODIFICAR ARCHIVOS *.CPP)
        B) (dentro de la carpate "build")  mingw32-make
        C) output en carpeta \bin
        C) Publicar via FTP

*/

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "OpenCvDll.h"

//
OpenCvApp::OpenCvApp() {
	//
	ReadConfigFile();
}
//
OpenCvApp::~OpenCvApp() {
	//
}
//
const char* OpenCvApp::GetOpenCvAPIVersion() {
    std::string version = cv::getVersionString();
    char* copy = new char[version.size() + 1];
    strcpy(copy, version.c_str());
    return copy; // Llama delete[] después de usarla!
}
//
const char*  OpenCvApp::GetOpenCvAppVersion() {
	//
	return this->configMap["DLL_VERSION"].c_str();
}
//
const char* OpenCvApp::OpenCvReadImage() {
	const char * result = "OK";

	cv::Mat image = cv::imread("image.png");

	if (image.empty()) {
		std::cerr << "Could not read the image!" << std::endl;
		return "Could not read the image 'image.png'";
	}

	// Detect shapes in the image
	std::vector<std::string> shapes = detectShapes(image);

	// Print the detected shapes
	std::cout << "Detected shapes:" << std::endl;
	for (const std::string& shape : shapes) {
		//std::cout << "- " << shape << std::endl;
		result = shape.c_str();
	}

	return result;
}
//
const char* OpenCvApp::OpenCvReadImagePath(char* path) {
	const char * result = "OK";

	cv::Mat image = cv::imread(path);

	if (image.empty()) {
		std::cerr << "Could not read the image!" << std::endl;
		return "Could not read the image 'image.png'";
	}

	// Detect shapes in the image
	std::vector<std::string> shapes = detectShapes(image);

	// Print the detected shapes
	std::cout << "Detected shapes:" << std::endl;
	for (const std::string& shape : shapes) {
		//std::cout << "- " << shape << std::endl;
		result = shape.c_str();
	}

	return result;
}
//
std::vector<std::string> OpenCvApp::detectShapes(const cv::Mat& inputImage) {
	std::vector<std::string> shapes;

	// Ensure the input image is valid
	if (inputImage.empty()) {
		std::cerr << "Error: Input image is empty!" << std::endl;
		return shapes;
	}

	// Create matrices for grayscale and edges
	cv::Mat gray, edges;

	// Convert the input image to grayscale
	cv::cvtColor(inputImage, gray, cv::COLOR_BGR2GRAY);

	// Apply Canny edge detector
	cv::Canny(gray, edges, 50, 150, 3, false);

	// Find contours
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(edges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// Iterate over contours and classify shapes
	for (size_t i = 0; i < contours.size(); ++i) {
		std::vector<cv::Point> contour = contours[i];
		std::vector<cv::Point> approx;

		// Approximate the contour to a polygon
		double epsilon = 0.04 * cv::arcLength(contour, true);
		cv::approxPolyDP(contour, approx, epsilon, true);

		std::string shape;
		if (approx.size() == 3) {
			shape = "[Triángulo]";
		} else if (approx.size() == 4) {
			// Calculate bounding rectangle and aspect ratio
			cv::Rect rect = cv::boundingRect(approx);
			double aspectRatio = static_cast<double>(rect.width) / rect.height;
			shape = (aspectRatio >= 0.95 && aspectRatio <= 1.05) ? "[Cuadrado]" : "[Rectángulo]";
		} else if (approx.size() > 4) {
			shape = "[Círculo]";
		}

		if (!shape.empty()) {
			shapes.push_back(shape);
		}
	}

	// Return the detected shapes
	return shapes;
}
//
int          OpenCvApp::ReadConfigFile() {
	// Open the configuration file
	std::ifstream configFile("opencv.ini");

	// Check if the file is opened successfully
	if (!configFile.is_open()) {
		std::cerr << "Error opening the configuration file." << std::endl;
		return 1;
	}

	// Read the file line by line
	std::string line = "";
	while (std::getline(configFile, line)) {
		// Skip empty lines or lines starting with '#' (comments)
		if (line.empty() || line[0] == '#') {
			continue;
		}

		// Split the line into key and value
		std::istringstream iss(line);
		std::string key, value;
		if (std::getline(iss, key, '=') && std::getline(iss, value)) {
			// Trim leading and trailing whitespaces from key and value
			key.erase(0, key.find_first_not_of(" \t"));
			key.erase(key.find_last_not_of(" \t") + 1);
			value.erase(0, value.find_first_not_of(" \t"));
			value.erase(value.find_last_not_of(" \t") + 1);

			// Insert key-value pair into the map
			this->configMap[key] = value;
		}
	}

	// Close the configuration file
	configFile.close();

	//
	return 0;
}

////////////////////////////////////////////////////////////////
// DLL ENTRY POINTS
////////////////////////////////////////////////////////////////

//
DLL_EXPORT const char* GetOpenCvAPIVersion() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->GetOpenCvAPIVersion();
}

//
DLL_EXPORT const char* GetOpenCvAppVersion() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->GetOpenCvAppVersion();
}

//
DLL_EXPORT const char* OpenCvReadImage() {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->OpenCvReadImage();
}

//
DLL_EXPORT const char* OpenCvReadImagePath(char* path) {
	//
	std::unique_ptr<OpenCvApp> uniquePtr = std::make_unique<OpenCvApp>();
	//
	return uniquePtr->OpenCvReadImagePath(path);
}


////////////////////////////////////////////////////////////////
// MAIN PROGRAM TEST
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////