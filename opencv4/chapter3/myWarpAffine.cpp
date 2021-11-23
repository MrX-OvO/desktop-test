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

    Mat rotation0, rotation1, img_warp0, img_warp1;
    double angle = 30;                                 // 设置图像旋转角度
    Size dst_size(img.rows, img.cols);                 // 设置输出图像的尺寸
    Point2f center(img.rows / 2.0f, img.cols / 2.0f);  // 设置图像的旋转中心
    rotation0 = getRotationMatrix2D(center, angle, 1); // 计算仿射变换矩阵
    warpAffine(img, img_warp0, rotation0, dst_size);   // 进行仿射变换
    imshow("img_warp0", img_warp0);

    // 根据定义的3个点进行仿射变换
    Point2f src_points[3], dst_points[3];
    src_points[0] = Point2f(0, 0);
    src_points[1] = Point2f(0, static_cast<float>(img.cols - 1));
    src_points[2] = Point2f(static_cast<float>(img.rows - 1), static_cast<float>(img.cols - 1));
    // 仿射变换后图像中的3个点
    dst_points[0] = Point2f(static_cast<float>(img.rows * 0.11), static_cast<float>(img.cols * 0.20));
    dst_points[1] = Point2f(static_cast<float>(img.rows * 0.15), static_cast<float>(img.cols * 0.70));
    dst_points[2] = Point2f(static_cast<float>(img.rows * 0.81), static_cast<float>(img.cols * 0.85));
    rotation1 = getAffineTransform(src_points, dst_points); // 根据对应点求取仿射变换矩阵
    warpAffine(img, img_warp1, rotation1, dst_size);        // 进行仿射变换
    imshow("img_warp1", img_warp1);
    waitKey(0);

    return 0;
}
