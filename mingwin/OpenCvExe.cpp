/////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////

/*


toolchainr -> ucrt64


*/

/////////////////////////////////////////////////////////


#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>


#define DLL_EXPORT extern "C" __declspec(dllexport) __stdcall __cdecl

using namespace std;

std::vector<std::string> detectShapes(const cv::Mat& inputImage) {
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
            shape = "Triángulo";
        } else if (approx.size() == 4) {
            // Calculate bounding rectangle and aspect ratio
            cv::Rect rect = cv::boundingRect(approx);
            double aspectRatio = static_cast<double>(rect.width) / rect.height;
            shape = (aspectRatio >= 0.95 && aspectRatio <= 1.05) ? "Cuadrado" : "Rectángulo";
        } else if (approx.size() > 4) {
            shape = "Círculo";
        }

        if (!shape.empty()) {
            shapes.push_back(shape);
        }
    }

    // Return the detected shapes
    return shapes;
}

int main()
{
    const char * result = "OK";

    cv::Mat image = cv::imread("image.png");
    
    if (image.empty()) {
        std::cerr << "Could not read the image!" << std::endl;
        result =  "Could not read the image 'image.png'";
        return 1;
    }
    
    
    // Detect shapes in the image
    std::vector<std::string> shapes = detectShapes(image);

    // Print the detected shapes
    std::cout << "Detected shapes:" << std::endl;
    for (const std::string& shape : shapes) {
        //std::cout << "- " << shape << std::endl;
        result = shape.c_str();
    }

    return 0;
}



