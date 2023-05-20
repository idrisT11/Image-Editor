#ifndef IMAGETRANSFORMER_H
#define IMAGETRANSFORMER_H
#include <opencv2/opencv.hpp>
#include <iostream>

// Important: Add the opencv includes here
using namespace cv;

class ImageTransformer
{
public:
    static const int GAUSS = 1;
    static const int SOBEL = 2;

    static Mat drawPoint(Mat& img, Point p, const cv::Scalar& color, int thickness = 1);
    static Mat resize(Mat& img, double scaleX = 2 , double scaleY = 2); // resizing the two dimensions by 2
    static Mat canny(Mat& img, double lowThreshold = 50.0, double highThreshold = 150.0, int kernelSize = 3);
    static Mat applyFilter(Mat& img, int filter); // filter 1 = gauss, filter 2 = sobel
    static Mat LightenDarken (Mat& image, double lightIntensity);
};

#endif
