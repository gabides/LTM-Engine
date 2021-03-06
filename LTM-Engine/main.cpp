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
    cout << "\n This engine is part of the LTM microexpressions analysis project.\n With the engine you can annotate a video with the related micro-exressions (from the video .txt file). It will result in a new video in output with details about the micro expression\n\n"
    "Usage:\n"
    "./LTM-Engine [--inputname=<input video filename> this is the video you want to analyse] = mandatory\n"
    "             [--outputname=<output video filename> this is the path of the video you want to write] = optional (if not chosen the video will be writen to 'OUT'+inputname\n"
    "             [--color=<integer between 0 and 7> to choose the color in which to show the ME] = optional\n"
    "             [--livedisplay= to choose whether to show the video while its being processed] = optional\n"
    "During execution:\n\tHit any key to quit.\n"
    "\n"
    "\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}

string cascadeName;

vector<Point> detectAndDraw( Mat& img, CascadeClassifier& cascade);

void drawScreen( Mat& img, int AU, Point tl, Point br, string emotion, int nColor);

vector<MicroExpression> txtToMEVector(string txtpath);

void drawScreen2( Mat& img){imshow( "result", img );}


int main(int argc, const char * argv[]) {
    void    ofSetDataPathRoot( string root );

    double t = 0;
    t = (double)getTickCount();

    CascadeClassifier cascade;  // for face detection, will only use cascade
    cascadeName = "Detector/haarcascade_frontalface_alt2.xml";
    cascade.load( cascadeName );
    
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    string outputName;
    double fps;
    bool display;
    int nColor;

    cv::CommandLineParser parser(argc, argv,
                                 "{help h||}"
                                 "{inputname|CASMEA/EP09_4.avi|}"
                                 "{outputname||}"
                                 "{livedisplay|true|}"
                                 "{color|5|}");

    if (parser.has("help"))
    {
        help();
        return 0;
    }
    
    
    inputName = parser.get<string>("inputname");
    outputName = parser.get<string>("outputname");
    display = parser.get<bool>("livedisplay");
    nColor= parser.get<int>("color");
    
    cout << "input name : " << inputName << endl << "given output name : " + outputName << endl;


    if (outputName == "")
    {
        outputName = "OUTPUT/"+inputName;
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

    
    int countME;
    
    
    std::vector<MicroExpression> ME;
    ME = txtToMEVector(txtpath);
    countME = (int)ME.size();
    
    cout << "number of microexpressions in the video : " << countME << endl;
    
    Point topleft;
    Point bottomright;

    vector<cv :: Point> points;

    cout << "Video capturing has been started ..." << endl;
    int refreshFaceDetectFrequency = 25;

    for(int i = 0; i < len ;i++)
    {

        capture >> frame;
        if( frame.empty() )
            break;
    
        
        if (i%refreshFaceDetectFrequency == 0){ // =5 : if =0 and first frames are black there will be an error with detectAndDraw
            points = detectAndDraw(frame, cascade);
            topleft = points[0];
            bottomright = points[1];
        }
        

        for (int k = 0; k< countME; k++){
            //cout <<"(i,k) = (" << i << "," << k << ") onset = " << ME[k].onset << ", offset = " << ME[k].offset << endl;
            if ((i>ME[k].onset-5) & (i<ME[k].offset+5)) // +/-5 frames to see more clearly when the faces changes
            {
                //cout <<"(i,k) = (" << i << "," << k << ") microExpression being drawn " << endl;
                drawScreen(frame, ME[k].AU, topleft, bottomright, ME[k].emotion, nColor);
            }
        }
    
        if (display == true){imshow( "result", frame );}
        video.write(frame);        // Write the frame into the file "outputName"

        char c = (char)waitKey(50); //why 10 ?
        
        if( c == 27 || c == 'q' || c == 'Q' ) // ?
            break;
    }
    capture.release();
    video.release();
    t = (double)getTickCount() - t;
    printf( "detection time = %g s\n", t/getTickFrequency());
    
    // Closes all the windows
    destroyAllWindows();
    
    
    return 0;
}



