#ifndef IMAGETRANSFORMER_H
#define IMAGETRANSFORMER_H

// Important: Add the opencv includes here
using namespace cv;

class ImageTransformer
{
public:
    static Mat drawPoint(Mat& img, Point p, const cv::Scalar& color, int thickness=1);
};

#endif
