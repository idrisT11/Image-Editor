#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
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

    cv::resize(img, out,  Size(), scaleX, scaleY, INTER_LINEAR);

    return out;
}


//===========================================================================
//Mathematical morphology ---------------------------------------------------
//===========================================================================

Mat ImageTransformer::erosion(Mat& img, int kernel_size, int kernel_type)
{
    Mat out;

    int erosion_type = 0;           // Type d'érosion (Rectangle, Croix, Ellipse) stocke le MorphShape correspondant à erosion_elem

    switch(kernel_type){
    case ImageTransformer::MATHMORPH_RECT:                     // Noyau rectangulaire
        erosion_type = MORPH_RECT;
        break;
    case ImageTransformer::MATHMORPH_CROSS:                     // Noyau en croix
        erosion_type = MORPH_CROSS;
        break;
    case ImageTransformer::MATHMORPH_ELLIPSE:                     // Noyau en ellipse
        erosion_type = MORPH_ELLIPSE;
        break;
    default:                    // Sinon : erreur
        //std::cout<<"kernel_type ne correspond pas à une valeur autorisée. Remise à la valeur par défaut : ellipse"<<std::endl;
        erosion_type = MORPH_ELLIPSE;

    }

    // Create kernel
    Mat kernel = getStructuringElement( erosion_type,
                                       Size(2*kernel_size + 1, 2*kernel_size+1),
                                       Point(kernel_size, kernel_size) );

    cv::erode( img, out, kernel);

    return out;
}

Mat ImageTransformer::dilatation(Mat& img, int kernel_size, int kernel_type)
{
    Mat out;

    int dilatation_type = 0;           // Type de dilatation (Rectangle, Croix, Ellipse) stocke le MorphShape correspondant à erosion_elem

    switch(kernel_type){
    case ImageTransformer::MATHMORPH_RECT:                     // Noyau rectangulaire
        dilatation_type = MORPH_RECT;
        break;
    case ImageTransformer::MATHMORPH_CROSS:                     // Noyau en croix
        dilatation_type = MORPH_CROSS;
        break;
    case ImageTransformer::MATHMORPH_ELLIPSE:                     // Noyau en ellipse
        dilatation_type = MORPH_ELLIPSE;
        break;
    default:                    // Sinon : erreur
        //std::cout<<"kernel_type ne correspond pas à une valeur autorisée. Remise à la valeur par défaut : ellipse"<<std::endl;
        dilatation_type = MORPH_ELLIPSE;

    }

    // Create kernel
    Mat kernel = getStructuringElement( dilatation_type,
                                       Size(2*kernel_size + 1, 2*kernel_size+1),
                                       Point(kernel_size, kernel_size) );
    dilate( img, out, kernel);

    return out;
}

//===========================================================================
//Filte----------------------------------------------------------------------
//===========================================================================

Mat ImageTransformer::canny(Mat& img, double lowThreshold, double highThreshold, int kernelSize)
{
    // Read source image
    Mat out = Mat::zeros(img.rows, img.cols, img.type());// = Scalar::all(0);
    Mat whiteBackground(img.rows, img.cols, img.type(), cv::Scalar(255, 255, 255));
    Mat mask;

    // Perform Canny edge detection
    cv::Canny(img, mask, lowThreshold, highThreshold, kernelSize);

    whiteBackground.copyTo( out, mask);

    return out;
}

Mat ImageTransformer::applyFilter(Mat& img, int filter)
{
    // Read source image
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);
    cv::Mat out = grayImg;

    if (filter == GAUSS)
    {
        // Apply Gaussian kernel (5x5)
        cv::GaussianBlur(img, out, cv::Size(5, 5), 0);
    }

    else if (filter == SOBEL)
    {
        // Apply Sobel filter
        cv::Mat gradX, gradY;
        cv::Mat absGradX, absGradY;

        // Apply Sobel operator in the X direction
        cv::Sobel(grayImg, gradX, CV_16S, 1, 0);
        cv::convertScaleAbs(gradX, absGradX);

        // Apply Sobel operator in the Y direction
        cv::Sobel(grayImg, gradY, CV_16S, 0, 1);
        cv::convertScaleAbs(gradY, absGradY);

        // Combine the gradient images using bitwise OR
        cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, out);

        cv::cvtColor(out, out, cv::COLOR_GRAY2BGR);
    }

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
