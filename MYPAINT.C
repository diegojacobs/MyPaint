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
#define PENCIL                   1
#define LINE                     2
#define RECTANGLE                3
#define FILLEDRECTANGLE          4

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

    toolBar();

    do {
        refreshMouse(&x, &y, &b, &tempx, &tempy);
        
        //Click Pencil
        if((x > 90 && x < 130) && (y > 15 && y < 55) && b==1){
            selectedAction = PENCIL;
        }

        //Click Rectangle
        if((x > 90 && x < 130) && (y > 55 && y < 95) && b==1){
            selectedAction = RECTANGLE;
        }

        //Click Line
        if((x > 130 && x < 170) && (y > 15 && y < 55) && b==1){
            selectedAction = LINE;
        }


        //Click Filled Rectangle
        if((x > 130 && x < 170) && (y > 55 && y < 95) && b==1){
            selectedAction = FILLEDRECTANGLE;
        }

        //Click en Palette
        if((x > startXPalette && x < endXPalette) && (y > startYPalette && y < endYPalette) && b==1){
            selectedColor = getSelectedColor(x, y);
        }

        //Click en canvas
    	if((x > 0 && x < 800) && (y > 75 && y < 600) && b==1){
            switch(selectedAction){
                case PENCIL:
                    hideMouse(x, y);
                    tempx = x;
                    tempy = y;
                    while(b==1 && (x > 0 && x < 800) && (y > 75 && y < 600)){
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
                    if((x > 0 && x < 800) && (y > 75 && y < 600))
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
                    if((x > 0 && x < 800) && (y > 75 && y < 600))
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
                        if((x > 0 && x < 800) && (y > 75 && y < 600))
                            drawFilledRectangle(x1, y1 ,x, y, selectedColor, 1);
                        showMouse(x, y);
                break;
            }
            
        }

    } while (!((x > 780 && x < 800) && (y > 0 && y < 20) && b == 1));

    unSetVideoSVGA();
}