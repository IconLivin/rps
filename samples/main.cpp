#include <iostream>
#include "classificator.h"
//#include "detector.h"
#include <vector>
string labels[3] = { "Paper","Rock","Scissiors" };
string win[3] = { "Scissiors","Paper","Rock" };

Point pt(-1, -1);
bool newCoords = false;
int x, y;
Mat frame;


void DrawGrid14(Mat mat){

	for (int i = 1; i < 14; i++)
	{
		line(mat, Point(0, mat.rows / 14 *i), Point(mat.cols, mat.rows / 14 *i), Scalar(0, 250, 0), 2);
		line(mat, Point(mat.cols / 14 *i, 0), Point(mat.cols / 14 * i, mat.rows ), Scalar(0, 250, 0), 2);
	}

}


void DrawGrid8(Mat mat)
{
	for (int i = 1; i < 8; i++)
	{
		line(mat, Point(0, mat.rows/8*i), Point(mat.cols, mat.rows/8*i), Scalar(0, 250, 0), 2);
		line(mat, Point(mat.cols/8*i, 0), Point(mat.cols/8 * i, mat.rows ), Scalar(0, 250, 0), 2);
	}

}
//Check mouse click
void mouse_callback(int  event, int  xt, int  yt, int  flag, void *param)
{
	if (event == EVENT_LBUTTONDOWN)
	{

		pt.x = xt;
		pt.y = yt;
		newCoords = true;
	}
}
//Draw start menu
void Menu(Mat image)
{
	//DrawGrid14(image);
	putText(image, "Menu", Point(image.cols/8 * 3, image.rows / 8 * 2.5), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
	putText(image, "Play", Point(image.cols/8 * 1, image.rows / 8 * 4.5), FONT_ITALIC, 2, Scalar(255, 255, 255), 5);
	putText(image, "Exit", Point(image.cols/8* 5.5, image.rows / 8 * 4.5), FONT_ITALIC, 2, Scalar(255, 255, 255), 5);
}

//Draw fairgame
int Level(Mat image) 
{
	int level;
	DrawGrid8(image);
	bool stop=false;
	while (!stop)
	{
	/*	pt.x = -1;
		pt.y = -1;*/
		newCoords = false;
		putText(image, "Easy", Point(image.cols / 8 * 3, image.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
		putText(image, "Medium", Point(image.cols / 8 * 3, image.rows / 8 * 4), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
		putText(image, "Hard", Point(image.cols / 8 * 3, image.rows / 8 * 6), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
		putText(image, "Exit", Point(frame.cols / 8 * 7, frame.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 3);
		imshow("rps", image);
		char c = (char)waitKey(2);
		if (newCoords || c == 'q' || c == '1' || c == '2' || c == '3') {
			if (pt.x > image.cols / 8 * 3 && pt.x<image.cols / 8 * 5 && pt.y> image.rows / 8 * 1 && pt.y < image.rows / 8 * 2 ||c=='1')
			{
				newCoords = false;
				cout << "easy" << endl;
				level = 1;
				return level;
			}
			else if (pt.x > image.cols / 8 * 3 && pt.x<image.cols / 8 * 6 && pt.y> image.rows / 8 * 3 && pt.y < image.rows / 8 * 4 || c == '2')
			{
				newCoords = false;
				cout << "Medium" << endl;
				level = 2;
				return level;
			}
			else if (pt.x > image.cols / 8 * 3 && pt.x<image.cols / 8 * 5 && pt.y> image.rows / 8 * 5 && pt.y < image.rows / 8 * 6 || c == '3')
			{
				newCoords = false;
				cout << "Hard" << endl;
				level = 3;
				return level;
			}
			else if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
			{
				newCoords = false;
				level = 0;
				cout << "back" << endl;
				return level;
			}
		}
	}
}


void Func() 
{
	Mat mat = imread("../../rps/data/rock.png");
	imshow("rps", mat);
	//waitKey();

}

int main()
{
	//Initialize
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Error opening cam" << endl;
		return -1;
	}
	Mat menu = imread("../../rps/data/background.png");
	Mat copy = imread("../../rps/data/background.png");
	Mat rock = imread("../../rps/data/rock.jpg");
	Mat paper = imread("../../rps/data/paper.jpg");
	Mat scrissors = imread("../../rps/data/scissors.jpg"); 
	if (!menu.data && !rock.data && !paper.data && !scrissors.data )
	{
		printf("Error loading image \n");
		return -1;
	}
	namedWindow("rps", WINDOW_AUTOSIZE);
	setMouseCallback("rps", mouse_callback);
	cap >> frame;
	resize(menu, menu, Size(frame.cols, frame.rows));
	resize(copy, copy, Size(frame.cols, frame.rows));
	resize(rock, rock, Size(frame.cols, frame.rows));
	resize(paper, paper, Size(frame.cols, frame.rows));
	resize(scrissors, scrissors, Size(frame.cols, frame.rows));

	cout << frame.cols << endl << frame.rows << endl;
	
	x = menu.cols / 14;
	y = menu.rows / 14;
	bool exit = false;
	while (!exit) {
		Menu(menu);
		//DrawGrid14(menu);
		imshow("rps", menu);
		char c = (char) waitKey(2);
		if (c == 'q')
			exit = true;
		if (newCoords||c=='p')
		{
			if ((pt.x > x * 2 && pt.x<x * 5 && pt.y>y * 6.5 && pt.y < y * 8) || c == 'p')
			{
				int bot_score = 0, player_score = 0;
				newCoords = false;
				int level=Level(copy);
				cout << "play" << endl;
				bool menu = false;
				cout << frame.cols << "  " << frame.rows << endl;
				Rect rect(Point(0, 0), Point(frame.cols , frame.rows ));
				while (!menu) 
				{
					HandClassificator ds;
					double confidence;
					Point classIdPoint;
					int wait_ = 3;
					cap >> frame;
					newCoords = false;
					//Draw 3 2 1 
					while (wait_ > 0) {
						int f = 0;
						while (f != 30)
						{
							cap >> frame;
							putText(frame, to_string(wait_), Point(frame.cols / 8 * 3.6, frame.rows / 8), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
							putText(frame, "Exit", Point(frame.cols / 8 * 7, frame.rows / 8 -20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
							rectangle(frame, rect, Scalar(0, 0, 255), 2);
							imshow("rps", frame);
							c = (char) waitKey(2);
							if (newCoords || c == 'q')
								if ((pt.x >  frame.cols/8 * 7 && pt.y < frame.rows / 8) || c == 'q')
								{
									wait_ = -1;
									menu = true;
									cout << "exit" << endl;
									break;
								}
							f++;
						}
						wait_--;
					}
					if (wait_ == -2)
						break;
					//Draw 0-Play
					int f = 0;
					newCoords = false;
					while (f != 30)
					{
						
						cap >> frame;
						putText(frame, "Play", Point(frame.cols / 8 * 3.2, frame.rows / 8), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
						putText(frame, "Exit", Point(frame.cols / 8 * 7, frame.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
						rectangle(frame, rect, Scalar(127, 255, 0), 2);
						imshow("rps", frame);
						c = (char)waitKey(2);
						if (newCoords || c == 'q')
							if ((pt.x >  frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
							{
								cout << "exit" << endl;
								menu = true;
								break;
							}
						f++;
					}
					newCoords = false;
					int i = 0;
					vector<int> res(3);
					res[0] = 0; res[1] = 0; res[2] = 0;
					int fff = 0;  //first fifteen frame
					while (fff != 3) {
						cap >> frame;
						putText(frame, "Exit", Point(frame.cols / 8 * 7, frame.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
						imshow("rps", frame);
						c = (char)waitKey(1);
						if (newCoords || c == 'q') {
							if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
							{
								cout << "exit" << endl;
								menu = true;
								break;
							}
						}
						minMaxLoc(ds.Classify(frame), 0, &confidence, 0, &classIdPoint);
						if (confidence > 0.7)
							res[classIdPoint.x]++;					
						fff++;
					}
					int class1 = 0; //Who is have max confidence
					for (int i = 0; i < res.size(); i++) {
						if (res[i] > res[class1])
							class1 = i;
					}

					if (level == 3) {
						cout << "win class -" << class1 << "\t" << win[class1] << endl;
						f = 0;
						bot_score++;
						while (f != 30)
						{
							//cap >> frame;
							//	putText(frame, "Exit", Point(frame.cols / 8 * 7, frame.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
							//	putText(frame, labels[class1], Point(frame.cols / 8 * 1, frame.rows / 8), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
							//	putText(frame, win[class1], Point(frame.cols / 8 * 5, frame.rows / 8 * 5), FONT_ITALIC, 2, Scalar(0, 255, 0), 2);
							if (class1 == 0)
							{
								putText(scrissors, "You lose", Point(scrissors.cols / 8 * 2, scrissors.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
								putText(scrissors, "Exit", Point(scrissors.cols / 8 * 7, scrissors.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
								//putText(scrissors, labels[class1], Point(frame.cols / 8 * 1, frame.rows / 8), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
								//putText(scrissors, win[class1], Point(frame.cols / 8 * 5, frame.rows / 8 * 5), FONT_ITALIC, 2, Scalar(0, 255, 0), 2);
								imshow("rps", scrissors);
								//waitKey(200);

							}
							else if (class1 == 1)
							{
								putText(paper, "You lose", Point(paper.cols / 8 * 2, paper.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
								putText(paper, "Exit", Point(paper.cols / 8 * 7, paper.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
								//putText(paper, labels[class1], Point(frame.cols / 8 * 1, frame.rows / 8), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
								//putText(paper, win[class1], Point(frame.cols / 8 * 5, frame.rows / 8 * 5), FONT_ITALIC, 2, Scalar(0, 255, 0), 2);
								imshow("rps", paper);
								//waitKey(200);
							}
							else if (class1==2)
							{
								putText(rock, "You lose", Point(rock.cols / 8 * 2, rock.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
								putText(rock, "Exit", Point(rock.cols / 8 * 7, rock.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
								//putText(rock, labels[class1], Point(frame.cols / 8 * 1, frame.rows / 8), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
								//putText(rock, win[class1], Point(frame.cols / 8 * 5, frame.rows / 8 * 5), FONT_ITALIC, 2, Scalar(0, 255, 0), 2);
								imshow("rps", rock);
								//waitKey(200);
							}
							c = (char)waitKey(150);
							if (newCoords || c == 'q')
								if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
								{
									cout << "exit" << endl;
									menu = true;
									break;
								}
							f++;
						}
						cout << "bot win" << endl;
						cout << "Player " << player_score << " : " << bot_score << " Bot " << endl;
					}
					else if (level == 2) 
					{
						int luck = rand() % 2;
						if (luck == 0) //nobody win and lose
						{
							f = 0;
							cout << "Draw" << endl;
							while (f != 30)
							{
								if (class1 == 2)
								{
									putText(scrissors, "Draw", Point(scrissors.cols / 8 * 2, scrissors.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(scrissors, "Exit", Point(scrissors.cols / 8 * 7, scrissors.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", scrissors);
								}
								else if (class1 == 0)
								{
									putText(paper, "Draw", Point(paper.cols / 8 * 2, paper.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(paper, "Exit", Point(paper.cols / 8 * 7, paper.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", paper);
								}
								else if (class1 == 1)
								{
									putText(rock, "Draw", Point(rock.cols / 8 * 2, rock.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(rock, "Exit", Point(rock.cols / 8 * 7, rock.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", rock);
								}
								c = (char)waitKey(150);
								if (newCoords || c == 'q')
									if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
									{
										cout << "exit" << endl;
										menu = true;
										break;
									}
								f++;
							}
							cout << "DRAW!!!!" << endl;
						
						}
						else if (luck == 1)//lose
						{
							cout << "win class -" << class1 << "\t" << win[class1] << endl;
							f = 0;
							bot_score++;
							while (f != 30)
							{
								if (class1 == 0)
								{
									putText(scrissors, "You lose", Point(scrissors.cols / 8 * 2, scrissors.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(scrissors, "Exit", Point(scrissors.cols / 8 * 7, scrissors.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", scrissors);
								}
								else if (class1 == 1)
								{
									putText(paper, "You lose", Point(paper.cols / 8 * 2, paper.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(paper, "Exit", Point(paper.cols / 8 * 7, paper.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", paper);
								}
								else if (class1 == 2)
								{
									putText(rock, "You lose", Point(rock.cols / 8 * 2, rock.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(rock, "Exit", Point(rock.cols / 8 * 7, rock.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", rock);
								}
								c = (char)waitKey(150);
								if (newCoords || c == 'q')
									if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
									{
										cout << "exit" << endl;
										menu = true;
										break;
									}
								f++;
							}
							cout<<"bot win"<<endl;
							cout << "Player " << player_score << " : " << bot_score << " Bot " << endl;
						}
						else //player win
						{
							f = 0;
							player_score++;
							while (f != 30)
							{
								if (class1 == 0)
								{
									putText(rock, "You win", Point(rock.cols / 8 * 2, rock.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(rock, "Exit", Point(rock.cols / 8 * 7, rock.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", rock);
								}
								else if (class1 == 1)
								{
									putText(scrissors, "You win", Point(scrissors.cols / 8 * 2, scrissors.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(scrissors, "Exit", Point(scrissors.cols / 8 * 7, scrissors.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", scrissors);
								}
								else if (class1 == 2)
								{
									putText(paper, "You win", Point(paper.cols / 8 * 2, paper.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(paper, "Exit", Point(paper.cols / 8 * 7, paper.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", paper);
								}
								c = (char)waitKey(150);
								if (newCoords || c == 'q')
									if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
									{
										cout << "exit" << endl;
										menu = true;
										break;
									}
								f++;
							}
							cout << "Player win" << endl;
							cout << "Player " << player_score << " : " << bot_score << " Bot " << endl;
						}
					} ///end level 2 
					else if (level == 1) 
					{
						int luck = rand() % 4;
						if (luck == 1 || luck == 2 || luck == 3) //Player win
						{
							f = 0;
							player_score++;
							while (f != 30)
							{
								if (class1 == 0)
								{
									putText(rock, "You win", Point(rock.cols / 8 * 2, rock.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(rock, "Exit", Point(rock.cols / 8 * 7, rock.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", rock);
								}
								else if (class1 == 1)
								{
									putText(scrissors, "You win", Point(scrissors.cols / 8 * 2, scrissors.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(scrissors, "Exit", Point(scrissors.cols / 8 * 7, scrissors.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", scrissors);
								}
								else if (class1 == 2)
								{
									putText(paper, "You win", Point(paper.cols / 8 * 2, paper.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(paper, "Exit", Point(paper.cols / 8 * 7, paper.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", paper);
								}
								c = (char)waitKey(150);
								if (newCoords || c == 'q')
									if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
									{
										cout << "exit" << endl;
										menu = true;
										break;
									}
								f++;
							}
							cout << "Player win" << endl;
							cout << "Player " << player_score << " : " << bot_score << " Bot " << endl;
						}
						else 
						{
							f = 0;
							bot_score++;
							while (f != 30)
							{
								if (class1 == 0)
								{
									putText(scrissors, "You lose", Point(scrissors.cols / 8 * 2, scrissors.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(scrissors, "Exit", Point(scrissors.cols / 8 * 7, scrissors.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", scrissors);
								}
								else if (class1 == 1)
								{
									putText(paper, "You lose", Point(paper.cols / 8 * 2, paper.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(paper, "Exit", Point(paper.cols / 8 * 7, paper.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", paper);
								}
								else if (class1 == 2)
								{
									putText(rock, "You lose", Point(rock.cols / 8 * 2, rock.rows / 8 * 2), FONT_ITALIC, 2, Scalar(255, 255, 255), 3);
									putText(rock, "Exit", Point(rock.cols / 8 * 7, rock.rows / 8 - 20), FONT_ITALIC, 1, Scalar(255, 255, 255), 2);
									imshow("rps", rock);
								}
								c = (char)waitKey(150);
								if (newCoords || c == 'q')
									if ((pt.x > frame.cols / 8 * 7 && pt.y < frame.rows / 8) || c == 'q')
									{
										cout << "exit" << endl;
										menu = true;
										break;
									}
								f++;
							}
							cout << "bot win" << endl;
							cout << "Player " << player_score << " : " << bot_score << " Bot " << endl;
						}

					}
					cout << "the end" << endl;
				}
			}
				
			if (pt.x > x * 9.7 && pt.x<x * 12.3 && pt.y>y * 6.5 && pt.y < y * 8)
				exit = true;
			cout << pt.x << "   " << pt.y << endl;
			newCoords = false;
		}
		
	}
	return 0;
}

//int main() 
//{
//	//Initialized arguments
//	//string name = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
//	VideoCapture cap(0);
//	Mat frame;
//	cap >> frame;
//	int x = frame.cols / 8;
//	int y = frame.rows / 8;
//	char c = 'w';
//	//
//	Rect rect(Point(0,0),Point(8*x,8*y));
//	//work with video
//	while (true) {
//		HandClassificator ds;
//		double confidence;
//		Point classIdPoint;
//		cap >> frame;
//		Rect r(Point(x, y * 4), Point(x * 7, y * 8));
//		Mat crop;
//		rectangle(frame, rect, Scalar(0, 0, 255), 2);
//		switch (c) {
//		case 'p': {
//		int wait_ = 3;
//		while (wait_ > 0) {
//				int f = 0; 
//				while (f!=30)
//				{
//					waitKey(1);
//					cap >> frame;
//					putText(frame, to_string(wait_), Point(x * 3.6, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
//					rectangle(frame, rect, Scalar(0, 0, 255), 2);
//					imshow("Sasha", frame);
//					f++;
//				}	
//				wait_--;
//			}
//			int f = 0;
//			while (f != 30)
//			{
//				waitKey(1);
//				cap >> frame;
//				putText(frame, "Play", Point(x * 3.2, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
//				rectangle(frame, rect, Scalar(127, 255, 0), 2);
//				imshow("Sasha", frame);
//				f++;
//			}
//			while (true) {
//				vector<int> res(3);
//				res[0] = 0; res[1] = 0; res[2] = 0;
//				int ca = 0;
//				while (ca != 15) {
//					cap >> frame;
//					imshow("Sasha", frame);
//					minMaxLoc(ds.Classify(frame), 0, &confidence, 0, &classIdPoint);
//					if (confidence > 0.7)res[classIdPoint.x]++;
//					waitKey(2);
//					ca++;
//				}
//				int class1 = 0;
//				for (int i = 0; i < res.size(); i++) {
//					if (res[i] > class1)class1 = i;
//				}
//				int f1 = 0;
//				while (f1 != 30)
//				{
//					waitKey(1);
//					cap >> frame;
//					putText(frame, labels[class1], Point(x * 1, y), FONT_ITALIC, 2, Scalar(255, 255, 255), 2);
//					putText(frame, win[class1], Point(x * 5, y * 5), FONT_ITALIC, 2, Scalar(0, 255, 0), 2);
//					rectangle(frame, rect, Scalar(127, 255, 0), 2);
//					imshow("Sasha", frame);
//					f1++;
//				}
//				c = (char)waitKey(10);
//				if (c == 'w')break;
//			}
//			c = 'w';
//			break;
//		}
//		}
//		cv::imshow("Sasha", frame);
//		c = (char)waitKey(2);
//		if (c == 'q')break;
//	}
//	
//	cout << " " << endl;
//	return 0;
//}
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