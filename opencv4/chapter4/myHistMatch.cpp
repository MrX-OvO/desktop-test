#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
using namespace cv;

void drawHist(const int hist_w, const int hist_h, const int width, Mat &hist, int type, std::string name)
{
    Mat histImg = Mat::zeros(hist_w, hist_h, CV_8UC3);
    normalize(hist, hist, 1.0, 0.0, type, -1, noArray());
    for (size_t i = 0; i < hist.rows; ++i)
    {
        // 绘制实心矩形
        rectangle(histImg, Point(width * i, hist_h), Point(width * (i + 1), hist_h - cvRound(hist_h * hist.at<float>(i))), Scalar(255, 255, 255), -1);
    }
    imshow(name, histImg);
}

int main(int argc, char const *argv[])
{
    // 读取两幅图
    Mat img1 = imread("../lena.png", IMREAD_GRAYSCALE);
    Mat img2 = imread("../peppers.bmp", IMREAD_GRAYSCALE);
    if (img1.empty() || img2.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    // 获取图像直方图
    Mat hist1, hist2;
    const int channels[] = {0};
    const int histSize[] = {256};
    float inRanges[] = {0, 255};
    const float *ranges[] = {inRanges};
    calcHist(&img1, 1, channels, Mat(), hist1, 1, histSize, ranges);
    calcHist(&img2, 1, channels, Mat(), hist2, 1, histSize, ranges);

    // 归一化直方图并显示归一化后的直方图
    const int hist_w = 512;
    const int hist_h = 512;
    const int width = 2;
    drawHist(hist_w, hist_h, width, hist1, NORM_L1, "hist1");
    drawHist(hist_w, hist_h, width, hist2, NORM_L1, "hist2");

    // 计算两幅图像直方图的累计概率
    std::vector<float> hist1_cdf = {hist1.at<float>(0)};
    std::vector<float> hist2_cdf = {hist2.at<float>(0)};
    for (size_t i = 1; i < 256; ++i)
    {
        hist1_cdf.emplace_back(hist1_cdf.back() + hist1.at<float>(i));
        hist2_cdf.emplace_back(hist2_cdf.back() + hist2.at<float>(i));
    }

    // 构建累计概率误差矩阵
    std::vector<std::vector<float>> diff_cdf;
    for (size_t i = 0; i < 256; ++i)
    {
        std::vector<float> tmp;
        for (size_t j = 0; j < 256; ++j)
        {
            tmp.emplace_back(fabs(hist1_cdf[i] - hist2_cdf[j]));
        }
        diff_cdf.emplace_back(tmp);
        tmp.clear();
    }

    // 生成LUT(Look-Up-Table)
    Mat lut(1, 256, CV_8U);
    for (size_t i = 0; i < 256; ++i)
    {
        // 查找原灰度级为i的映射灰度
        // 与i的累计概率差值（绝对值）最小的规定化灰度
        auto minIdx = std::min_element(diff_cdf[i].begin(), diff_cdf[i].end()) - diff_cdf[i].begin();
        lut.at<uchar>(i) = static_cast<uchar>(minIdx);
    }

    // 直方图匹配（规定化）
    Mat result, hist3;
    LUT(img1, lut, result);
    imshow("img1", img1);
    imshow("img2", img2);
    imshow("result", result);
    calcHist(&result, 1, channels, Mat(), hist3, 1, histSize, ranges);
    drawHist(hist_w, hist_h, width, hist3, NORM_L1, "hist3");

    waitKey(0);

    return 0;
}
