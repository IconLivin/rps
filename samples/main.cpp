#include <iostream>
#include "classificator.h"
#include "detector.h"

#define wait 'w';
#define play 'p';
#define quit 'q';
#define two_play '2';
#define one_play '1';
string labels[3] = { "Rock","Scissors","Paper" };
string win[3] = { "Scissiors","Paper","Rock" };

bool flag = 1;
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
	char s = 'w';
	namedWindow("rps", WINDOW_NORMAL);
	setMouseCallback("rps", mouse_callback);

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
				//start to game
				if (pt.x > 240 && pt.x < 370 && pt.y>190 && pt.y < 240)
				{
					while (flag) {
						HandClassificator ds;
						double confidence;
						Point classIdPoint;
						cap >> frame;
						Rect r(Point(x, y * 4), Point(x * 7, y * 8));
						Rect rect(Point(0, 0), Point(8 * x, 8 * y));
						rectangle(frame, rect, Scalar(0, 0, 255), 2);
						//switch (s) {
						//case 'p': {
							int wait_ = 3;
							while (wait_ > 0) {
								int f = 0;
								while (f != 30)
								{
									waitKey(1);
									cap >> frame;
									putText(frame, to_string(wait_), Point(x * 3.6, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
									rectangle(frame, rect, Scalar(0, 0, 255), 2);
									imshow("rps", frame);
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
								imshow("rps", frame);
								f++;
							}
							while (flag) {
								vector<int> res(3);
								res[0] = 0; res[1] = 0; res[2] = 0;
								int ca = 0;
								while (ca != 15) {
									cap >> frame;
									imshow("rps", frame);
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
									imshow("rps", frame);
									f1++;
								}
								if (s = (char)waitKey(2) == 'q') {
									flag = 0;
									break;
								}
							}
						}
				}
				
				imshow("rps", frame);
				char ch = (char)waitKey(2);
				if (ch == 'q')
				break;
				

	
				if (pt.x > 240 && pt.x < 365 && pt.y>250 && pt.y < 305)
					flag = 0;
				std::cout << "Clicked coordinates: " << pt << std::endl;
				newCoords = false;
			}
		}

		char co = (char)waitKey(2);
		if (co == 'q')
			break;
	}
	destroyAllWindows();
	cout << " " << endl;
	return 0;
}


