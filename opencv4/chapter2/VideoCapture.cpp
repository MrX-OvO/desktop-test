#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
  /*   VideoCapture video;
    video.open("./pubg.mp4"); */
  VideoCapture video("./pubg.mp4");
  if (video.isOpened())
  {
    std::cout << "视频中图像的宽度=" << video.get(CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "视频中图像的高度=" << video.get(CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "视频的帧率=" << video.get(CAP_PROP_FPS) << std::endl;
    std::cout << "视频的总帧数=" << video.get(CAP_PROP_FRAME_COUNT) << std::endl;
  }
  else
  {
    std::cout << "请确认视频文件名称是否正确！\n";
    return -1;
  }
  while (1)
  {
    Mat srcFrame, dstFrame;
    video >> srcFrame;
    resize(srcFrame, dstFrame, Size(1600, 800));
    if (dstFrame.empty())
      break;
    imshow("pubg video", dstFrame);
    waitKey(1000 / video.get(CAP_PROP_FPS));
  }
  waitKey();

  return 0;
}
