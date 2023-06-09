#ifndef IMAGETRANSFORMER_H
#define IMAGETRANSFORMER_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face.hpp>
#include <vector>
#include <dirent.h>
#include <cstdlib>
#include <iostream>

// Important: Add the opencv includes here
using namespace cv;
using namespace cv::face;

class ImageTransformer
{
public:
    static const int GAUSS = 1;
    static const int SOBEL = 2;

    static const int MATHMORPH_RECT = 0;
    static const int MATHMORPH_CROSS = 1;
    static const int MATHMORPH_ELLIPSE = 2;

    static Mat drawPoint(Mat& img, Point p, const cv::Scalar& color, int thickness = 1);
    static Mat resize(Mat& img, double scaleX = 2 , double scaleY = 2); // resizing the two dimensions by 2
    static Mat canny(Mat& img, double lowThreshold = 50.0, double highThreshold = 150.0, int kernelSize = 3);
    static Mat applyFilter(Mat& img, int filter); // filter 1 = gauss, filter 2 = sobel
    static Mat LightenDarken (Mat& image, double lightIntensity);
    static Mat dilatation(Mat& img, int kernel_size, int kernel_type=MATHMORPH_ELLIPSE);
    static Mat erosion(Mat& img, int kernel_size, int kernel_type=MATHMORPH_ELLIPSE);
    static Mat detectAndRecognizeFaces(Mat img, CascadeClassifier& cascade, Ptr<cv::face::LBPHFaceRecognizer>& recognizer, double scale);

};

#endif
