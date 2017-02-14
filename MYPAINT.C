#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <time.h>
#include "asm.h"
#include "mouse.h"
#include "image.h"
#include "graph.h"
#include "bar.h"


#define v800x600x256             0x103
#define NEW                      1
#define SAVE                     2
#define OPEN                     3
#define PENCIL                   4
#define LINE                     5
#define RECTANGLE                6
#define FILLEDRECTANGLE          7
#define CIRCLE                   8
#define FILLEDCIRCLE             9
#define POLYGON                 10
#define FILLEDPOLYGON           11
#define ERASER                  12
#define BUCKET                  13
#define TEXT                    14
#define EYEDROPPER              15
#define COPY                    16
#define CUT                     17
#define PASTE                   18
#define UNDO                    19
#define PATTERN1                20
#define PATTERN2                21

void main ()
{
    int selectedAction = PENCIL;
    int x, y, b, tempx, tempy;
    int i, j;
    int x1, y1;
    char selectedColor = 0;

    if( !setVideoSVGA(v800x600x256, 800, 600)){
      printf("\r\nError inicializacion de SVGA.\r\n");
      return;
    }

    //Activa el mouse
    setMouse();
    setBoundariesMouse(790, 590);
    getMouse(&x, &y, &b);

    canvas();
    toolBar();

    do {
        refreshMouse(&x, &y, &b, &tempx, &tempy);
        
        //Click New
        if((x > 10 && x < 34) && (y > 8 && y < 41) && b==1){
            canvas();
            toolBar();
        }

        //Click Save
        if((x > 10 && x < 42) && (y > 56 && y < 88) && b==1){

        }

        //Click Open
        if((x > 42 && x < 75) && (y > 12 && y < 88) && b==1){

        }

        //Click Pencil
        if((x > 86 && x < 118) && (y > 8 && y < 40) && b==1){
            selectedAction = PENCIL;
        }

        //Click Line
        if((x > 86 && x < 113) && (y > 52 && y < 88) && b==1){
            selectedAction = LINE;
        }

        //Click Rectangle
        if((x > 125 && x < 157) && (y > 9 && y < 41) && b==1){
            selectedAction = RECTANGLE;
        }

        //Click Filled Rectangle
        if((x > 124 && x < 156) && (y > 55 && y < 87) && b==1){
            selectedAction = FILLEDRECTANGLE;
        }

        //Click Circle
        if((x > 166 && x < 202) && (y > 8 && y < 44) && b==1){
            selectedAction = CIRCLE;
        }

        //Click Filled Circle
        if((x > 166 && x < 198) && (y > 55 && y < 87) && b==1){
            selectedAction = FILLEDCIRCLE;
        }

        //Click Polygon
        if((x > 209 && x < 245) && (y > 9 && y < 45) && b==1){
            selectedAction = POLYGON;
        }

        //Click Filled Polygon
        if((x > 208 && x < 244) && (y > 50 && y < 86) && b==1){
            selectedAction = FILLEDPOLYGON;
        }

        //Click Eraser
        if((x > 254 && x < 286) && (y > 11 && y < 41) && b==1){
            selectedAction = ERASER;
        }

        //Click Bucket
        if((x > 251 && x < 284) && (y > 53 && y < 85) && b==1){
            selectedAction = BUCKET;
        }

        //Click Eraser
        if((x > 254 && x < 286) && (y > 11 && y < 41) && b==1){
            selectedAction = ERASER;
        }

        //Click Bucket
        if((x > 251 && x < 284) && (y > 53 && y < 85) && b==1){
            selectedAction = BUCKET;
        }

        //Click Text
        if((x > 254 && x < 286) && (y > 11 && y < 41) && b==1){
            selectedAction = TEXT;
        }

        //Click EyeDropper
        if((x > 251 && x < 284) && (y > 53 && y < 85) && b==1){
            selectedAction = EYEDROPPER;
        }

        //Click Copy
        if((x > 336 && x < 368) && (y > 11 && y < 43) && b==1){
            selectedAction = COPY;
        }

        //Click Cut
        if((x > 338 && x < 366) && (y > 55 && y < 87) && b==1){
            selectedAction = CUT;
        }

        //Click Paste
        if((x > 377 && x < 403) && (y > 12 && y < 44) && b==1){
            selectedAction = PASTE;
        }

        //Click Undo
        if((x > 338 && x < 406) && (y > 55 && y < 87) && b==1){
            selectedAction = UNDO;
        }

        //Click Pattern 1
        if((x > 701 && x < 745) && (y > 52 && y < 96) && b==1){
            selectedAction = PATTERN1;
        }

        //Click Pattern 2
        if((x > 753 && x < 797) && (y > 52 && y < 96) && b==1){
            selectedAction = PATTERN2;
        }

        //Click en Palette
        if((x > startXPalette && x < endXPalette) && (y > startYPalette && y < endYPalette) && b==1){
            selectedColor = getSelectedColor(x, y);
        }

        //Click en canvas
    	if((x > 0 && x < 800) && (y > 100 && y < 600) && b==1){
            switch(selectedAction){
                case PENCIL:
                    hideMouse(x, y);
                    tempx = x;
                    tempy = y;
                    while(b==1 && (x > 0 && x < 800) && (y > 100 && y < 600)){
                        drawLine(x, y, tempx, tempy, selectedColor, 1);
                        tempx=x; tempy = y;
                        getMouse(&x,&y,&b);
                    }
                    showMouse(x, y);
                    tempx=x; 
                    tempy=y;
                break;

                case LINE:
                    x1 = x;
                    y1 = y;
                    getMouse(&x,&y,&b);
                    while(b==1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    if((x > 0 && x < 800) && (y > 100 && y < 600))
                        drawLine(x1, y1, x, y, selectedColor, 1);
                    showMouse(x, y);
                break;

                case RECTANGLE:
                    x1=x;
                    y1=y;
                    while(b==1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    if((x > 0 && x < 800) && (y > 100 && y < 600))
                        drawRectangle(x1, y1 ,x, y, selectedColor, 1);
                    showMouse(x, y);
                break;

                case FILLEDRECTANGLE:
                    x1=x;
                        y1=y;
                        while(b==1){
                            refreshMouse(&x, &y, &b, &tempx, &tempy);
                        }
                        hideMouse(x, y);
                        if((x > 0 && x < 800) && (y > 100 && y < 600))
                            drawFilledRectangle(x1, y1 ,x, y, selectedColor, 1);
                        showMouse(x, y);
                break;
            }
            
        }

    } while (!((x > 776 && x < 800) && (y > 0 && y < 24) && b == 1));

    unSetVideoSVGA();
}