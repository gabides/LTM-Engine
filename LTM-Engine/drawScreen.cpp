//
//  drawScreen.cpp
//  LTM-Engine
//
//  Created by Gabriel Dittrick on 18/04/2018.
//  Copyright © 2018 Gabriel Dittrick. All rights reserved.
//

#include "Header.h"

void drawScreen( Mat& img, string AU, Point tl, Point br, string emotion)
{
    vector<string> actionUnits;
    
    int xleft, ytop, xright, ybottom;
    

    xleft = tl.x;
    ytop = tl.y;
    xright = br.x;
    ybottom = br.y;
    
    
    double xmid = (xleft + xright)/2.;
    double ymid = (ytop + ybottom)/2.;
    
    double dx = (xright- xleft);
    double dy = (ybottom - ytop);
    
    /*
     Point middle = Point(xmid,ymid);
    Point vertical = Point(0,1);
    int width = img.cols;
    int height=img.rows;
     */
    Point center;
    int radius;
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
    
    Scalar color = colors[3];
    
    
    //milieux //rajouter toutes les AU !
    if (AU == "4")
    {
        center.x = xmid;
        center.y = ymid - dy/4.;
        radius = dy/4;
    }
    else if (AU == "17") //chin
    {
        center.x = xmid;
        center.y = ymid +1.2*dy/2.;
        radius = dy/4;
    }
    
    //symétriques
    else if (AU == "12")
    {
        center.x = xmid - dy/4;
        center.y = ymid + dy/4.;
        
        radius = dy/4;
        Point center2 = Point(2*xmid-center.x,center.y);
        circle( img, center2 , radius, color, 3, 8, 0 );

    }
    
    else
    {
        center.x = xmid;
        center.y = ymid;
        radius = dy/4;
        
    }
    
    circle( img, center, radius, color, 3, 8, 0 );
    Point textpoint = Point(center.x+radius+4, center.y);
    putText(img, emotion, textpoint,
           FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    imshow( "result", img );
}
