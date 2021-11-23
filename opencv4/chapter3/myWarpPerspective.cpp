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

    Point2f src_points[4], dst_points[4];
    // 原图像中的4个角点坐标
    /*     src_points[0]=Point2f();
    src_points[1]=Point2f();
    src_points[2]=Point2f();
    src_points[3]=Point2f(); */
    // 期望透视变换后图像4个角点坐标
    /*     dst_points[0] = Point2f(0.0f, 0.0f);
    dst_points[1] = Point2f();
    dst_points[2] = Point2f();
    dst_points[3] = Point2f(); */
    Mat perspection, img_warp;
    perspection = getPerspectiveTransform(src_points, dst_points); // 计算透视变换矩阵
    warpPerspective(img, img_warp, perspection, img.size());       // 进行透视变换
    imshow("img", img);
    imshow("iymg_warp", img_warp);
    waitKey(0);

    return 0;
}
