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
    radius = dy/4;

    //AU = 0 neutral face

    
    //milieux //rajouter toutes les AU !
    
    
    if (AU == "4") //front entre sourcils // brow lowerer
    {
        center.x = xmid;
        center.y = ymid - dy/4.;
    }
    else if (AU == "8" or AU == "22" or AU == "23" or AU == "24" or AU == "25" or AU == "28")// mouth (AV)
        //8: lips toword each other / 22: lip funneler / 23: lip tightener / 24: lip pressor / 25: lips part(??) / 28 lip suck
    {
        center.x = xmid;
        center.y = ymid +1*dy/3.;
    }
    
    else if (AU == "9") //nose wrinckler (AV)
    {
        center.x = xmid;
        center.y = ymid +1*dy/4.;
    }
    else if (AU == "10") //upper lip raiser (AV)
    {
        center.x = xmid;
        center.y = ymid +1*dy/4.;
    }
    else if (AU == "17") //chin raiser ok
    {
        center.x = xmid;
        center.y = ymid +1.2*dy/2.;
    }
    
    else if (AU == "21") //neck tightener (AV)
    {
        center.x = xmid;
        center.y = ymid +3*dy/4.;
    }
    
    else if (AU == "26") // jaw drop (AV)
    {
        center.x = xmid;
        center.y = ymid + dy/2.;
    }
    else if (AU == "27") // mouth stretch (AV)
    {
        center.x = xmid;
        center.y = ymid + dy/3.;
    }
    
    //19 = tongue show ??
    
    //symétriques
    else if (AU == "1")  //inner brow  à verifier (AV)
    {
        center.x = xmid - dy/4.;
        center.y = ymid - dy/4.;
    }
    else if (AU == "2")  //outer brow (AV)
    {
        center.x = xmid - dy/3.;
        center.y = ymid - dy/4.;
    }
    
    else if (AU == "5")  //upper lid (AV)
    {
        center.x = xmid - dy/4.;
        center.y = ymid - dy/4.5;
    }
    else if (AU == "6")  //cheek raiser (AV) // under the eye
    {
        center.x = xmid - dy/4.;
        center.y = ymid - dy/3.;
    }
    else if (AU == "7")  //lids tightener (AV) // under the eye
    {
        center.x = xmid - dy/4.;
        center.y = ymid - dy/3.;
    }
    else if (AU == "11")  //Nasolabial deepener (AV?)
    {
        center.x = xmid - dy/4.;
        center.y = ymid + dy/4.;
    }
    
    else if (AU == "12") //pomettes // lip corner puller ok (ArV?)
    {
        center.x = xmid - 1.2*dy/4.;
        center.y = ymid + dy/4.;
    }
    else if (AU == "13") //sharp lip  puller  (AV)
    {
        center.x = xmid - 0.8*dy/4.;
        center.y = ymid + dy/4.;
    }
    else if (AU == "14") //Dimpler/buccinator  (AV)
    {
        center.x = xmid - 0.8*dy/4.;
        center.y = ymid + dy/3.;
    }
    else if (AU == "15") //lip corner depressor  (AV)
    {
        center.x = xmid - dy/8.;
        center.y = ymid + dy/3.;
    }
    else if (AU == "16") //lower lip depressor  (AV)
    {
        center.x = xmid - dy/10.;
        center.y = ymid + dy/3.;
    }
    else if (AU == "18") //lip pucker (AV)
    {
        center.x = xmid - 0.6*dy/4.;
        center.y = ymid + dy/3.;
    }
    else if (AU == "20") // lip stretcher (AV)
    {
        center.x = xmid - 1.4*dy/4.;
        center.y = ymid + dy/4.; // dy/3 ?
    }
    

    else // ?
    {
        center.x = xmid;
        center.y = ymid;
        radius = 0;
    }
    
    Point center2 = Point(2*xmid-center.x,center.y);
    circle( img, center, radius, color, 3, 8, 0 );
    circle( img, center2 , radius, color, 3, 8, 0 );


    Point textpoint = Point(center.x+radius+4, center.y);
    putText(img, emotion, textpoint,
           FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    imshow( "result", img );
}
