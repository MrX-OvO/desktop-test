#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;

void drawHist(const int hist_w, const int hist_h, const int width, const Mat &hist, int type, std::string name)
{
    Mat histImg = Mat::zeros(hist_w, hist_h, CV_8UC3);
    Mat hist_type;
    normalize(hist, hist_type, 1.0, 0.0, type, -1, noArray());
    for (size_t i = 0; i < hist.rows; ++i)
    {
        // 绘制实心矩形
        rectangle(histImg, Point(width * i, hist_h), Point(width * (i + 1), hist_h - cvRound(hist_h * hist_type.at<float>(i))), Scalar(255, 255, 255), -1);
    }
    imshow(name, histImg);
}

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat gray, hist, gray2, hist2, gray3, hist3;
    cvtColor(img, gray, COLOR_RGB2GRAY);
    resize(gray, gray2, Size(), 0.5, 0.5);
    gray3 = imread("../peppers.bmp", IMREAD_GRAYSCALE);

    const int channels[] = {0};
    const int histSize[] = {256};
    float inRanges[] = {0, 255};
    const float *ranges[] = {inRanges};
    // 图像直方图归一化
    calcHist(&gray, 1, channels, Mat(), hist, 1, histSize, ranges);
    calcHist(&gray2, 1, channels, Mat(), hist2, 1, histSize, ranges);
    calcHist(&gray3, 1, channels, Mat(), hist3, 1, histSize, ranges);
    const int hist_w = 512;
    const int hist_h = 512;
    const int width = 2;
    drawHist(hist_w, hist_h, width, hist, NORM_INF, "hist");
    drawHist(hist_w, hist_h, width, hist2, NORM_INF, "hist2");
    drawHist(hist_w, hist_h, width, hist3, NORM_INF, "hist3");

    // 原图直方图与原图直方图的相关系数
    double hist_hist = compareHist(hist, hist, HISTCMP_CORREL);
    std::cout << "lena_lena = " << hist_hist << std::endl;

    // 原图直方图与缩小原图后直方图的相关系数
    double hist_hist2 = compareHist(hist, hist2, HISTCMP_CORREL);
    std::cout << "lena_lena256 = " << hist_hist2 << std::endl;

    // 两幅不同图像直方图相关系数
    double hist_hist3 = compareHist(hist, hist3, HISTCMP_CORREL);
    std::cout << "lena_peppers = " << hist_hist3 << std::endl;

    waitKey(0);

    return 0;
}
