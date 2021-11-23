#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

double uniform(double x_min, double x_max, int y_min, int y_max, float x);

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    // 获取灰度图
    Mat gray;
    cvtColor(img, gray, COLOR_RGB2GRAY);

    // 获取直方图
    Mat hist;
    const int channels[1] = {0};
    float inRanges[2] = {0, 255};
    const float *ranges[1] = {inRanges};
    const int bins[1] = {256};
    calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);
    // std::cout << hist << std::endl; // 1-D array
    // std::cout << "hist type=" << hist.type() << std::endl; // 5 CV_32F

    // 绘制直方图
    const int hist_w = 512;
    const int hist_h = 400;
    const int width = 2;
    Mat histImg = Mat::zeros(hist_h, hist_w, CV_8UC3);
    for (size_t i = 0; i < hist.rows; ++i)
    {
        // 绘制实心矩形
        double minVal, maxVal;
        Point minIdx, maxIdx;
        minMaxLoc(hist, &minVal, &maxVal, &minIdx, &maxIdx);
        float hist_at_i_nums = uniform(minVal, maxVal, 0, hist_h, hist.at<float>(i));
        rectangle(histImg, Point(width * i, hist_h), Point(width * (i + 1), hist_h - cvRound(hist_at_i_nums)), Scalar(255, 255, 255), -1);
    }

    namedWindow("histImg", WINDOW_NORMAL);
    imshow("histImg", histImg);
    imshow("gray", gray);
    imshow("img", img);
    waitKey(0);

    return 0;
}

double uniform(double x_min, double x_max, int y_min, int y_max, float x)
{
    double k = (y_max - y_min) / static_cast<double>(x_max - x_min);
    return y_min + k * (x - x_min) + 1;
}
