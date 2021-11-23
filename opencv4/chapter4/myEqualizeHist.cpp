#include <iostream>
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

    Mat gray, hist, hist2;
    cvtColor(img, gray, COLOR_RGB2GRAY);
    Mat equalImg;
    equalizeHist(gray, equalImg); // 直方图均衡化
    const int channels[] = {0};
    const int histSize[] = {256};
    float inRanges[] = {0, 255};
    const float *ranges[] = {inRanges};
    calcHist(&gray, 1, channels, Mat(), hist, 1, histSize, ranges);
    calcHist(&equalImg, 1, channels, Mat(), hist2, 1, histSize, ranges);

    // 绘制直方图
    const int hist_w = 512;
    const int hist_h = 512;
    const int width = 2;
    drawHist(hist_w, hist_h, width, hist, NORM_INF, "hist");
    drawHist(hist_w, hist_h, width, hist2, NORM_INF, "hist2");
    imshow("gray", gray);
    imshow("equalImg", equalImg);
    waitKey(0);

    return 0;
}
