
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

	int X = -1;
	int Y = -1;
	VideoCapture cap(0);   // open default camer

	if (!cap.isOpened()){
		cout << "ERROR Camera is not working" << endl;
		exit(0);
	}
	else
	{
		Mat frameHSV;  // Przechowuje obraz HSV

		//vector< vector<Point> > contours;   // Dwa vektory potrzebne dla outputu z findcontours
		//vector<Vec4i> hierarchy;


		
	
		Mat trackedLines(480, 640, CV_8UC3, Scalar(0, 0, 0));  // Czarny mat dla linii
		Mat tracker(480, 640, CV_8UC3, Scalar(0, 0, 0));  // Czarny mat dla linii
		cout << "Video display - success. Press ESC to exit." << endl;
		while (cap.isOpened())
		{

			Mat frame;  // Standardowy input
			cap.read(frame); // dodaj frame z camery

			if (!cap.read(frame))
				break;

			cvtColor(frame, frameHSV, COLOR_BGR2HSV);

			Mat filtr;

			//inRange(frameHSV, Scalar(0, 180, 158), Scalar(11, 255, 255), filtr); // Dla czerwonej pokrywki
			inRange(frameHSV, Scalar(0, 180, 158), Scalar(200, 255, 255), filtr); // Dla czerwonej pokrywki w swietle
			//inRange(edges, Scalar(90, 153, 228), Scalar(116, 225, 255), filtr); // Dla niebieskiego korka
			//inRange(edges, Scalar(30, 28, 135), Scalar(86, 160, 255), filtr); // Dla zielonej zapalniczki
		
			// DODAC ERODE I DILATE !_!
			dilate(filtr, filtr, (-1, -1)); // -1-1 - centre obiektu 
				erode(filtr, filtr,(-1,-1));
			
			// findContours(filtr, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE); // fatal error 

			//Moze 5sec nagrywania, ostatnia klatka filmu z filtrem czerwonym i przyrownanie do patternu ?! 

			Moments filtrMoments = moments(filtr);
			double dM01 = filtrMoments.m01;
			double dM10 = filtrMoments.m10;
			double centralMoment = filtrMoments.m00;
			int centerXY[2];
			centerXY[0] = dM10 / centralMoment;   //center [0] dla X, [1] dla Y
			centerXY[1] = dM01 / centralMoment;


			if (X > -1 && Y > -1 && centerXY[0] > -1 && centerXY[1] > -1){   // zapobiega rysowaniu linii od gornego rogu -1-1
				line(tracker, Point(centerXY[0], centerXY[1]), Point(X, Y), Scalar(255, 0, 0), 2);  // Scalar (BGR), rysuje od X do centerXY[0]...
			}
			
			X = centerXY[0];
			Y = centerXY[1];

			frame = frame + tracker;

			imshow("Main", frame);
			imshow("HSVview", frameHSV);
			imshow("FilteredRed", filtr);
			imshow("Tracker", tracker);
			imshow("TrackedLines", trackedLines);





			int k = waitKey(30);
			if (k == 27) {   // ASCII 27 dla ESC, czekaj 30ms
				break;
			}
		}
	}
	cap.release();

	return 0;
}
