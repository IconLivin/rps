#include <iostream>
#include "classificator.h"
#include "detector.h"

#define wait 'w';
#define play 'p';
#define quit 'q';
#define two_play '2';
#define one_play '1';
string labels[3] = { "Rock","Scissors","Paper" };

int x, y;
Mat frame;
Point pt(-1, -1);
bool newCoords = false;


void Menu(Mat frame)
{
	putText(frame, "Menu", Point(x * 3, y * 3), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
	putText(frame, "Play", Point(x * 3, y * 4), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
	putText(frame, "Exit", Point(x * 3, y * 5), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
}

void DrawGrid(Mat mat, int x, int y)
{
	for (int i = 1; i < 8; i++)
	{
		line(mat, Point(0, y*i), Point(x * 8, y*i), Scalar(0, 250, 0), 2);
		line(mat, Point(x*i, 0), Point(x * i, y * 8), Scalar(0, 250, 0), 2);
	}

}

void mouse_callback(int  event, int  xt, int  yt, int  flag, void *param)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		
		pt.x = xt;
		pt.y = yt;
		newCoords = true;
	}
}

int main()
{
	//Initialized arguments
	//string name = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
	VideoCapture cap(0);
	cap >> frame;
	 x = frame.cols / 8;
	 y = frame.rows / 8;
	cout << x << "  " << y << endl;
	char c = 'w';
	namedWindow("rps", WINDOW_NORMAL);
	setMouseCallback("rps", mouse_callback);
	bool flag = 1;
	//work with video
	while (flag) {
		
		/*frame = imread("../data/back.jpg");*/
		frame = imread("../../rps/data/back.jpg");
		Menu(frame);
		imshow("rps", frame);
		if (pt.x != -1 && pt.y != -1)
		{
			circle(frame, pt, 3, Scalar(0, 0, 255));

			if (newCoords)
			{
				if (pt.x > 240 && pt.x < 370 && pt.y>190 && pt.y < 240)
				{
					while (1) {
						cap >> frame;
						imshow("rps", frame);
						char c = (char)waitKey(2);
						if (c == 'q')
							break;
					}

				}
				if (pt.x > 240 && pt.x < 365 && pt.y>250 && pt.y < 305)
					flag = 0;
				std::cout << "Clicked coordinates: " << pt << std::endl;
				newCoords = false;
			}
		}

		char c = (char)waitKey(2);
		if (c == 'q')
			break;
	}
	destroyAllWindows();
	cout << " " << endl;
	return 0;
}



//#include <iostream>
//#include "classificator.h"
//#include "detector.h"
//#define wait 'w';
//#define play 'p';
//#define quit 'q';
//#define two_play '2';
//string labels[3] = { "Rock","Scissors","Paper" };
//
//int x, y;
//Mat frame;
//Point pt(-1, -1);
//bool newCoords = false;
//
//
//void mouse_callback(int  event, int  x, int  y, int  flag, void *param)
//{
//	if (event == EVENT_LBUTTONDOWN)
//	{
//		// Store point coordinates
//		pt.x = x;
//		pt.y = y;
//		newCoords = true;
//	}
//}
//
//void Menu(Mat frame) 
//{
//	putText(frame, "Menu", Point(x * 3, y * 3),  FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
//	putText(frame, "Play", Point(x * 3, y * 4), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
//	putText(frame, "Exit", Point(x * 3, y * 5), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
//}
//
//void DrawGrid(Mat mat,int x, int y) 
//{
//	for (int i = 1; i < 8; i++) 
//	{
//		line(mat, Point(0, y*i), Point(x * 8, y*i), Scalar(0, 250, 0), 2);
//		line(mat, Point(x*i,0), Point(x * i, y*8), Scalar(0, 250, 0), 2);
//	}
//
//}
//
//
//int main()
//{
//	//Initialized arguments
//
//	VideoCapture cap(0);
//	Mat frame;
//	Mat image = imread("C:\\Users\\temp2019\\GitProject\\CV-SUMMER-CAMP\\data\\lobachevsky.jpg", 1);
//	namedWindow("rps", WINDOW_NORMAL);
//	cap >> frame;
//	x = frame.cols / 8;
//	y = frame.rows / 8;
//	char c = 'w';
//	// Set callback
//	setMouseCallback("img", mouse_callback);
//	while (1) {
//		cap >> frame;
//		DrawGrid(frame, x, y);
//		Menu(frame);
//		if (newCoords)
//		{
//			newCoords = false;
//		}
//		imshow("rps", frame);
//		char c = waitKey(100);
//		if (c == 'q')
//			break;
//	}
//}
//
//
//
//
//
//
//
//
//int main(int, char**)
//{
//	VideoCapture cap(0); // open the default camera
//	if (!cap.isOpened())  // check if we succeeded
//		return -1;
//
//	Mat edges;
//	namedWindow("img", 1);
//
//	// Set callback
//	setMouseCallback("img", mouse_callback);
//
//	for (;;)
//	{
//		cap >> frame; // get a new frame from camera
//
//					  // Show last point clicked, if valid
//		if (pt.x != -1 && pt.y != -1)
//		{
//			circle(frame, pt, 3, Scalar(0, 0, 255));
//
//			if (newCoords)
//			{
//				std::cout << "Clicked coordinates: " << pt << std::endl;
//				newCoords = false;
//			}
//		}
//
//		imshow("img", frame);
//
//		// Exit if 'q' is pressed
//		if ((waitKey(1) & 0xFF) == 'q') break;
//	}
//	// the camera will be deinitialized automatically in VideoCapture destructor
//	return 0;
//}
//

	
	//Rect rect(Point(x,y*8),Point(7*x,4*y));
	//work with video
	//while (true) {
	//	HandClassificator ds;
	//	double confidence;
	//	Point classIdPoint;
	//	cap >> frame;
	//	Mat crop;
	//	line(frame, Point(x * 4, 0), Point(x * 4, y * 8), Scalar(0, 0, 255),2);
	//	switch (c) {
	//	case 'p': {
	//		int wait_ = 3;
	//		while (wait_ > 0) {
	//			cap >> frame;
	//			putText(frame, to_string(wait_), Point(x * 4, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
	//			wait_--;
	//			imshow("Sasha", frame);
	//			int kw = 0;
	//			waitKey(100);
	//		}
	//		cap >> frame;
	//		line(frame, Point(x * 4, y), Point(x * 4, y * 8), Scalar(127, 255, 0));
	//		putText(frame, "play", Point(x * 4, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);		
	//		imshow("Sasha", frame);
	//		waitKey(100);
	//		minMaxLoc(ds.Classify(frame), 0, &confidence, 0, &classIdPoint);
	//		putText(frame, labels[classIdPoint.x], Point(x * 2, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
	//		c = 'p';
	//		break;
	//	}
	//	}
	//	imshow("Sasha", frame);
	//	c = (char)waitKey(2);
	//	if (c == 'q')break;
	//}
	
//	cout << " " << endl;
//	return 0;
//}
/*int main() 
{
	return 0;
}*/	