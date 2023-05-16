#ifndef IMAGETRANSFORMER_H
#define IMAGETRANSFORMER_H
#include <opencv2/opencv.hpp>
#include <iostream>

// Important: Add the opencv includes here
using namespace cv;

class ImageTransformer
{
public:
    static Mat drawPoint(Mat& img, Point p, const cv::Scalar& color, int thickness = 1);
    static Mat resize(Mat& img, double scaleX = 2 , double scaleY = 2); // resizing the two dimensions by 2
};

#endif
