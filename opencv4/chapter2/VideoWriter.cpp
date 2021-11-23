#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img;
    VideoCapture video(0); // 使用某个摄像头
    if (!video.isOpened()) //判断摄像头是否调用成功
    {
        std::cout << "打开摄像头失败，请确认是否安装摄像头！\n";
        return -1;
    }
    video >> img;    //获取图像
    if (img.empty()) // 判断读取图像是否成功
    {
        std::cout << "没有获取到图像\n";
        return -1;
    }

    bool isColor = (img.type() == CV_8UC3); // 判断相机（视频）类型是否为彩色
    VideoWriter writer;
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');    // 选择编码格式
    double fps = 25.0;                                      // 设置视频帧率
    std::string filename = "live.avi";                      // 保存的视频文件名称
    writer.open(filename, codec, fps, img.size(), isColor); // 创建保存视频文件的视频流
    if (!writer.isOpened())                                 //判断摄像头是否调用成功
    {
        std::cout << "打开视频文件失败，请确认是否为合法输入！\n";
        return -1;
    }

    while (1) // 保存视频
    {
        if (!video.read(img))
        {
            std::cout << "摄像头断开连接或视频读取完成\n";
            return -1;
        }
        writer.write(img);   // 把图像写入视频流
        imshow("Live", img); // 显示图像
        char c = waitKey(50);
        if (c == 27) // 按下"ESC"键退出视频保存
            break;
    }

    video.release();
    writer.release();

    return 0;
}
