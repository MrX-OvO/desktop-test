#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#define VNAME(value) (#value)

using namespace cv;

template <typename T>
void printVec(const std::string &vecName, const std::vector<T> &vec)
{
    std::cout << (vecName + " = [");
    for (auto iter = vec.begin(); iter != vec.end();)
        std::cout << *iter++ << (iter == vec.end() ? "]\n" : ", ");
}

int main(int argc, char const *argv[])
{
    std::vector<double> positiveData = {1.0, 4.0, 5.0};
    std::vector<double> normalized_Inf, normalized_L1, normalized_L2, normalized_L2SQR, normalize_MINMAX;

    // 测试不同归一化方法
    normalize(positiveData, normalized_Inf, 1.0, 0.0, NORM_INF);
    printVec(VNAME(normalized_Inf), normalized_Inf);

    normalize(positiveData, normalized_L1, 1.0, 0.0, NORM_L1);
    printVec(VNAME(normalized_L1), normalized_L1);

    normalize(positiveData, normalized_L2, 1.0, 0.0, NORM_L2);
    printVec(VNAME(normalized_L2), normalized_L2);

    //normalize(positiveData, normalized_L2SQR, 1.0, 0.0, NORM_L2SQR);
    //printVec(VNAME(normalized_L2SQR), normalized_L2SQR);

    normalize(positiveData, normalize_MINMAX, 1.0, 0.0, NORM_MINMAX);
    printVec(VNAME(normalize_MINMAX), normalize_MINMAX);

    // 将图像直方图归一化
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat gray, hist;
    cvtColor(img, gray, COLOR_RGB2GRAY);
    const int channels[1] = {0};
    float inRanges[2] = {0, 255};
    const float *ranges[1] = {inRanges};
    const int bins[1] = {256};
    calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);

    const int hist_w = 512;
    const int hist_h = 400;
    const int width = 2;
    Mat histImg_L1 = Mat::zeros(hist_h, hist_w, CV_8UC3);
    Mat histImg_Inf = Mat::zeros(hist_h, hist_w, CV_8UC3);
    Mat hist_L1, hist_Inf;
    normalize(hist, hist_L1, 1.0, 0.0, NORM_L1);
    for (size_t i = 0; i < hist.rows; ++i)
    {
        // 绘制实心矩形
        rectangle(histImg_L1, Point(width * i, hist_h), Point(width * (i + 1), hist_h - cvRound(hist_h * hist_L1.at<float>(i))), Scalar(255, 255, 255), -1);
    }
    normalize(hist, hist_Inf, 1.0, 0.0, NORM_INF);
    for (size_t i = 0; i < hist.rows; ++i)
    {
        // 绘制实心矩形
        rectangle(histImg_Inf, Point(width * i, hist_h), Point(width * (i + 1), hist_h - cvRound(hist_h * hist_Inf.at<float>(i))), Scalar(255, 255, 255), -1);
    }
    imshow("histImg_L1", histImg_L1);
    imshow("histImg_Inf", histImg_Inf);
    waitKey(0);

    return 0;
}
