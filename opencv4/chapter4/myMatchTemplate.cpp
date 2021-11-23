#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    Mat img2 = imread("../peppers.bmp");
    Mat temp = imread("../lena00.png");
    Mat temp2 = imread("../lena01.png");
    if (img.empty() || img2.empty() || temp.empty() || temp2.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat result, result2;
    matchTemplate(img, temp, result, TM_CCOEFF_NORMED);
    matchTemplate(img2, temp2, result2, TM_CCORR_NORMED);
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    std::cout << "maxLoc = " << maxLoc << std::endl;
    rectangle(img, cv::Rect(maxLoc.x, maxLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255));
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    std::cout << "maxLoc = " << maxLoc << std::endl;
    rectangle(img2, cv::Rect(maxLoc.x, maxLoc.y, temp2.cols, temp2.rows), Scalar(0, 255, 255));

    imshow("img", img);
    imshow("img2", img2);
    imshow("tmp", temp);
    imshow("tmp2", temp2);
    imshow("result", result);
    imshow("result2", result2);

    waitKey(0);

    return 0;
}