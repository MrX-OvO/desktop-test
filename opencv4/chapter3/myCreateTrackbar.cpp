#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int value;
void callBack(int, void *);
Mat img1, img2;

int main(int argc, char const *argv[])
{
    img1 = imread("../lena.png");
    if (img1.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }
    namedWindow("slider chage img brightness");
    imshow("slider chage img brightness", img1);
    value = 100;
    createTrackbar("brightness percentage", "slider chage img brightness", &value, 600, callBack);
    waitKey(0);

    return 0;
}

void callBack(int, void *)
{
    float a = value / 100.f;
    img2 = img1 * a;
    imshow("slider chage img brightness", img2);
}
