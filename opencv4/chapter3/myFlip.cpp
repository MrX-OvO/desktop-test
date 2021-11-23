#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }

    Mat img_x, img_y, img_xy;
    flip(img, img_x, 0);   // 以x轴为对称轴
    flip(img, img_y, 1);   // 以y轴为对称轴
    flip(img, img_xy, -1); // 先以x轴为对称轴，再以y轴为对称轴
    imshow("img", img);
    imshow("img_x", img_x);
    imshow("img_y", img_y);
    imshow("img_xy", img_xy);
    waitKey(0);

    return 0;
}
