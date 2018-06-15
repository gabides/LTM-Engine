# LTM-Engine
C++ application for micro-expressions detection and recognition with graphical interface (video player). This engine is the video editing part of the app (displays the ME at the right place and time in the video, with annotations). OpenCV is necessary to run the app.

 This engine is part of the LTM microexpressions analysis project.  
 With the engine you can annotate a video with the related ME (from the video .txt file). It will result in a new video in output with details about the micro-expression (location of the ME, and feeling related)


The interface is being implemented for OSX with Swift language in another project ([LTM-interface](https://github.com/gabides/LTM-Interface-cocoa/)), and the detection/recognition runs in an independent app.



Usage:  
./LTM-Engine  
[--inputname={input video filename} this is the video you want to analyse] = mandatory  
[--outputname={output video filename} this is the path of the video you want to write] = optional (if not chosen the video will be writen to "OUT"+inputname  
[--color={integer between 0 and 7} to choose the color in which to show the ME] = optional  
[--livedisplay={true or false} to choose whether to show the video while its being processed] = optional  
During execution:
Hit any key to quit.

This app was developped using OpenCV version 3.4.1


ME = micro-expression


Year-long project with Louis Lenief at CentraleSupélec (2018) and the Facial Analysis Synthesis and Tracking ([FAST](http://www.rennes.supelec.fr/ren/rd/fast/fast_accueil.php)) research team.

