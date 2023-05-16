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

int bright_contr_students (){
    
    double alpha;
    string imagePath;
    bool imageEmpty=false;
    Mat image;
    

    //reading the image and creating a new image matrix
    
    
    do {
        
        cout << "Enter the path to the image: ";
        cin >> imagePath;
        image= imread(imagePath);
        
        if (image.empty() || image.empty())
            {
                cout << "Could not open or find the images" << endl;
                imageEmpty=false;
            }
        else imageEmpty=true;
    }
    while (imageEmpty==false);
    
    Mat lightenDarken_image = Mat::zeros(image.size(), image.type());
    
    //asking for alpha [1.0-3.0] and beta values [0-100]
    
    do {
        cout << "Enter alpha value [-100 and 100]: ";
        cin >> alpha;
    }
    while ( alpha < -100 || alpha > 100);
    
    
        
    for(int y = 0; y < image.rows; y++) {
        for(int x = 0; x < image.cols; x++) {
            for(int c = 0; c < image.channels(); c++) {
                lightenDarken_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>(( image.at<Vec3b>(y,x)[c] ) + alpha );
           }
        }
    }
    
    //create windows
    
    namedWindow("Original Image", WINDOW_NORMAL);
    namedWindow("New Image", WINDOW_NORMAL);
    
    //show original and new image
 
    imshow("Original Image", image);
    imshow("New Image", lightenDarken_image);
    
    
    waitKey();
    return 0;
}
