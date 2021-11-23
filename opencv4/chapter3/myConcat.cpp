#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

int main(int argc, char const *argv[])
{
    // 矩阵数组的横竖连接
    Mat matArray[] = {Mat(1, 2, CV_32FC1, Scalar(1)), Mat(1, 2, CV_32FC1, Scalar(2))};
    Mat vout, hout;
    vconcat(matArray, 2, vout);
    std::cout << "矩阵数组的竖向连接：\n"
              << vout << std::endl;
    hconcat(matArray, 2, hout);
    std::cout << "矩阵数组的横向连接：\n"
              << hout << std::endl;

    // 矩阵的横竖连接
    Mat A = (Mat_<float>(2, 2) << 1, 7, 2, 8);
    Mat B = (Mat_<float>(2, 2) << 4, 10, 11, 5);
    Mat vC, hC;
    vconcat(A, B, vC);
    std::cout << "多个矩阵的竖向连接：\n"
              << vC << std::endl;
    hconcat(A, B, hC);
    std::cout << "多个矩阵的横向连接：\n"
              << hC << std::endl;

    // 分割图像成4个子图像并显示，00表示左上角，01表示右上角，10表示左下角，11表示右下角
    Mat img = imread("../lena.png");
    if (img.empty())
    {
        std::cout << "请确认图像文件名称是否正确！\n";
        return -1;
    }
    int rows = img.rows;
    int cols = img.cols;
    Rect rect00(0, 0, rows / 2, cols / 2);
    Rect rect01(cols / 2, 0, rows / 2, cols / 2);
    Rect rect10(0, rows / 2, rows / 2, cols / 2);
    Rect rect11(rows / 2, cols / 2, rows / 2, cols / 2);
    Mat img00 = img(rect00);
    Mat img01 = img(rect01);
    Mat img10 = img(rect10);
    Mat img11 = img(rect11);
    std::vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    imwrite("../lena00.png", img00, compression_params);
    imwrite("../lena01.png", img01, compression_params);
    imwrite("../lena10.png", img10, compression_params);
    imwrite("../lena11.png", img11, compression_params);
    imshow("img00", img00);
    imshow("img01", img01);
    imshow("img10", img10);
    imshow("img11", img11);
    // 图像连接
    Mat img0, img1, img2;
    // 图像横向连接
    hconcat(img00, img01, img0);
    hconcat(img10, img11, img1);
    imshow("img0", img0);
    imshow("img1", img1);
    // 再在横向连接的结果上进行竖向连接
    vconcat(img0, img1, img2);
    imshow("img2", img2);
    waitKey(0);

    return 0;
}
