//
//  Motor_control.cpp
//  Sprite Project
//
//  Created by Yoann Blanchot on 17/04/2018.
//  Copyright © 2018 Yoann Blanchot. All rights reserved.
//

#include "Color_tracking.hpp"

//conversion degré/temps d'impulsion (et inversement)
int map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
 unité des servomoteurs: 1000ème de 20ms (= 1 unit) = 20 microsecondes (10^(-6))
 "0" (1,5ms pulse) --> 75 units
 "90" (2ms pulse) --> 100 units
 "-90" (1ms pulse) --> 50 units
 */


void position(CvPoint coord,int* val)
{
    //position courante des servo
    int pos_x = 5;
    int pos_y = 5;
    
    //intervalle autour du centre de l'image
    int x_min = 300-20;
    int x_max = 300+20;
    int y_min = 250-15;
    int y_max = 250+15;
    
    //conversion en angle
    int i;
    int angle[2];
    for(i=0;i<2;i++)
        angle[i]=map(val[i],50,100,-90,90);
    
    // Conditions sur y
    if (coord.y > y_max)
        val[1]=map(angle[1]+pos_y,-90,90,50,100);
    if (coord.y < y_min)
        val[1]=map(angle[1]-pos_y,-90,90,50,100);
    // Conditions sur x
    if (coord.x > x_max)
        val[0]=map(angle[0]+pos_x,-90,90,50,100);
    if (coord.x < x_min)
        val[0]=map(angle[0]-pos_x,-90,90,50,100);
}
