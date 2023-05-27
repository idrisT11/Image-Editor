#include <opencv2/opencv.hpp>
#include <iostream>
#include "ImageTransformer.h"

#include <opencv2/highgui.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <cstdlib>

using namespace cv;
using namespace cv::face;
using namespace std;
namespace fs = std::filesystem;

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

//===========================================================================
//Mathematical morphology -------------------------------------------------------------------
//===========================================================================

Mat ImageTransformer::erosion(Mat& img, int kernel_type)
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

Mat ImageTransformer::dilatation(Mat& img, int kernel_type)
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
//Filters -------------------------------------------------------------------
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

    if (filter == 1) {
        // Apply Gaussian kernel (5x5)
        cv::GaussianBlur(grayImg, out, cv::Size(5, 5), 0);
    }

    if (filter == 2){
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


//training function
void ImageTransformer::trainingData(){
    
    cv::setUseOptimized(false);
    
    // Path to the directory containing the face images for training
    string trainingDataPath = "training_data_path";

    // Create a vector to hold the training images
    vector<Mat> images;

    // Create a vector to hold the corresponding labels for each image
    vector<int> labels;

    DIR* dir;
    struct dirent* entry;

    // Open the training data directory
    dir = opendir(trainingDataPath.c_str());
    if (dir != nullptr)
        {
            while ((entry = readdir(dir)) != nullptr)
            {
                if (entry->d_type == DT_DIR)
                {
                    string dirName = entry->d_name;
                    if (dirName != "." && dirName != "..")
                    {
                        int label = stoi(dirName);
                        string subDirPath = trainingDataPath + "/" + dirName;

                        DIR* subDir;
                        struct dirent* subEntry;

                        // Open the subdirectory
                        subDir = opendir(subDirPath.c_str());
                        if (subDir != nullptr)
                        {
                            while ((subEntry = readdir(subDir)) != nullptr)
                            {
                                if (subEntry->d_type == DT_REG)
                                {
                                    string imagePath = subDirPath + "/" + subEntry->d_name;

                                    // Read the image and convert it to grayscale
                                    Mat image = imread(imagePath, IMREAD_GRAYSCALE);
                                    if (!image.empty())
                                    {
                                        images.push_back(image);
                                        labels.push_back(label);
                                    }
                                }
                            }
                            closedir(subDir);
                        }
                    }
                }
            }
            closedir(dir);
        }

        // Create the face recognizer object
        Ptr<LBPHFaceRecognizer> recognizer = LBPHFaceRecognizer::create();

        // Train the recognizer using the training images and labels
        recognizer->train(images, labels);

        // Save the trained recognizer to a file
        recognizer->save("path/to/trained_recognizer.yml");

        cout << "Training completed and recognizer model saved." << endl;
    
}



// Function to detect and recognize faces
void ImageTransformer::detectAndRecognizeFaces(Mat& img, CascadeClassifier& cascade, Ptr<LBPHFaceRecognizer>& recognizer, double scale){
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, gray);
    
    const std::vector<std::string> names = {
         "Alexender Dadario", "Scarlet Johanson", "testChris", "test2"};

    vector<Rect> faces;
    cascade.detectMultiScale(gray, faces, scale, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    for (const Rect& faceRect : faces)
    {
        // Draw rectangle around the face
        rectangle(img, faceRect, Scalar(255, 0, 0), 2);

        // Preprocess the face region for recognition (e.g., resize, convert to grayscale)
        Mat faceROI = gray(faceRect);
        resize(faceROI, faceROI, Size(128, 128));

        // Recognize the face
        int predictedLabel = -1;
        double confidence = 0.0;
        recognizer->predict(faceROI, predictedLabel, confidence);

        // Display the recognized label and confidence
        string label;
        if (predictedLabel != -1)
        {
            // Get the label associated with the predicted face
            label = recognizer->getLabelInfo(predictedLabel);
        }
        else
        {
            label = "Unknown";
        }

        string confidenceStr = "Confidence: " + to_string(confidence);
        putText(img, names[predictedLabel], Point(faceRect.x, faceRect.y - 10), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(0, 255, 0), 2);
        putText(img, confidenceStr, Point(faceRect.x, faceRect.y + faceRect.height + 20), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    }
}

/* int main()
{
    trainingData();

    // Create the face recognizer object
    Ptr<LBPHFaceRecognizer> recognizer = LBPHFaceRecognizer::create();

    // Path to the XML file containing the pre-trained face classifier in opencv
    string cascadePath = "/usr/local/Cellar/opencv/4.7.0_2/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml";//chemin vers haarcascade_frontalface_alt.xml

    // Create the face cascade classifier
    CascadeClassifier cascade;
    if (!cascade.load(cascadePath))
    {
        cerr << "Failed to load cascade classifier." << endl;
        return -1;
    }

    // Load the trained face recognizer from file
    recognizer->read(""path/to/trained_recognizer.yml");

    VideoCapture capture(0);
    if (!capture.isOpened())
    {
        cerr << "Failed to open video capture." << endl;
        return -1;
    }

    // Process frames from the video capture
    Mat frame;
    while (capture.read(frame))
    {
        // Clone the frame for drawing
        Mat frameClone = frame.clone();

        // Detect and recognize faces
        detectAndRecognizeFaces(frameClone, cascade, recognizer, 1.1);

        // Display the frame with detected and recognized faces
        imshow("Face Recognition", frameClone);

        // Break the loop if the 'q' key is pressed
        if (waitKey(1) == 'q')
            break;
    }

    // Release the video capture and destroy windows
    capture.release();
    destroyAllWindows();

    return 0;
}
*/
