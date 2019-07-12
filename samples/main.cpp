#include <iostream>
#include "classificator.h"
#include "detector.h"
#include <vector>
#define wait 'w';
#define play 'p';
#define quit 'q';
#define two_play '2';
#define one_play '1';
string labels[3] = { "Paper","Rock","Scissiors" };
string win[3] = { "Scissiors","Paper","Rock" };


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
	Rect rect(Point(0,0),Point(8*x,8*y));
	//work with video
	while (true) {
		HandClassificator ds;
		double confidence;
		Point classIdPoint;
		cap >> frame;
		Rect r(Point(x, y * 4), Point(x * 7, y * 8));
		Mat crop;
		rectangle(frame, rect, Scalar(0, 0, 255), 2);
		switch (c) {
		case 'p': {
		int wait_ = 3;
		while (wait_ > 0) {
				int f = 0; 
				while (f!=30)
				{
					waitKey(1);
					cap >> frame;
					putText(frame, to_string(wait_), Point(x * 3.6, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
					rectangle(frame, rect, Scalar(0, 0, 255), 2);
					imshow("Sasha", frame);
					f++;
				}	
				wait_--;
			}
			int f = 0;
			while (f != 30)
			{
				waitKey(1);
				cap >> frame;
				putText(frame, "Play", Point(x * 3.2, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
				rectangle(frame, rect, Scalar(127, 255, 0), 2);
				imshow("Sasha", frame);
				f++;
			}
			while (true) {
				vector<int> res(3);
				res[0] = 0; res[1] = 0; res[2] = 0;
				int ca = 0;
				while (ca != 15) {
					cap >> frame;
					imshow("Sasha", frame);
					minMaxLoc(ds.Classify(frame), 0, &confidence, 0, &classIdPoint);
					if (confidence > 0.7)res[classIdPoint.x]++;
					waitKey(2);
					ca++;
				}
				int class1 = 0;
				for (int i = 0; i < res.size(); i++) {
					if (res[i] > class1)class1 = i;
				}
				int f1 = 0;
				while (f1 != 30)
				{
					waitKey(1);
					cap >> frame;
					putText(frame, labels[class1], Point(x * 1, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
					putText(frame, win[class1], Point(x * 5, y * 5), FONT_ITALIC, 2, Scalar(0, 255, 0), 2);
					rectangle(frame, rect, Scalar(127, 255, 0), 2);
					imshow("Sasha", frame);
					f1++;
				}
				c = (char)waitKey(10);
				if (c == 'w')break;
			}
			c = 'w';
			break;
		}
		}
		cv::imshow("Sasha", frame);
		c = (char)waitKey(2);
		if (c == 'q')break;
	}
	
	cout << " " << endl;
	return 0;
}
//int main() 
//{
//	VideoCapture cap(0);
//	Mat frame;
//	cap >> frame;
//	while (true) {
//		HandClassificator ds; 
//		double confidence;
//		Point classIdPoint;
//		cap >> frame;
//		cv::imshow("Okno", frame);
//		minMaxLoc(ds.Classify(frame), 0, &confidence, 0, &classIdPoint);
//		cout << "ClassId:" << classIdPoint.x << endl << "Confidence:" << confidence << endl;
//		waitKey(2);
//	}
//	return 0;
//}	