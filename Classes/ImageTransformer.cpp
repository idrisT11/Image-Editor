#include <opencv2/opencv.hpp>
#include <iostream>
#include "ImageTransformer.h"

Mat ImageTransformer::drawPoint(Mat& img, Point p, const cv::Scalar& color, int thickness=1)
{
    Mat out = img;

    circle( out, p, thickness, color, thickness);

    return out;
}

