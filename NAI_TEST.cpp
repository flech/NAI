
#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include <opencv2\\opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main()
{


	VideoCapture cap(0);   // open default camer

	if (!cap.isOpened()){
		cout << "ERROR Camera is not working" << endl;
		exit(0);
	}
	else
	{

		Mat frameHSV;  // Przechowuje obraz HSV
		cout << "Video display - success. Press ESC to exit." << endl;
		while (cap.isOpened())
		{
			Mat frame;  // Standardowy input
			cap.read(frame); // dodaj frame z camery


			Mat trackLines(480, 640, CV_8UC3, Scalar(0, 0, 0));  // Czarny mat dla linii


			if (!cap.read(frame))
				break;

			cvtColor(frame, frameHSV, COLOR_BGR2HSV);

			Mat filtr;

			inRange(frameHSV, Scalar(0, 180, 158), Scalar(11, 255, 255), filtr); // Dla czerwonej pokrywki
			//inRange(frameHSV, Scalar(0, 180, 158), Scalar(200, 255, 255), filtr); // Dla czerwonej pokrywki w swietle
			//inRange(edges, Scalar(90, 153, 228), Scalar(116, 225, 255), filtr); // Dla niebieskiego korka
			//inRange(edges, Scalar(30, 28, 135), Scalar(86, 160, 255), filtr); // Dla zielonej zapalniczki
		
			// DODAC ERODE I DILATE !_!
			dilate(filtr, filtr, (-1, -1)); // -1-1 - centre obiektu 
			erode(filtr, filtr,(-1,-1));
			


			//Moze 5sec nagrywania, ostatnia klatka filmu z filtrem czerwonym i przyrownanie do patternu ?! 

			imshow("Main", frame);
			imshow("HSVview", frameHSV);
			imshow("FilteredRed", filtr);
		//	imshow("asd", trackLines);



			int k = waitKey(100);
			if (k == 27) {   // ASCII 27 dla ESC
				break;
			}
		}
	}
	cap.release();

	return 0;
}
