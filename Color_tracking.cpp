//
//  Color_tracking.cpp
//  Sprite Project
//
//  Created by Yoann Blanchot on 17/04/2018.
//  Copyright © 2018 Yoann Blanchot. All rights reserved.
//

#include "Color_tracking.hpp"

int main() {

    // Image & hsvImage
    IplImage *image;
    //IplImage *hsv;
    // Video Capture
    CvCapture *capture;
    // Key for keyboard event
    char key='o';
    
    // Number of tracked pixels
    int nbPixels;
    // Next position of the object we overlay
    CvPoint objectNextPos;
    //écriture dans ttyACM0
    FILE* File;
    // Initialize the video Capture
    capture = cvCreateCameraCapture(CV_CAP_ANY);
    
    // Check if the capture is ok
    if (!capture) {
        printf("Can't initialize the video capture.\n");
        return -1;
    }
    
    // Create the windows
    cvNamedWindow("Sprite Project _ CAMERA", CV_WINDOW_AUTOSIZE);
    //cvResizeWindow("Sprite Project _ CAMERA",500,500);
    cvNamedWindow("Sprite Project _ Mask", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Sprite Project _ CAMERA", 0, 100);
    cvMoveWindow("Sprite Project _ Mask", 650, 100);
    
    // Mouse event to select the tracked color on the original image
    cvSetMouseCallback("Sprite Project _ CAMERA", getObjectColor);
    
    // Ouverture du fichier de communication : macOSX : "/dev/tty.usbmodem1422" ; Linux : "/dev/ttyACM0"
    File = fopen("/dev/tty.usbmodem1422","w"); // mac OSX
    //File = fopen("/dev/ttyACM0","w"); // Linux
    if(!File){
        printf("Port non reconnu.\n");
        return -1;
    }
    int val[2]={0,0};
    
    /* Boucle principale */
    
    // While we don't want to quit
    while(key != 'Q' && key != 'q') {
        // We get the current image
        image = cvQueryFrame(capture);
        
        // If there is no image, we exit the loop
        if(!image)
            continue;
        
        cvDrawCircle(image, cvPoint(325, 250), 15, CV_RGB(255, 255, 0), -1);
        objectNextPos = binarisation(image, &nbPixels);
        addObjectToVideo(image, objectNextPos, nbPixels);
        
        position(objectNextPos,val);
        
        fprintf(File,"%d %d",val[0],val[1]);
        
        // We wait 10 ms
        key = cvWaitKey(10);
        return 0;
        
    }
    
    //Fermeture du fichier
    fclose(File);
    
    // Destroy the windows we have created
    cvDestroyWindow("Sprite Project _ CAMERA");
    cvDestroyWindow("Sprite Project _ Mask");
    
    // Destroy the capture
    cvReleaseCapture(&capture);
    
    return 0;
    
}
