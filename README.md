# LTM-Engine
C++ application for detecting, recognizing and showing micro-expressions on a graphical interface. OpenCV is necessary to run the app.

 This engine is part of the LTM microexpressions analysis project.
 With the engine you can annotate a video with the related ME (from the video .txt file). It with result in a new video in output with details about the micro expression (location of the ME, and feeling related)


The interface is being implemented for OSX with Swift language in another project, and the detection/recognition runs in an independent app.

Year-long project with Louis Lenief at CentraleSupélec (2018) and the Facial Analysis Synthesis and Tracking (FAST) research team.


Usage:
./LTM-Engine [--inputname=<input video filename> this is the video you want to analyse]
   [--outputname=<output video filename> this is the path of the video you want to write]
During execution:
	Hit any key to quit.

This app was developped using OpenCV version 3.4.1


ME = micro-expression
