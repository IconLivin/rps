#include <iostream>
#include "classificator.h"
#include "detector.h"
#define wait 'w';
#define play 'p';
#define quit 'q';
#define two_play '2';
string labels[3] = { "Rock","Scissors","Paper" };


int main() 
{
	//Initialized arguments
	string name = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
	VideoCapture cap(0);
	Mat frame;
	cap >> frame;
	int x = frame.cols / 8;
	int y = frame.rows / 8;
	char c = wait;
	//
	//Rect rect(Point(x,y*8),Point(7*x,4*y));
	//work with video
	while (true) {
		HandClassificator ds;
		double confidence;
		Point classIdPoint;
		cap >> frame;
		Mat crop;
		line(frame, Point(x * 4, 0), Point(x * 4, y * 8), Scalar(0, 0, 255),2);
		switch (c) {
		case 'p': {
			int wait_ = 3;
			while (wait_ > 0) {
				putText(frame, to_string(wait_), Point(x * 4, 0), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
				wait_--;
				imshow("Sasha", frame);
				int kw = 0;
				while (kw != 30) {
					cap >> frame;
					kw++;
				}
			}
			line(frame, Point(x * 4, 0), Point(x * 4, y * 8), Scalar(127, 255, 0));
			putText(frame, "play", Point(x * 4, 0), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
			imshow("Sasha", frame);
			_sleep(100);
			minMaxLoc(frame, 0, &confidence, 0, &classIdPoint);
			putText(frame, labels[classIdPoint.x], Point(x * 2, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
			c = wait;
			break;
		}
		}
		imshow("Sasha", frame);
		c = (char)waitKey(2);
		if (c == 'q')break;
	}
	
	cout << " " << endl;
	return 0;
}