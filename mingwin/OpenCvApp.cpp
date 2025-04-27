/////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////

/*


https://github.com/thommyho/Cpp-OpenCV-Windows-PreBuilts

*/

/////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
   
    cv::Mat img = cv::imread("image.png");
    
    if (img.empty()) {
        std::cerr << "Could not read the image!" << std::endl;
        return 1;
    }
    
    cv::imshow("Display window", img);
    cv::waitKey(0); // Wait for a keystroke in the window
   
    return 0;
}

