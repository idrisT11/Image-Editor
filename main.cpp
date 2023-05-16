#include "Classes/ImageTransformer.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{
    Mat img = cv::imread(R"(/Users/romy/Desktop/ISEP/ISEP - A2/Développement des applications multimédia/Projet/Image-Editor/HappyFish.jpg)");

    Mat out = ImageTransformer::resize(img);
    cv::namedWindow("Source", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Resize", cv::WINDOW_AUTOSIZE);
    cv::imshow("Source", img);
    cv::imshow("Resize", out);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
