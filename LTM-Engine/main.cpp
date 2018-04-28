//
//  main.cpp
//  LTM-Engine
//
//  Created by Gabriel Dittrick on 17/04/2018.
//  Copyright © 2018 Gabriel Dittrick. All rights reserved.
//


#include "Header.h"

static void help()
{
    cout << "\n This engine is part of the LTM microexpressions analysis project.\n With the engine you can annotate a video with the related micro-exressions (from the video .txt file). It with result in a new video in output with details about the micro expression\n\n"
    "Usage:\n"
    "./LTM-Engine [--inputname=<input video filename> this is the video you want to analyse]\n"
    "   [--outputname=<output video filename> this is the path of the video you want to write]\n"
    "During execution:\n\tHit any key to quit.\n"
    "\n"
    "\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}

string cascadeName;


vector<Point> detectAndDraw( Mat& img, CascadeClassifier& cascade, bool display);


void drawScreen( Mat& img, int AU, Point tl, Point br, string emotion, bool display);


vector<vector<string>> txtToVector(string txtpath);


void drawScreen2( Mat& img){imshow( "result", img );}





int main(int argc, const char * argv[]) {
    void    ofSetDataPathRoot( string root );

    
   
    CascadeClassifier cascade;  // for face detection, will only use cascade
    cascadeName = "Detector/haarcascade_frontalface_alt2.xml";
    cascade.load( cascadeName );
    
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    string outputName;
    double fps;
    bool display;

    cv::CommandLineParser parser(argc, argv,
                                 "{help h||}"
                                 "{inputname|EP07_10.avi|}"
                                 "{outputname||}"
                                 "{livedisplay|true|}");

    if (parser.has("help"))
    {
        help();
        return 0;
    }
    
    
    inputName = parser.get<string>("inputname");
    outputName = parser.get<string>("outputname");
    display = parser.get<bool>("livedisplay");
    
    cout << "input name : " << inputName << endl << "given output name : " + outputName << endl;


    if (outputName == "")
    {
        outputName = "OUT"+inputName;
    }
    
    cout << "output name : " + outputName << endl;
    
    capture.open(inputName);
    capture >> frame;
    
    fps = capture.get(CAP_PROP_FPS);
    
    
    // Check if camera opened successfully
    if(!capture.isOpened())
    {
        cout << "Error opening video stream" << endl;
        return -1;
    }
    
    
    int frame_width = frame.cols;
    int frame_height = frame.rows;
    int len = capture.get(CAP_PROP_FRAME_COUNT);
    cout << "video has " << len << " frames" << endl;
    
    
    VideoWriter video(outputName,CV_FOURCC('M','J','P','G'),fps, Size(frame_width,frame_height));

    video.write(frame);
    
    
    //manage the textfile
    string txtpath;// = "../timestamps/";
    //string inputName2 = inputName;
    //inputName2.erase(0,6);
    
    txtpath.append(inputName);
    txtpath.pop_back();
    txtpath.pop_back();
    txtpath.pop_back();
    txtpath.pop_back();
    txtpath.append(".txt");

    cout << "txtpath = " << txtpath << endl;
    int onset;
    int offset;
    string emotion;
    int AU;
    int dimension;
    
    std::vector<std::vector<string>> vect(dimension, std::vector<string>(4));


    vect = txtToVector(txtpath);

    onset = atoi(vect[0][0].c_str());
    
    if(vect[0][1]=="/") {offset = onset+25;}
    else {offset = atoi(vect[0][1].c_str());}
    
    emotion = vect[0][2];
    AU = atoi(vect[0][3].c_str());
    cout << onset << " " << offset << " " << emotion << " " << AU << endl;
    
    
    
    Point topleft;
    Point bottomright;
    vector<cv :: Point> points;

    cout << "Video capturing has been started ..." << endl;
    
    for(int i = 0; i < len ;i++)
    {
        capture >> frame;
        if( frame.empty() )
            break;
        
        Mat frame1 = frame.clone(); // pourquoi ? surement pour du traitement
        
        points = detectAndDraw(frame1, cascade, display);
        
        topleft = points[0];
        bottomright = points[1];
        
        
        if (i>onset && i< offset)
            drawScreen(frame1, AU, topleft, bottomright, emotion, display);
    
        video.write(frame1);        // Write the frame into the file "outputName"

        char c = (char)waitKey(10); //why 10 ?
        
        if( c == 27 || c == 'q' || c == 'Q' ) // ?
            break;
    }
    capture.release();
    video.release();
    
    // Closes all the windows
    destroyAllWindows();
    
    
    return 0;
}



