#include <opencv2/opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main() 
{
	VideoCapture cap(0);
	Mat frame;
	cap >> frame;
	int x = frame.cols / 8;
	int y = frame.rows / 8;
	Rect rec(Point(x, y * 4), Point(x * 7, y * 8));
	Mat save;
	int count = 0;
	char c='w';
	string name = "Paper";
	while (true) {
		rectangle(frame, rec, Scalar(0, 0, 255), 2);
		imshow("Window", frame);	
		cap >> frame;
		putText(frame, name, Point(x, y), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 255, 255));
		if (c == '`'||c=='+') {
			int wt = 0;
			while (wt != 30) { 
				putText(frame, to_string(wt / 10 ), Point(x * 4, y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255));
				rectangle(frame, rec, Scalar(127, 255, 0), 2);
				imshow("Window", frame); 	
				cap >> frame; 
				waitKey(2);
				wt++; 
			}
			save = frame(rec);
			rectangle(frame, rec, Scalar(127, 255, 0), 2);
			imshow("Window", frame);
			cap >> frame;
			string st = name + to_string(count) + ".jpg";
			imwrite(st, save);
			count++;
			waitKey(2);
			c = 'w';
		}
		if (c == 'p') {
			name = "Paper_";
			c = 'w';
		}
		if (c == 'r') {
			name = "Rock_";
			c = 'w';
		}
		if (c == 's') {
			name = "Scissiors_";
			c = 'w';
		}
		c = waitKey(2);
		if (c == 'q')break;
	}
}