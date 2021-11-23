#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

void AlphaMat(Mat &mat)
{
    CV_Assert(mat.channels() == 4);
    for (size_t i = 0; i < mat.rows; ++i)
    {
        for (size_t j = 0; j < mat.cols; ++j)
        {
            // 获取四通道，bgra
            Vec4b &bgra = mat.at<Vec4b>(i, j);
            bgra[0] = UCHAR_MAX;
            bgra[1] = saturate_cast<uchar>(static_cast<float>(mat.cols - j)) / (static_cast<float>(mat.cols) * UCHAR_MAX);
            bgra[2] = saturate_cast<uchar>(static_cast<float>(mat.cols - j)) / (static_cast<float>(mat.cols) * UCHAR_MAX);
            bgra[3] = saturate_cast<uchar>(0.5 * (bgra[0] + bgra[1] + bgra[2]));
        }
    }
}

int main(int argc, char const *argv[])
{
    Mat mat(400, 300, CV_8UC4);
    /*     auto brga_0_0 = mat.at<Vec4b>(0, 0);
    std::cout << "blue=" << brga_0_0[0] << std::endl;
    std::cout << "green=" << brga_0_0[1] << std::endl;
    std::cout << "red=" << brga_0_0[2] << std::endl;
    std::cout << "alpha=" << brga_0_0[3] << std::endl; */
    std::cout << "显示原图片：\n";
    imshow("src img", mat);
    waitKey(0);

    AlphaMat(mat);
    std::vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION); // PNG格式图像压缩标志
    compression_params.push_back(9);                       // 设置最高压缩质量
    bool result = imwrite("alpah.png", mat, compression_params);
    if (!result)
    {
        std::cout << "保存成PNG格式图像失败！\n";
        return -1;
    }

    return 0;
}
