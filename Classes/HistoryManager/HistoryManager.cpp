
#include "Classes/HistoryManager/HistoryManager.h"
#include <iostream>

HistoryManager::HistoryManager()
{

}

void HistoryManager::pushAction(cv::Mat m)
{
    this->imageHistory.push_back(m);
    this->undidImageHistory.clear();
}

cv::Mat HistoryManager::undoAction(cv::Mat currentAction)
{
    if(!this->imageHistory.empty())
    {
        cv::Mat previousAction = this->imageHistory.back();
        this->imageHistory.pop_back();

        this->undidImageHistory.push_back(currentAction);

        return previousAction;
    }
    else
    {
        return currentAction;
    }
}

cv::Mat HistoryManager::redoAction(cv::Mat currentAction)
{
    if(!this->undidImageHistory.empty())
    {
        cv::Mat nextAction = this->undidImageHistory.back();
        undidImageHistory.pop_back();

        imageHistory.push_back(currentAction);

        return nextAction;
    }
    else
    {
        return currentAction;
    }
}
