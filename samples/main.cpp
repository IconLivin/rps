#include <iostream>
#include "classificator.h"
//#include "detector.h"

string label[3] = { "paper","rock", "scissors" };
int main() 
{
	//Initialized arguments
	VideoCapture cap(0);
	Mat frame;
	cap >> frame;
	int x = frame.cols / 8;
	int y = frame.rows / 8;
	//
	Rect rect(Point(x,y*8),Point(7*x,4*y));
	//work with video
	while (true) {
		HandClassificator ds;
		double confidence;
		Point classIdPoint;
		cap >> frame;
		Mat crop;
		crop = frame(rect);
		
		minMaxLoc(ds.Classify(crop), 0, &confidence, 0, &classIdPoint);
		cout << "ClassId:" << classIdPoint.x << endl << "Confidence:" << confidence << endl;
		string str = " class  " + /*to_string(classIdPoint.x);*/label[classIdPoint.x];
		rectangle(frame, rect, Scalar(0, 0, 255),2);
		putText(frame,str,Point(10,100), cv::FONT_HERSHEY_COMPLEX,	1.0, cv::Scalar(0, 0, 0), 2);
		imshow("Sasha", frame);
		char c = (char)waitKey(2);
		if (c == 'q')
			break;
		}
	
	cout << " " << endl;
	return 0;
}