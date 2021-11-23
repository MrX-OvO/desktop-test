#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

void createXMLorYAML(const std::string &fileName)
{
    FileStorage fwrite(fileName, FileStorage::WRITE);
    Mat mat = Mat::eye(3, 3, CV_8U);

    fwrite.write("mat", mat);
    float x = 100.f;
    fwrite << "x" << x;
    String str = "Learn OpenCV4";
    fwrite << "str" << str;
    fwrite << "number_array"
           << "[" << 4 << 5 << 6 << "]";
    fwrite << "multi_nodes"
           << "{"
           << "month" << 10 << "day" << 20 << "year" << 2021 << "time"
           << "[" << 19 << ":" << 54 << "]"
           << "}";
    fwrite.release();
}

void printXMLorYAML(const std::string &fileName)
{
    FileStorage fread(fileName, FileStorage::READ);
    if (!fread.isOpened())
    {
        std::cout << "打开文件失败，请确认文件名称是否正确！\n";
        return;
    }

    Mat matRead;
    fread["mat"] >> matRead;
    std::cout << "mat=" << matRead << std::endl;

    float xRead;
    fread["x"] >> xRead;
    std::cout << "x=" << xRead << std::endl;

    std::string strRead;
    fread["str"] >> strRead;
    std::cout << "str=" << strRead << std::endl;

    FileNode fileNode = fread["number_array"];
    std::cout << "number_array=[";
    for (FileNodeIterator iter = fileNode.begin(); iter != fileNode.end();)
    {
        float a;
        (*iter++) >> a;
        std::cout << a << (iter == fileNode.end() ? "]\n" : " ");
    }

    FileNode mulFileNode = fread["multi_nodes"];
    int month = static_cast<int>(mulFileNode["month"]);
    int day = static_cast<int>(mulFileNode["day"]);
    int year = static_cast<int>(mulFileNode["year"]);
    std::cout << "multi_nodes:\n"
              << " month=" << month << " day=" << day << " year=" << year;
    std::cout << " time=[";
    FileNode time = mulFileNode["time"];
    for (int i = 0; i < time.size(); ++i)
    {
        if (time[i].isString())
            std::cout << ": ";
        else
        {
            int a = static_cast<int>(time[i]);
            std::cout << a << ((i == time.size() - 1) ? "]\n" : " ");
        }
    }

    fread.release();
}

int main(int argc, char const *argv[])
{
    std::string xmlFile = "datas.xml";
    std::string yamlFile = "datas.yaml";

    createXMLorYAML(xmlFile);
    createXMLorYAML(yamlFile);

    std::cout << "print xml:\n";
    printXMLorYAML(xmlFile);
    std::cout << "print yaml:\n";
    printXMLorYAML(yamlFile);

    return 0;
}
