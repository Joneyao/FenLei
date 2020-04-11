// FenLei.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

// opencv include 
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp"

#include "MultImgWindow.h"

using namespace cv;
using namespace cv::ml;

MultImgWindow* miw;
Mat light_pattern;

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char* keys =
{
   "{help h usage ? | | print this message}"
   "{@image || Image to classify}"
};


/*
    去除光照
*/

Mat removeLight(Mat img, Mat pattern)
{
    Mat aux;
    // Require change our image to 32 float division
    Mat img32, pattern32;

    img.convertTo(img32,CV_32F);
    pattern.convertTo(pattern32,CV_32F);

    aux = 1 - (img32 / pattern32);

    aux = aux * 255;
    
    aux.convertTo(aux, CV_8U);

    return aux;
}


/*
    图像前处理
*/

Mat preprocessImage(Mat input)
{
    Mat result;
    // remove noise
    Mat img_noise, img_box_smooth;

    medianBlur(input, img_noise,3);

    // apply the light pattern
    Mat img_no_light;
    img_noise.copyTo(img_no_light);

    img_no_light = removeLight(img_noise, light_pattern);

    // binrize image for segment

    return result;

}


/*
    读取文件夹中的图片，并提取特征
*/

bool readFolderAndExtractFeatures(string folder, int label, int numForTest, 
    vector<float> &trainData, vector<int> &responsesData,
    vector<float> &testData, vector<float> &testResponsesData)
{
    VideoCapture images;
    if (images.open(folder) == false) {
        cout << "Cant't open the folder ( " << folder << " ) images !\n";
        return false;
    }

    Mat frame;
    int img_index = 0;

    while (images.read(frame))
    {
        // 图像前处理
        Mat pre = preprocessImage(frame);
        // 提取特征
        vector< vector<float>>  features = ;
    }

}

/*
    数据集训练
*/
void trainAndTest(void)
{
    vector<float> trainingData;
    vector<int>   responsesData;
    vector<float> testData;
    vector<float> testResponsesData;

    int num_for_test = 20;

    // 获取 nut 图像

}

/*
    主函数：
*/ 
int main(int argc,const char** argv)
{
    //1. 命令解析
    CommandLineParser parser(argc,argv,keys);
    parser.about("Chapter 6. Classification v1.0.0");
    if (parser.has("help"))
    {
        parser.printMessage();
        cout << "prt help msg...\n";
        return 0;
    }

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    String img_file = parser.get<String>(0);
    String light_pattern_file = "pattern.pgm";

    cout << "img file name:" << img_file << endl;

    // 创建复合窗口: 2行*2列
    miw = new MultImgWindow("Main window", 2, 2, WINDOW_AUTOSIZE);

    // 加载图片进行处理
    Mat img = imread(img_file,0);
    if (img.data == NULL) {
        cout << " Error loading image " << endl;
        return 0;
    }

    Mat img_output = img.clone();
    cvtColor(img_output, img_output, COLOR_GRAY2BGR);

    // 加载光模板
    light_pattern = imread(light_pattern_file,0);
    if (light_pattern.data == NULL) {
        cout << " Error loading image " << endl;
        return 0;
    }

    //imshow("org_pattern", light_pattern);

    medianBlur(light_pattern,light_pattern,3);

    //imshow("out_pattern", light_pattern);


    // 数据训练

    waitKey(0);

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
