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
	//string name = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
	VideoCapture cap(0);
	Mat frame;
	cap >> frame;
	int x = frame.cols / 8;
	int y = frame.rows / 8;
	char c = 'w';
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
				cap >> frame;
				putText(frame, to_string(wait_), Point(x * 4, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
				wait_--;
				imshow("Sasha", frame);
				int kw = 0;
				waitKey(100);
			}
			cap >> frame;
			line(frame, Point(x * 4, y), Point(x * 4, y * 8), Scalar(127, 255, 0));
			putText(frame, "play", Point(x * 4, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);		
			imshow("Sasha", frame);
			waitKey(100);
			minMaxLoc(ds.Classify(frame), 0, &confidence, 0, &classIdPoint);
			putText(frame, labels[classIdPoint.x], Point(x * 2, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
			c = 'p';
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
/*int main() 
{
	return 0;
}*/	