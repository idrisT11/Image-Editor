#include <opencv2/opencv.hpp>
#include <iostream>
#include "ImageTransformer.h"

Mat ImageTransformer::drawPoint(Mat& img, Point p, const cv::Scalar& color, int thickness)
{
    Mat out = img;

    circle( out, p, thickness, color, thickness);

    return out;
}

Mat ImageTransformer::resize(Mat& img, double scaleX, double scaleY)
{
    // Read source image
    Mat out = img;

    // Scaling up the image 2 times
    cv::resize(img, out,  Size(), scaleX, scaleY, INTER_LINEAR);

    return out;
}

Mat ImageTransformer::canny(Mat& img, double lowThreshold, double highThreshold, int kernelSize)
{
    // Read source image
    Mat out = img;

    // Perform Canny edge detection
    cv::Canny(img, out, lowThreshold, highThreshold, kernelSize);

    return out;

}

Mat ImageTransformer::LightenDarken (Mat& image, double lightIntensity){
    

    //creating a new image matrix

    Mat lightenDarken_image = Mat::zeros(image.size(), image.type());
    
    for(int y = 0; y < image.rows; y++) {
        for(int x = 0; x < image.cols; x++) {
            for(int c = 0; c < image.channels(); c++) {
                lightenDarken_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>(( image.at<Vec3b>(y,x)[c] ) + lightIntensity );
           }
        }
    }
    return lightenDarken_image;
}
