#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

void drawHist(const int hist_w, const int hist_h, const int width, Mat &hist, int type, std::string name)
{
    Mat histImg = Mat::zeros(hist_w, hist_h, CV_8UC3);
    normalize(hist, hist, 255.0, 0.0, type, -1, noArray());
    namedWindow(name, WINDOW_NORMAL);
    imshow(name, hist);
}

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    Mat sub_img = imread("../lena00.png");
    if (img.empty() || sub_img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }
    imshow("img", img);
    imshow("sub_img", sub_img);

    Mat img_HSV, sub_img_HSV, hist, hist2;
    // 转成HSV空间，提取H、S两个通道
    cvtColor(img, img_HSV, COLOR_RGB2HSV);
    cvtColor(sub_img, sub_img_HSV, COLOR_RGB2HSV);
    int channels[] = {0, 1};                      // 统计的通道索引
    int h_bins = 32, s_bins = 32;                 // H、S通道直方图数组尺寸
    int histSize[] = {h_bins, s_bins};            // 存放每个维度直方图的数组的尺寸
    float h_ranges[] = {0, 180};                  // H通道值的范围为0-179
    float s_ranges[] = {0, 256};                  // S通道值的范围为0-255
    const float *ranges[] = {h_ranges, s_ranges}; // 每个通道的范围
    // 绘制H-S二维直方
    calcHist(&sub_img_HSV, 1, channels, Mat(), hist, 2, histSize, ranges);
    const int hist_w = 512;
    const int hist_h = 512;
    const int width = 2;
    drawHist(hist_w, hist_h, width, hist, NORM_INF, "hist");

    // 直方图反向投影
    Mat backproj;
    calcBackProject(&img_HSV, 1, channels, hist, backproj, ranges);
    imshow("backproj", backproj);

    waitKey(0);

    return 0;
}
