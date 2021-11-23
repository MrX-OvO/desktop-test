#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    std::vector<Mat> Gauss, Lap; // 高斯“金字塔”和拉普拉斯“金字塔”
    int level = 3;               // 高斯“金字塔”下采样次数
    Gauss.push_back(img);
    // 构建 高斯“金字塔”
    for (size_t i = 0; i < level; ++i)
    {
        Mat gauss;
        pyrDown(Gauss[i], gauss);
        Gauss.push_back(gauss);
    }
    // 构建拉普拉斯“金字塔”
    for (size_t i = Gauss.size() - 1; i > 0; --i)
    {
        Mat lap, upGauss;
        if (i == Gauss.size() - 1) // 如果是高斯“金字塔”的最上面一层图像
        {
            Mat down;
            pyrDown(Gauss[i], down);
            pyrUp(down, upGauss);
            lap = Gauss[i] - upGauss;
            Lap.push_back(lap);
        }
        pyrUp(Gauss[i], upGauss);
        lap = Gauss[i - 1] - upGauss;
        Lap.push_back(lap);
    }
    for (size_t i = 0; i < Gauss.size(); ++i)
    {
        std::string idx = std::to_string(i);
        imshow("G" + idx, Gauss[i]);
        imshow("L" + idx, Lap[i]);
    }
    waitKey(0);

    return 0;
}
