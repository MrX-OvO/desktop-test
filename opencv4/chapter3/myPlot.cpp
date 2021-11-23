#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat img = Mat::zeros(Size(512, 512), CV_8UC3);

    // 绘制圆形
    circle(img, Point(50, 50), 25, Scalar(255, 255, 255), -1); // 绘制一个白色实心圆
    circle(img, Point(100, 50), 20, Scalar(0, 0, 255), 4);     // 绘制一个红色空心圆

    // 绘制直线
    line(img, Point(100, 100), Point(200, 300), Scalar(255, 0, 0), 2); // 蓝色

    // 绘制椭圆
    ellipse(img, Point(250, 200), Size(100, 70), 0, 0, 110, Scalar(0, 255, 0), -1);       // 绿色
    ellipse(img, RotatedRect(Point(200, 100), Size(50, 80), 30), Scalar(0, 255, 255), 2); // 黄色

    // 用一些点来近似一个椭圆
    std::vector<Point> points;
    ellipse2Poly(Point(200, 400), Size(100, 60), 10, 0, 360, 2, points);
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (i == points.size() - 1)
        {
            // 椭圆最后一个点与第一个点连线
            line(img, points[0], points[i], Scalar(255, 255, 0)); // 青色
            break;
        }
        line(img, points[i], points[i + 1], Scalar(255, 255, 0)); // 青色
    }

    // 绘制矩形
    rectangle(img, Rect(400, 450, 100, 20), Scalar(255, 0, 255), -1);     // 洋红
    rectangle(img, Point(300, 400), Point(500, 20), Scalar(255, 0, 255)); // 洋红

    // 绘制多边形
    std::vector<std::vector<Point>> pp;
    std::vector<Point> tmp;
    tmp.push_back(Point(22, 150));
    tmp.push_back(Point(72, 160));
    tmp.push_back(Point(150, 260));
    tmp.push_back(Point(100, 300));
    tmp.push_back(Point(10, 200));
    pp.push_back(tmp);
    tmp.clear();
    tmp.push_back(Point(380, 100));
    tmp.push_back(Point(447, 140));
    tmp.push_back(Point(480, 190));
    tmp.push_back(Point(400, 230));
    tmp.push_back(Point(350, 150));
    pp.push_back(tmp);

    std::vector<Point> p;
    p.push_back(Point(200, 170));
    p.push_back(Point(190, 200));
    p.push_back(Point(350, 160));
    const Point *pts[3] = {&pp[0][0], &pp[1][0], &p[0]};
    int npts[] = {5, 5, 3};
    fillPoly(img, pts, npts, 3, Scalar(80, 127, 255), LINE_AA); // 珊瑚色

    // 生成文字
    putText(img, "Learn OpenCV 4", Point(10, 360), FONT_HERSHEY_COMPLEX, 2, Scalar(0, 165, 255)); // 橙色

    imshow("myPlot", img);
    waitKey(0);

    return 0;
}
