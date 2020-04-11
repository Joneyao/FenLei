#include "MultImgWindow.h"

MultImgWindow::MultImgWindow(string window_title, int cols, int rows, int flag)
{
	this->window_title = window_title;
	this->cols = cols;
	this->rows = rows;
	namedWindow(window_title,flag);
	moveWindow(window_title,0,0);
	this->canvas_w = 1200;
	this->canvas_h = 700;
	this->canvas = Mat(this->canvas_h,this->canvas_w,CV_8UC3);
	imshow(this->window_title,this->canvas);
}

int MultImgWindow::addImg(string title, Mat img, bool render)
{
	int index = -1;
	for (int i = 0; i < this->titles.size(); i++) {
		string t = this->titles[i];
		if (t.compare(title) == 0) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		this->titles.push_back(title);
		this->imgs.push_back(img);
	}
	else {
		this->imgs[index] = img;
	}

	if (render)
		this->render();
	return this->imgs.size() - 1;
}

void MultImgWindow::removeImg(int pos)
{
	this->titles.erase(this->titles.begin() + pos);
	this->imgs.erase(this->imgs.begin() + pos);
}

void MultImgWindow::render()
{
	//Clean our canvas
	this->canvas.setTo(Scalar(20,20,20));
	int cell_w = (canvas_w / cols);
	int cell_h = (canvas_h / rows);
	int max_imgs = (this->imgs.size() > cols * rows)? cols * rows :(this->imgs.size());
	int i = 0;

	vector<string>::iterator titles_it = this->titles.begin();

	for (vector<Mat>::iterator it = this->imgs.begin(); it != this->imgs.end(); ++it)
	{
		string title = *titles_it;
		int cell_x = (cell_w) * (i % cols);
		int cell_y = (cell_h) * floor(i / (float)cols);
		Rect mask(cell_x,cell_y,cell_w,cell_h);

		Mat cell(this->canvas,mask);
		Mat resized;

		double cell_aspect = (double)cell_w/(double)cell_h;
		Mat img = *it;
		double img_aspect = (double)img.cols / (double) img.rows;
		double f = (cell_aspect < img_aspect) ? cell_aspect : img_aspect;

		resize(img,resized,Size(0,0),f,f);
		if (resized.channels() == 1) {
			cvtColor(resized,resized,COLOR_GRAY2BGR);
		}

		Rect mask2(cell_x + ((cell_w - resized.cols) / 2), cell_y + ((cell_h - resized.rows) / 2), resized.cols, resized.rows);

		Mat sub_cell(this->canvas, mask2);
		resized.copyTo(sub_cell);

		putText(cell,title.c_str(),Point(20,20),FONT_HERSHEY_SIMPLEX,0.5,Scalar(200,0,0),
			1,LINE_AA);

		rectangle(canvas,Rect(cell_x,cell_y,cell_w,cell_h),Scalar(200,0,0),1);

		i++;
		++titles_it;
		if (i == max_imgs)
			break;
	}

	imshow(this->window_title,this->canvas);
}
