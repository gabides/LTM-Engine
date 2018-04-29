//
//  detectAndDraw.cpp
//  LTM-Engine
//
//  Created by Gabriel Dittrick on 18/04/2018.
//  Copyright © 2018 Gabriel Dittrick. All rights reserved.
//

#include "Header.h"

vector<cv::Point> detectAndDraw( Mat& img, CascadeClassifier& cascade, bool display)
{
    double scale = 1; //added
    double fx = 1 / scale;
    
    vector<Rect> faces;
    const static Scalar colors[] =
    {
        Scalar(255,0,0),
        Scalar(255,128,0),
        Scalar(255,255,0),
        Scalar(0,255,0),
        Scalar(0,128,255),
        Scalar(0,255,255),
        Scalar(0,0,255),
        Scalar(255,0,255)
    };
    Mat gray, smallImg;
    cvtColor( img, gray, COLOR_BGR2GRAY );
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    cascade.detectMultiScale( smallImg, faces,
                             1.1, 2, 0
                             //|CASCADE_FIND_BIGGEST_OBJECT
                             //|CASCADE_DO_ROUGH_SEARCH
                             |CASCADE_SCALE_IMAGE,
                             Size(30, 30) );


    
    Rect r = faces[0]; // problems if several faces are detected ? which one is n°1 ? I think it's ok
    
    Scalar color = colors[0%8];

    //cout << "top left corner : " << r.tl() << ", width : " << r.width << ", height : " << r.height << endl;
    


    Point topleft = r.tl();
    Point bottomright = r.br();

    
    //rectangle(img, topleft, bottomright,color, 3, 8, 0); // comment this line to erase the rectangle
    

    if (display == true){imshow( "result", img);};
    vector<Point> v;
    v.push_back(topleft);
    v.push_back(bottomright);
    return v;
}

