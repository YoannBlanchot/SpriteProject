//
//  Color_tracking.hpp
//  Sprite Project
//
//  Created by Yoann Blanchot on 17/04/2018.
//  Copyright © 2018 Yoann Blanchot. All rights reserved.
//

#ifndef Color_tracking_hpp
#define Color_tracking_hpp

/* Include section */

//#include "opencv/highgui.h"
//#include "opencv/cv.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

/* Define section */

// Maths methods
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))
#define sign(x) ((x) > 0 ? 1 : -1)
// Step mooving for object min & max
#define STEP_MIN 5
#define STEP_MAX 100

/* Structure section */

/* Prototype section */

CvPoint binarisation(IplImage* image, int *nbPixels);
void addObjectToVideo(IplImage* image, CvPoint objectNextPos, int nbPixels);
void getObjectColor(int event, int x, int y, int flags, void *param);
void position(CvPoint coord,int* val);

#endif /* Color_tracking_hpp */
