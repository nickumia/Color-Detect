/* HSV Color Code:

    Color               Hue      Saturation    Value
    Red     ...     163 - 179    161 - 228   116 - 169
    Orange  ...     0 - 12       112 - 227   134 - 255
    Yellow  ...     22 - 34      38 - 244    160 - 255
    Green   ...     45 - 108     39 - 153    92 - 255
    Blue    ...     92 - 135     62 - 176    32 - 126
    Purple  ...     109 - 139    58 - 148    43 - 87

    **Note: Color May Vary depending on lighting!
*/

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat imgOriginal;
Mat imgCircles;
Mat imgThresholded;

void HSVOnly(int, int, int, int, int, int);
void Location();
void ImageFinalization();
void DebugSize();

 int main()
 {
    int iLowH = 0;
    int iHighH = 44;

    int iLowS = 161;
    int iHighS = 228;

    int iLowV = 46;
    int iHighV = 179;

    namedWindow("Control", CV_WINDOW_NORMAL); //create a window called "Control"
    namedWindow("Camera", CV_WINDOW_NORMAL);

    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);

    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);

    cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighV, 255);

    VideoCapture cam(0);

    while(1)
    {
        cam.read(imgOriginal);

        HSVOnly(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);
        Location();
        ImageFinalization();

        imshow("Thresholded Image", imgThresholded); //show the thresholded image
        imshow("Camera", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "Who pressed the ESC Key?!" << endl;
            destroyAllWindows();
            break;
        }
    }

   return 0;
}

void HSVOnly(int iLowH, int iHighH, int iLowS, int iHighS, int iLowV, int iHighV)
{
    Mat imgHSV;

    //Convert the captured frame from BGR to HSV
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

    //Threshold the image
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

    //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    //morphological closing (fill small holes in the foreground)
    //dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    //erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    //dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
}

void Location()
{
    imgCircles = Mat::zeros( imgOriginal.size(), CV_8UC3 );
    Moments oMoments = moments(imgThresholded);

    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    if (dArea > 10000)
    {
        //calculate the position of the ball
        int posX = dM10 / dArea;
        int posY = dM01 / dArea;

        if (posX >= 0 && posY >= 0)
        {
            //Draw a red circle encompassing object
            circle(imgCircles, Point(posX, posY), 25, Scalar(0, 0, 255), 1, 8, 1);
            circle(imgCircles, Point(posX, posY), 26, Scalar(0, 0, 255), 1, 8, 1);
            circle(imgCircles, Point(posX, posY), 27, Scalar(0, 0, 255), 1, 8, 1);
            circle(imgCircles, Point(posX, posY), 24, Scalar(0, 0, 255), 1, 8, 1);
            circle(imgCircles, Point(posX, posY), 23, Scalar(0, 0, 255), 1, 8, 1);
        }
    }
}

void ImageFinalization()
{
    line(imgOriginal, Point(320,230), Point(320,250), Scalar(255, 0, 255), 1, 8);
    line(imgOriginal, Point(310,240), Point(330,240), Scalar(255, 0, 255), 1, 8);

    imgOriginal = imgOriginal + imgCircles;
}

void DebugSize()
{
    cout << imgCircles.size() << "\t" << imgCircles.channels() << "\t"
         << imgOriginal.size() << "\t" << imgOriginal.channels() << endl;
}
