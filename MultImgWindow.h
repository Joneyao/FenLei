#pragma once
#ifndef MIW_H
#define MIW_H

#include <string>
#include <iostream>
using namespace std;

// OpenCV includes
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

class MultImgWindow
{
public:
	//构造函数，创建一个 行*列的窗口
	MultImgWindow(string window_title, int cols, int rows, int flag);
	//添加 img 到指定窗口
	int addImg(string title, Mat img, bool render = false);
	//remove img
	void removeImg(int pos);
	void render();
private:
	int cols;
	int rows;
	int canvas_w;
	int canvas_h;
	string window_title;
	vector<string> titles;
	vector<Mat> imgs;
	Mat canvas;
};

#endif // !MIW_H
