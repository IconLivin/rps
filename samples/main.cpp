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
	while (true) {
		rectangle(frame, rec, Scalar(0, 0, 255), 2);
		imshow("Window", frame);	
		cap >> frame;
		
		if (c == 'p') {
			int f = 0;
			while (f != 30) {
				save = frame(rec);
				rectangle(frame, rec, Scalar(127, 255, 0), 2);
				imshow("Window", frame);
				cap >> frame;
				string st= "Paper_" + to_string(count) + ".jpg";
				imwrite(st, save);
				count++;
				f++;
				waitKey(2);
			}
			c = 'w';
		}
		c = waitKey(2);
		if (c == 'q')break;
	}
}