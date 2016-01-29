
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
		CascadeClassifier CClassif;
		CClassif.load("cascade.xml");

		if (CClassif.empty()) {
			cout << "ERROR CASCADE NOT LOADED" << endl;
			exit(0);
		}

		Mat track1;
		Mat tracker(480, 640, CV_8UC3, Scalar(0, 0, 0));  // Czarny mat dla linii


		cout << "Video display - success. Press ESC to exit." << endl;

		while (cap.isOpened())
		{

			Mat frame;  // Standardowy input
			cap.read(frame); // dodaj frame z camery

			if (!cap.read(frame))
				break;


			vector<Rect> vectorK;                // Vector kwadrat



			cvtColor(frame, frameHSV, COLOR_BGR2HSV);

			Mat filtr;

			//inRange(frameHSV, Scalar(0, 180, 158), Scalar(11, 255, 255), filtr); // Dla czerwonej pokrywki
			//inRange(frameHSV, Scalar(0, 180, 158), Scalar(200, 255, 255), filtr); // Dla czerwonej pokrywki w swietle
			inRange(frameHSV, Scalar(16, 113, 61), Scalar(37, 256, 206), filtr); // Dla czerwonej pokrywki w swietle
			//inRange(edges, Scalar(90, 153, 228), Scalar(116, 225, 255), filtr); // Dla niebieskiego korka
			//inRange(frameHSV, Scalar(30, 28, 135), Scalar(86, 160, 255), filtr); // Dla zielonej zapalniczki

			// DODAC ERODE I DILATE !_!
			//dilate(filtr, filtr, Mat(), Point(-1, -1),3,1,1); // -1-1 - centre obiektu 
			erode(filtr, filtr, Mat(), Point(-1, -1), 3, 1, 1);

			GaussianBlur(filtr, filtr, Size(5, 5), 0, 0);
			Moments filtrMoments = moments(filtr);
			double dM01 = filtrMoments.m01;
			double dM10 = filtrMoments.m10;
			double centralMoment = filtrMoments.m00;
			int centerXY[2];
			centerXY[0] = dM10 / centralMoment;   //center [0] dla X, [1] dla Y
			centerXY[1] = dM01 / centralMoment;


			if (X > -1 && Y > -1 && centerXY[0] > -1 && centerXY[1] > -1){   // zapobiega rysowaniu linii od gornego rogu -1-1
				line(tracker, Point(centerXY[0], centerXY[1]), Point(X, Y), Scalar(0, 0, 255), 10);  // Scalar (BGR), rysuje od X do centerXY[0]...
			}


			X = centerXY[0];
			Y = centerXY[1];


			frame = frame + tracker;

			//cvtColor(frame, frame, COLOR_BGR2GRAY);

			//DETECTOR !
			CClassif.detectMultiScale(frame, vectorK, 1.1, 5, CV_HAAR_SCALE_IMAGE, Size(50, 360)); //CV_HAAR_DO_CANNY_PRUNING CV_HAAR_SCALE_IMAGE

			for (int i = 0; i < (int)vectorK.size(); i++) {
				Point pt1(vectorK[i].x, vectorK[i].y);
				Point pt2(vectorK[i].x + vectorK[i].width,
					vectorK[i].y + vectorK[i].width);
				// Rysowanie
				rectangle(frame, pt1, pt2, Scalar(255, 0, 0), 2);
			}

			imshow("Main", frame);
			//imshow("HSVview", frameHSV);
			imshow("FilteredRed", filtr);
			imshow("Tracker", tracker);
			//imshow("Grey", track1);


			int k = waitKey(30);
			if (k == 27) {   // ASCII 27 dla ESC, czekaj 30ms
				break;
			}
		}
	}
	cap.release();
	destroyAllWindows();

	return 0;
}
