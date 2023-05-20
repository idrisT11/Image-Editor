
#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef struct{
    cv::Mat Img;
    bool isVisible;
} LayerInfo;

class LayerManager
{
private:
    std::vector<LayerInfo> layerList;

public:
    LayerManager();
    void addLayer(cv::Mat newImage, bool isVisible=false);
    void addLayer(LayerInfo layerInfo);
    bool removeLayer(int index);

    void setVisibility(int index);
    bool toggleVisibility();    //Returns the new visibility value

    cv::Mat getImageFromLayers();
};

#endif // LAYERMANAGER_H
