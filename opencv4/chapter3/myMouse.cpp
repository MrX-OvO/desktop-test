#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

Mat img, imgPoint;
Point prePoint;
void mouse(int, int, int, int, void *);

int main(int argc, char const *argv[])
{
    img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }
    img.copyTo(imgPoint);
    imshow("img window 1", img);
    imshow("img window 2", imgPoint);
    setMouseCallback("img window 1", mouse); // 在图像窗口1 鼠标响应
    waitKey(0);

    return 0;
}

void mouse(int event, int x, int y, int flags, void *)
{
    if (event == EVENT_RBUTTONDOWN) // 单击右键
    {
        std::cout << "点击鼠标左键才可以绘制轨迹\n";
    }
    if (event == EVENT_LBUTTONDOWN) // 单机左键，输出坐标
    {
        prePoint = Point(x, y);
        std::cout << "轨迹起点坐标：" << prePoint << std::endl;
    }
    if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) // 按住鼠标左键移动
    {
        // 通过改变图像像素显示鼠标移动轨迹
        imgPoint.at<Vec3b>(y, x) = Vec3b(0, 0, 255);
        imgPoint.at<Vec3b>(y, x - 1) = Vec3b(0, 0, 255);
        imgPoint.at<Vec3b>(y, x + 1) = Vec3b(0, 0, 255);
        imgPoint.at<Vec3b>(y - 1, x) = Vec3b(0, 0, 255);
        imgPoint.at<Vec3b>(y + 1, x) = Vec3b(0, 0, 255);
        imshow("img window 2", imgPoint);

        // 通过绘制直线显示鼠标移动轨迹
        Point pt(x, y);
        line(img, prePoint, pt, Scalar(255, 0, 0), 2);
        prePoint = pt;
        imshow("img window 1", img);
    }
}
