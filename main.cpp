#include <QCoreApplication>

#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
using namespace cv;
Mat mat2gray(const Mat& src)
{
    Mat dst;
    normalize(src, dst, 0.0, 1, NORM_MINMAX, CV_32FC1);
    return dst;
}

int main()
{


    Mat image;
    Mat img;

    img= imread("/home/raman/MEGA/MEGAsync/documents/MATLAB/infrared_images/img_002.bmp", 0);
    img.convertTo(image, CV_32FC1);
    namedWindow("original image");
    imshow("original image", img);


    Point anchor;
    anchor = Point(-1, -1);


    double delta = 0;

    Mat mu3,mu5,mu7,mu9;
    Mat mub;
    Mat mun3,mun5,mun7,mun9;
    Mat temp3,temp5,temp7,temp9;
    Mat out3,out5,out7,out9;
    Mat outs3,outs5,outs7,outs9;
    Mat outf3,outf5,outf7,outf9;

    Mat s3,s5,s7,s9;

    Mat diff3,diff31,diff32,diff33,diff34, difftemp31,difftemp32;
    Mat diff5,diff51,diff52,diff53,diff54, difftemp51,difftemp52;
    Mat diff7,diff71,diff72,diff73,diff74, difftemp71,difftemp72;
    Mat diff9,diff91,diff92,diff93,diff94, difftemp91,difftemp92;


    Mat max1,max2;
    Mat ADMCDD_out;
    Mat temp_thresh3,temp_thresh5,temp_thresh7,temp_thresh9;
    Mat temp_threshd3,temp_threshd5,temp_threshd7,temp_threshd9;


    double minVal3, minVal5, minVal7, minVal9;
    double maxVal3, maxVal5, maxVal7, maxVal9;
    Point minLoc3, minLoc5, minLoc7, minLoc9;
    Point maxLoc3, maxLoc5, maxLoc7, maxLoc9;

    double minVald3, minVald5, minVald7, minVald9;
    double maxVald3, maxVald5, maxVald7, maxVald9;
    Point minLocd3, minLocd5, minLocd7, minLocd9;
    Point maxLocd3, maxLocd5, maxLocd7, maxLocd9;



    // internal and external windows sizing

    double bnhood = 19;
    double tnhood3 = 3;
    double tnhood5 = 5;
    double tnhood7 = 7;
    double tnhood9 = 9;


    double Nb=bnhood*bnhood;
    double N3=tnhood3*tnhood3;
    double N5=tnhood5*tnhood5;
    double N7=tnhood7*tnhood7;
    double N9=tnhood9*tnhood9;


    double Ndiff3=Nb-N3;
    double Ndiff5=Nb-N5;
    double Ndiff7=Nb-N7;
    double Ndiff9=Nb-N9;


    Mat mask31=Mat::zeros(5,5, CV_32FC1);
    Mat mask32=Mat::zeros(5,5, CV_32FC1);
    Mat mask33=Mat::zeros(5,5, CV_32FC1);
    Mat mask34=Mat::zeros(5,5, CV_32FC1);

    mask31(Rect(2,1,1,2))=1;
    mask31(Rect(2,0,1,1))=-2;

    mask32(Rect(2,2,2,1))=1;
    mask32(Rect(4,2,1,1))=-2;

    mask33(Rect(2,2,1,2))=1;
    mask33(Rect(2,4,1,1))=-2;

    mask34(Rect(1,2,2,1))=1;
    mask34(Rect(0,2,1,1))=-2;




    Mat mask51=Mat::zeros(7,7, CV_32FC1);
    Mat mask52=Mat::zeros(7,7, CV_32FC1);
    Mat mask53=Mat::zeros(7,7, CV_32FC1);
    Mat mask54=Mat::zeros(7,7, CV_32FC1);



    mask51(Rect(3,1,1,3))=1;
    mask51(Rect(3,0,1,1))=-3;

    mask52(Rect(3,3,3,1))=1;
    mask52(Rect(6,3,1,1))=-3;

    mask53(Rect(3,3,1,3))=1;
    mask53(Rect(3,6,1,1))=-3;

    mask54(Rect(1,3,3,1))=1;
    mask54(Rect(0,3,1,1))=-3;


    Mat mask71=Mat::zeros(9,9, CV_32FC1);
    Mat mask72=Mat::zeros(9,9, CV_32FC1);
    Mat mask73=Mat::zeros(9,9, CV_32FC1);
    Mat mask74=Mat::zeros(9,9, CV_32FC1);



    mask71(Rect(4,1,1,4))=1;
    mask71(Rect(4,0,1,1))=-4;

    mask72(Rect(4,4,4,1))=1;
    mask72(Rect(8,4,1,1))=-4;

    mask73(Rect(4,4,1,4))=1;
    mask73(Rect(4,8,1,1))=-4;

    mask74(Rect(1,4,4,1))=1;
    mask74(Rect(0,4,1,1))=-4;

    Mat mask91=Mat::zeros(11,11, CV_32FC1);
    Mat mask92=Mat::zeros(11,11, CV_32FC1);
    Mat mask93=Mat::zeros(11,11, CV_32FC1);
    Mat mask94=Mat::zeros(11,11, CV_32FC1);



    mask91(Rect(5,1,1,5))=1;
    mask91(Rect(5,0,1,1))=-5;

    mask92(Rect(5,5,5,1))=1;
    mask92(Rect(10,5,1,1))=-5;

    mask93(Rect(5,5,1,5))=1;
    mask93(Rect(5,10,1,1))=-5;

    mask94(Rect(1,5,5,1))=1;
    mask94(Rect(0,5,1,1))=-5;
 // mean value calculation for internal window for all scales

    blur(image, mu3, Size(tnhood3, tnhood3),anchor,BORDER_REPLICATE);
     blur(image, mu5, Size(tnhood5, tnhood5),anchor,BORDER_REPLICATE);
      blur(image, mu7, Size(tnhood7, tnhood7),anchor,BORDER_REPLICATE);
       blur(image, mu9, Size(tnhood9, tnhood9),anchor,BORDER_REPLICATE);

       //mean value calculation for external window

    blur(image, mub, Size(bnhood, bnhood),anchor,BORDER_REPLICATE);



       //constructing ADM_prop and CDD in  3by3 scale


    mun3=N3*mu3;

    mub=Nb*mub;


    temp3=(mub-mun3)/Ndiff3;
    s3=mu3-temp3;
    outs3=s3.clone();
    minMaxLoc(outs3, &minVal3, &maxVal3, &minLoc3, &maxLoc3 );

    threshold(outs3, temp_thresh3 , 0,maxVal3, THRESH_TOZERO );

    pow(temp_thresh3,2,out3);


    filter2D(image, diff31, -1, mask31, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff32, -1, mask32, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff33, -1, mask33, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff34, -1, mask34, anchor,delta, BORDER_REPLICATE);

    min(diff31,diff32,difftemp31);

    min(difftemp31, diff33,difftemp32);


    min(difftemp32,diff34,diff3);

    minMaxLoc(diff3, &minVald3, &maxVald3, &minLocd3, &maxLocd3 );

    threshold(diff3, temp_threshd3 , 0,maxVald3, THRESH_TOZERO );


    outf3=temp_threshd3.mul(out3);

    //constructing ADM_prop and CDD in  5by5 scale


        mun5=N5*mu5;




    temp5=(mub-mun5)/Ndiff5;

    s5=mu5-temp5;
    outs5=s5.clone();
    minMaxLoc(outs5, &minVal5, &maxVal5, &minLoc5, &maxLoc5 );


    threshold(outs5, temp_thresh5 , 0,maxVal5, THRESH_TOZERO );

    pow(temp_thresh5,2,out5);

    filter2D(image, diff51, -1, mask51, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff52, -1, mask52, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff53, -1, mask53, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff54, -1, mask54, anchor,delta, BORDER_REPLICATE);

    min(diff51,diff52,difftemp51);

    min(difftemp51, diff53,difftemp52);

    min(difftemp52,diff54,diff5);

    minMaxLoc(diff5, &minVald5, &maxVald5, &minLocd5, &maxLocd5 );

    threshold(diff5, temp_threshd5 , 0,maxVald5, THRESH_TOZERO );


    outf5=temp_threshd5.mul(out5);

    //constructing ADM_prop and CDD in  7by7 scale


        mun7=N7*mu7;




    temp7=(mub-mun7)/Ndiff7;

    s7=mu7-temp7;
    outs7=s7.clone();
    minMaxLoc( outs7, &minVal7, &maxVal7, &minLoc7, &maxLoc7 );


    threshold(outs7, temp_thresh7 , 0,maxVal7, THRESH_TOZERO );

    pow(temp_thresh7,2,out7);


    filter2D(image, diff71, -1, mask71, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff72, -1, mask72, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff73, -1, mask73, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff74, -1, mask74, anchor,delta, BORDER_REPLICATE);


    min(diff71,diff72,difftemp71);

    min(difftemp71, diff73,difftemp72);

    min(difftemp72,diff74,diff7);

    minMaxLoc(diff7, &minVald7, &maxVald7, &minLocd7, &maxLocd7 );

    threshold(diff7, temp_threshd7 , 0,maxVald7, THRESH_TOZERO );


    outf7=temp_threshd7.mul(out7);


    //constructing ADM_prop and CDD in  9by9 scale


        mun9=N9*mu9;




    temp9=(mub-mun9)/Ndiff9;
    s9=mu9-temp9;
    outs9=s9.clone();
    minMaxLoc( outs9, &minVal9, &maxVal9, &minLoc9, &maxLoc9 );

    threshold(outs9, temp_thresh9 , 0,maxVal9, THRESH_TOZERO );

    pow(temp_thresh9,2,out9);

    filter2D(image, diff91, -1, mask91, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff92, -1, mask92, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff93, -1, mask93, anchor,delta, BORDER_REPLICATE);
    filter2D(image, diff94, -1, mask94, anchor,delta, BORDER_REPLICATE);

    min(diff91,diff92,difftemp91);

    min(difftemp91, diff93,difftemp92);

    min(difftemp92,diff94,diff9);

    minMaxLoc(diff9, &minVald9, &maxVald9, &minLocd9, &maxLocd9 );

    threshold(diff9, temp_threshd9 , 0,maxVald9, THRESH_TOZERO );


    outf9=temp_threshd9.mul(out9);

           //output response by maximum selection along scale dimension


    max(outf3,outf5,max1);

    max(max1, outf7,max2);


    max(max2,outf9,ADMCDD_out);

    namedWindow("output image");
    imshow("output image", mat2gray(ADMCDD_out));

//    namedWindow("TEST");
//    imshow("TEST", mat2gray(mask91));

//    namedWindow("TEST2");
//    imshow("TEST2", mat2gray(mask92));

//    namedWindow("TEST3");
//    imshow("TEST3", mat2gray(mask93));

//    namedWindow("TEST4");
//    imshow("TEST4", mat2gray(mask94));

    cv::waitKey(0);
    return EXIT_SUCCESS;
}
