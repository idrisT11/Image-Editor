
#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class HistoryManager
{
private:
    std::vector<cv::Mat> imageHistory;
    std::vector<cv::Mat> undidImageHistory;

public:
    HistoryManager();
    void pushAction(cv::Mat m);
    cv::Mat undoAction(cv::Mat currentAction);
    cv::Mat redoAction(cv::Mat currentAction);
};

#endif // LAYERMANAGER_H
