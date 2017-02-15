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
#define SPRAY                   22
void main ()
{
    int selectedAction = PENCIL;
    int x, y, b, tempx, tempy;
    int i, j;
    int x1, y1;
    char selectedColor1 = getPixel(6, 182);
    char selectedColor2 = getPixel(48, 182);
    int grossor = 1;

    if( !setVideoMode(v800x600x256, 800, 600)){
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

        //Click Grossor 1
        if((x > 123 && x < 165) && (y > 24 && y < 33) && b==1){
            grossor = 1;
        }

        //Click Grossor 2
        if((x > 123 && x < 165) && (y > 38 && y < 49) && b==1){
            grossor = 2;
        }

        //Click Grossor 3
        if((x > 123 && x < 165) && (y > 54 && y < 65) && b==1){
            grossor = 3;
        }

        //Click Pencil
        if((x > 193 && x < 227) && (y > 7 && y < 44) && b==1){
            selectedAction = PENCIL;
            drawRectangle(191, 5, 229, 46, 0, 1);
        }

        //Click Line
        if((x > 195 && x < 222) && (y > 54 && y < 88) && b==1){
            selectedAction = LINE;
            drawRectangle(193, 52, 224, 90, 0, 1);
        }

        //Click Rectangle
        if((x > 241 && x < 273) && (y > 10 && y < 42) && b==1){
            selectedAction = RECTANGLE;
            drawRectangle(239, 8, 275, 44, 0, 1);
        }

        //Click Filled Rectangle
        if((x > 240 && x < 272) && (y > 56 && y < 88) && b==1){
            selectedAction = FILLEDRECTANGLE;
            drawRectangle(238, 54, 274, 90, 0, 1);
        }

        //Click Circle
        if((x > 290 && x < 328) && (y > 8 && y < 46) && b==1){
            selectedAction = CIRCLE;
        }

        //Click Filled Circle
        if((x > 290 && x < 325) && (y > 56 && y < 88) && b==1){
            selectedAction = FILLEDCIRCLE;
        }

        //Click Polygon
        if((x > 338 && x < 377) && (y > 8 && y < 47) && b==1){
            selectedAction = POLYGON;
        }

        //Click Filled Polygon
        if((x > 336 && x < 377) && (y > 49 && y < 88) && b==1){
            selectedAction = FILLEDPOLYGON;
        }

        //Click Eraser
        if((x > 425 && x < 462) && (y > 10 && y < 46) && b==1){
            selectedAction = ERASER;
            drawRectangle(423, 8, 464, 48, 0, 1);
        }

        //Click Bucket
        if((x > 424 && x < 462) && (y > 53 && y < 90) && b==1){
            selectedAction = BUCKET;
        }

        //Click Spray
        if((x > 392 && x < 413) && (y > 8 && y < 44) && b==1){
            selectedAction = SPRAY;
            drawRectangle(390, 6, 411, 46, 0, 1);
        }

        //Click Text
        if((x > 467 && x < 502) && (y > 8 && y < 45) && b==1){
            selectedAction = TEXT;
        }

        //Click EyeDropper
        if((x > 384 && x < 422) && (y > 55 && y < 92) && b==1){
            selectedAction = EYEDROPPER;
            drawRectangle(382, 53, 424, 94, 0, 1);
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
        if((x > 23 && x < 41) && b==1){
            if(y > 238 && y < 256)
                selectedColor1 = getPixel(23, y);
            if(y > 271 && y < 289)
                selectedColor1 = getPixel(23, y);
            if(y > 304 && y < 322)
                selectedColor1 = getPixel(23, y);
            if(y > 338 && y < 356)
                selectedColor1 = getPixel(23, y);
            if(y > 371 && y < 389)
                selectedColor1 = getPixel(23, y);
            if(y > 404 && y < 422)
                selectedColor1 = getPixel(23, y);
            if(y > 437 && y < 455)
                selectedColor1 = getPixel(23, y);
            if(y > 470 && y < 488)
                selectedColor1 = getPixel(23, y);
            if(y > 503 && y < 521)
                selectedColor1 = getPixel(23, y);
            if(y > 538 && y < 556)
                selectedColor1 = getPixel(23, y);
            if(y > 571 && y < 589)
                selectedColor1 = getPixel(23, y);  

            //Fill color 1 rectangle
            drawFilledRectangle(5, 181, 44, 220, selectedColor1, selectedColor1, 1);
        }

        if((x > 57 && x < 75) && b==1){
            if(y > 238 && y < 256)
                selectedColor1 = getPixel(57, y);
            if(y > 271 && y < 289)
                selectedColor1 = getPixel(57, y);
            if(y > 304 && y < 322)
                selectedColor1 = getPixel(57, y);
            if(y > 338 && y < 356)
                selectedColor1 = getPixel(57, y);
            if(y > 371 && y < 389)
                selectedColor1 = getPixel(57, y);
            if(y > 404 && y < 422)
                selectedColor1 = getPixel(57, y);
            if(y > 437 && y < 455)
                selectedColor1 = getPixel(57, y);
            if(y > 470 && y < 488)
                selectedColor1 = getPixel(57, y);
            if(y > 503 && y < 521)
                selectedColor1 = getPixel(57, y);
            if(y > 538 && y < 556)
                selectedColor1 = getPixel(57, y);
            if(y > 571 && y < 589)
                selectedColor1 = getPixel(57, y);  

            //Fill color 1 rectangle
            drawFilledRectangle(5, 181, 44, 220, selectedColor1, selectedColor1, 1);
        }
        
        if((x > 23 && x < 41) && b==2){
            if(y > 238 && y < 256)
                selectedColor2 = getPixel(23, y);
            if(y > 271 && y < 289)
                selectedColor2 = getPixel(23, y);
            if(y > 304 && y < 322)
                selectedColor2 = getPixel(23, y);
            if(y > 338 && y < 356)
                selectedColor2 = getPixel(23, y);
            if(y > 371 && y < 389)
                selectedColor2 = getPixel(23, y);
            if(y > 404 && y < 422)
                selectedColor2 = getPixel(23, y);
            if(y > 437 && y < 455)
                selectedColor2 = getPixel(23, y);
            if(y > 470 && y < 488)
                selectedColor2 = getPixel(23, y);
            if(y > 503 && y < 521)
                selectedColor2 = getPixel(23, y);
            if(y > 538 && y < 556)
                selectedColor2 = getPixel(23, y);
            if(y > 571 && y < 589)
                selectedColor2 = getPixel(23, y);  

            //Fill color 2 rectangle
            drawFilledRectangle(5, 181, 44, 220, selectedColor2, selectedColor2, 1);
        }

        if((x > 57 && x < 75) && b==2){
            if(y > 238 && y < 256)
                selectedColor2 = getPixel(57, y);
            if(y > 271 && y < 289)
                selectedColor2 = getPixel(57, y);
            if(y > 304 && y < 322)
                selectedColor2 = getPixel(57, y);
            if(y > 338 && y < 356)
                selectedColor2 = getPixel(57, y);
            if(y > 371 && y < 389)
                selectedColor2 = getPixel(57, y);
            if(y > 404 && y < 422)
                selectedColor2 = getPixel(57, y);
            if(y > 437 && y < 455)
                selectedColor2 = getPixel(57, y);
            if(y > 470 && y < 488)
                selectedColor2 = getPixel(57, y);
            if(y > 503 && y < 521)
                selectedColor2 = getPixel(57, y);
            if(y > 538 && y < 556)
                selectedColor2 = getPixel(57, y);
            if(y > 571 && y < 589)
                selectedColor2 = getPixel(57, y);  

            //Fill color 2 rectangle
            drawFilledRectangle(57, 181, 96, 220, selectedColor2, selectedColor2, 1);
        }

        //Click en canvas
    	if((x > 100 && x < 800) && (y > 100 && y < 600) && b==1){
            switch(selectedAction){
                case PENCIL:
                    hideMouse(x, y);
                    tempx = x;
                    tempy = y;
                    while(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                        drawLine(x, y, tempx, tempy, selectedColor1, grossor);
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
                    if((x > 100 && x < 800) && (y > 100 && y < 600))
                        drawLine(x1, y1, x, y, selectedColor1, grossor);
                    showMouse(x, y);
                break;

                case RECTANGLE:
                    x1=x;
                    y1=y;
                    while(b==1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    if((x > 100 && x < 800) && (y > 100 && y < 600))
                        drawRectangle(x1, y1 ,x, y, selectedColor1, grossor);
                    showMouse(x, y);
                break;

                case FILLEDRECTANGLE:
                    x1=x;
                        y1=y;
                        while(b==1){
                            refreshMouse(&x, &y, &b, &tempx, &tempy);
                        }
                        hideMouse(x, y);
                        if((x > 100 && x < 800) && (y > 100 && y < 600))
                            drawFilledRectangle(x1, y1 ,x, y, selectedColor1, selectedColor2, 1);
                        showMouse(x, y);
                break;

                case ERASER:
                    hideMouse(x, y);
                    tempx = x;
                    tempy = y;
                    while(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                        drawLine(x, y, tempx, tempy, selectedColor2, grossor);
                        tempx=x; tempy = y;
                        getMouse(&x,&y,&b);
                    }
                    showMouse(x, y);
                    tempx=x; 
                    tempy=y;
                break;

                case SPRAY:
                    spray(x, y, selectedColor1);
                break;
            }
            
        }

    } while (!((x > 776 && x < 800) && (y > 0 && y < 24) && b == 1));

    unsetVideoMode();
}