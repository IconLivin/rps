#include <iostream>
#include "classificator.h"


int main() 
{
	//Initialized arguments
	string name = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
	Mat cap;
	cap = imread("rock.jfif");
	/*string model_path =" ";
	string config_path = " ";
	string label_path = " ";*/
	HandClassificator ds(name);
	//work with video

		Point classIdPoint;
		double confidence;
		minMaxLoc(ds.Classify(cap), 0, &confidence, 0, &classIdPoint);
		cout << "ClassID:" << classIdPoint.x << endl << "Confidence:" << confidence << endl;
		
	
	cout << " " << endl;
	return 0;
}