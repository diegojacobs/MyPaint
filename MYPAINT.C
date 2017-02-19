#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>
#include <time.h>
#include "asm.h"
#include "mouse.h"
#include "image.h"
#include "clip.h"
#include "undo.h"
#include "text.h"
#include "graph.h"
#include "bar.h"

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

void main ()
{
    int selectedAction = PENCIL;
    int x, y, b, tempx, tempy, cont;
    int i, j;
    int x1, y1;
    int rx, ry, xc, yc;
    char selectedColor1, selectedColor2;
    int thickness = 1;
    int a[20][2];
    
    FILE *fontFile;
    unsigned char font[58][16*16];
    unsigned char backspace[16][16];

    if(!setVideoMode(v800x600x256, 800, 600)){
      printf("\r\nError couldn't initialize SVGA.\r\n");
      return;
    }

    if((fontFile = fopen ("MyPaint/Font/font.fnt","rb"))==NULL){
        printf("\r\nError.-Font not found.\r\n");
        return;
    }
    for(x=0; x<58; x++){
        fread(&font[x], 1, 16*16, fontFile);
    }
    fclose(fontFile);
    setDimensions(16,16);

    //Activa el mouse
    setMouse();
    setBoundariesMouse(790, 590);
    getMouse(&x, &y, &b);

    canvas();
    toolBar();
    showSelectedAction(PENCIL, 0);
    showSelectedThickness(SMALL, 0);

    selectedColor1 = getPixel(25, 200);
    selectedColor2 = getPixel(75, 200);

    b = 0;
    do {
        refreshMouse(&x, &y, &b, &tempx, &tempy);

        //Click New
        if((x > 10 && x < 34) && (y > 8 && y < 41) && b==1){
            hideMouse(x, y);
            canvas();
            toolBar();
            showMouse(x, y);
        }

        //Click Save
        if((x > 10 && x < 42) && (y > 56 && y < 88) && b==1){
            hideMouse(x, y);
            showMouse(x, y);
        }

        //Click Open
        if((x > 42 && x < 75) && (y > 12 && y < 88) && b==1){
            hideMouse(x, y);
            showMouse(x, y);
        }

        //Click Small Thickness
        if((x > 123 && x < 165) && (y > 24 && y < 33) && b==1){
            hideMouse(x, y);
            showSelectedThickness(SMALL, thickness);
            thickness = SMALL;
            showMouse(x, y);
        }

        //Click Medium Thickness
        if((x > 123 && x < 165) && (y > 38 && y < 49) && b==1){
            hideMouse(x, y);
            showSelectedThickness(MEDIUM, thickness);
            thickness = MEDIUM;
            showMouse(x, y);
        }

        //Click Big Thickness
        if((x > 123 && x < 165) && (y > 54 && y < 65) && b==1){
            hideMouse(x, y);
            showSelectedThickness(BIG, thickness);
            thickness = BIG;
            showMouse(x, y);
        }

        //Click Pencil
        if((x > 193 && x < 227) && (y > 7 && y < 44) && b==1){
            hideMouse(x, y);
            showSelectedAction(PENCIL, selectedAction);
            selectedAction = PENCIL;
            showMouse(x, y);
        }

        //Click Line
        if((x > 195 && x < 222) && (y > 54 && y < 88) && b==1){
            hideMouse(x, y);
            showSelectedAction(LINE, selectedAction);
            selectedAction = LINE;
            showMouse(x, y);
        }

        //Click Rectangle
        if((x > 241 && x < 273) && (y > 10 && y < 42) && b==1){
            hideMouse(x, y);
            showSelectedAction(RECTANGLE, selectedAction);
            selectedAction = RECTANGLE;
            showMouse(x, y);
        }

        //Click Filled Rectangle
        if((x > 240 && x < 272) && (y > 56 && y < 88) && b==1){
            hideMouse(x, y);
            showSelectedAction(FILLEDRECTANGLE, selectedAction);
            selectedAction = FILLEDRECTANGLE;
            showMouse(x, y);
        }

        //Click Circle
        if((x > 290 && x < 328) && (y > 8 && y < 46) && b==1){
            hideMouse(x, y);
            showSelectedAction(CIRCLE, selectedAction);
            selectedAction = CIRCLE;
            showMouse(x, y);
        }

        //Click Filled Circle
        if((x > 290 && x < 325) && (y > 56 && y < 88) && b==1){
            hideMouse(x, y);
            showSelectedAction(FILLEDCIRCLE, selectedAction);
            selectedAction = FILLEDCIRCLE;
            showMouse(x, y);
        }

        //Click Polygon
        if((x > 338 && x < 377) && (y > 8 && y < 47) && b==1){
            hideMouse(x, y);
            showSelectedAction(POLYGON, selectedAction);
            selectedAction = POLYGON;
            showMouse(x, y);
        }

        //Click Filled Polygon
        if((x > 336 && x < 377) && (y > 49 && y < 88) && b==1){
            hideMouse(x, y);
            showSelectedAction(FILLEDPOLYGON, selectedAction);
            selectedAction = FILLEDPOLYGON;
            showMouse(x, y);
        }

        //Click Eraser
        if((x > 425 && x < 462) && (y > 10 && y < 46) && b==1){
            hideMouse(x, y);
            showSelectedAction(ERASER, selectedAction);
            selectedAction = ERASER;
            showMouse(x, y);
        }

        //Click Bucket
        if((x > 424 && x < 462) && (y > 53 && y < 90) && b==1){
            hideMouse(x, y);
            showSelectedAction(BUCKET, selectedAction);
            selectedAction = BUCKET;
            showMouse(x, y);
        }

        //Click Spray
        if((x > 392 && x < 413) && (y > 8 && y < 44) && b==1){
            hideMouse(x, y);
            showSelectedAction(SPRAY, selectedAction);
            selectedAction = SPRAY;
            showMouse(x, y);
        }

        //Click EyeDropper
        if((x > 384 && x < 422) && (y > 55 && y < 92) && b==1){
            hideMouse(x, y);
            showSelectedAction(EYEDROPPER, selectedAction);
            selectedAction = EYEDROPPER;
            showMouse(x, y);
        }

        //Click Text
        if((x > 467 && x < 502) && (y > 8 && y < 45) && b==1){
            hideMouse(x, y);
            showSelectedAction(TEXT, selectedAction);
            selectedAction = TEXT;
            showMouse(x, y);
        }

        //Click Copy
        if((x > 575 && x < 611) && (y > 8 && y < 43) && b==1){
            hideMouse(x, y);
            showSelectedAction(COPY, selectedAction);
            selectedAction = COPY;
            showMouse(x, y);
        }

        //Click Cut
        if((x > 578 && x < 608) && (y > 54 && y < 89) && b==1){
            hideMouse(x, y);
            showSelectedAction(CUT, selectedAction);
            selectedAction = CUT;
            showMouse(x, y);
        }

        //Click Paste
        if((x > 616 && x < 647) && (y > 9 && y < 46) && b==1){
            hideMouse(x, y);
            showSelectedAction(PASTE, selectedAction);
            selectedAction = PASTE;
            showMouse(x, y);
        }

        //Click Undo
        if((x > 613 && x < 651) && (y > 55 && y < 86) && b==1){
            hideMouse(x, y);
            undo();
            showMouse(x, y);
        }

        //Click Pattern 1
        if((x > 701 && x < 745) && (y > 52 && y < 96) && b==1){
            hideMouse(x, y);
            selectedAction = PATTERN1;
            showMouse(x, y);
        }

        //Click Pattern 2
        if((x > 753 && x < 797) && (y > 52 && y < 96) && b==1){
            hideMouse(x, y);
            selectedAction = PATTERN2;
            showMouse(x, y);
        }

        //Left Click in Palette
        if(((x > 23 && x < 41) || (x > 57 && x < 75)) && b==1){
            hideMouse(x, y);
            selectedColor1 = getSelectedColor1(x - 1, y - 1);
            showMouse(x, y);
        }
        
        //Right Click in Palette
        if(((x > 23 && x < 41) || (x > 57 && x < 75)) && b==2){
            hideMouse(x, y);
            selectedColor2 = getSelectedColor2(x - 1, y - 1);
            showMouse(x, y);
        }

        //Left click in canvas
    	if((x > 100 && x < 800) && (y > 100 && y < 600) && b==1){
            switch(selectedAction){
                case PENCIL:
                    hideMouse(x, y);
                    tempx = x;
                    tempy = y;
                    saveUndo();
                    while(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                        drawLine(x, y, tempx, tempy, selectedColor1, thickness);
                        tempx = x; 
                        tempy = y;
                        getMouse(&x, &y, &b);
                    }
                    showMouse(x, y);
                    tempx = x; 
                    tempy = y;
                break;

                case LINE:
                    x1 = x;
                    y1 = y;
                    getMouse(&x, &y, &b);
                    while(b == 1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    saveUndo();
                    if((x > 100 && x < 800) && (y > 100 && y < 600))
                        drawLine(x1, y1, x, y, selectedColor1, thickness);
                    showMouse(x, y);
                break;

                case RECTANGLE:
                    x1 = x;
                    y1 = y;
                    while(b == 1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    saveUndo();
                    if((x > 100 && x < 800) && (y > 100 && y < 600))
                        drawRectangle(x1, y1 ,x, y, selectedColor1, thickness);
                    showMouse(x, y);
                break;

                case FILLEDRECTANGLE:
                    x1 = x;
                    y1 = y;
                    while(b==1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    saveUndo();
                    if((x > 100 && x < 800) && (y > 100 && y < 600))
                        drawFilledRectangle(x1, y1 ,x, y, selectedColor1, selectedColor2, thickness);
                    showMouse(x, y);
                break;

                case ERASER:
                    hideMouse(x, y);
                    tempx = x;
                    tempy = y;
                    saveUndo();
                    while(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                        drawLine(x, y, tempx, tempy, selectedColor2, thickness);
                        tempx = x; 
                        tempy = y;
                        getMouse(&x,&y,&b);
                    }
                    showMouse(x, y);
                    tempx = x; 
                    tempy = y;
                break;

                case BUCKET:
                    hideMouse(x, y);
                    saveUndo();
                    bucketFill(x, y, selectedColor1, 0);
                    showMouse(x, y);
                break;

                case SPRAY:
                    hideMouse(x, y);
                    tempx = x;
                    tempy = y;
                    saveUndo();
                    while(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                        spray(x, y, selectedColor1);
                        tempx = x; 
                        tempy = y;
                        getMouse(&x, &y, &b);
                    }
                    showMouse(x, y);
                    tempx = x; 
                    tempy = y;
                break;

                case EYEDROPPER:
                    if(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                        selectedColor1 = getPixel(x - 1, y - 1);
                        drawFilledRectangle(5, 181, 44, 220, selectedColor1, selectedColor1, 1);
                    }
                break;

                case POLYGON:
                    x1 = x; 
                    y1 = y;
                    i = x; 
                    j = y;

                    hideMouse(x, y);
                    saveUndo();
                    showMouse(x, y);

                    cont = 0;
                    while(b!=2){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                        while(b!=1 && b!=2){
                            refreshMouse(&x, &y, &b, &tempx, &tempy);
                        }
                        if(b==1){
                            if(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                                hideMouse(x, y);
                                delay(300);
                                drawLine(x1, y1, x, y, selectedColor1, thickness);
                                showMouse(x, y);
                                cont++;
                            }
                        }else{
                            if(b==2 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                                hideMouse(x, y);
                                delay(300);
                                drawLine(i, j, x1, y1, selectedColor1, thickness);
                                showMouse(x, y);
                                cont++;
                            }
                        }
                        x1 = x;
                        y1 = y;
                        
                    }
                break;

                case FILLEDPOLYGON:
                    x1 = x; 
                    y1 = y;
                    i = x; 
                    j = y;

                    hideMouse(x, y);
                    saveUndo();
                    showMouse(x, y);

                    a[0][0] = i; 
                    a[0][1] = j;

                    cont = 1;
                    while(b!=2){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                        while(b!=1 && b!=2){
                            refreshMouse(&x, &y, &b, &tempx, &tempy);
                        }
                        if(b==1){
                            if(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                                hideMouse(x, y);
                                a[cont][0] = x; 
                                a[cont][1] = y;
                                delay(300);
                                drawLine(x1, y1, x, y, selectedColor1, thickness);
                                showMouse(x, y);
                                cont++;
                            }
                        }else{
                            if(b==2 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                                hideMouse(x, y);
                                a[cont][0] = i; 
                                a[cont][1] = j;
                                delay(300);
                                drawLine(i, j, x1, y1, selectedColor1, thickness);
                                showMouse(x, y);
                                cont++;
                            }
                        }
                        x1 = x;
                        y1 = y;
                        
                    }
                    scanline(a, cont, selectedColor1, selectedColor2, thickness);
                break;

                case TEXT:
                    hideMouse(x,y);
                    saveUndo();
                    printText(x, y, selectedColor1, font);
                    showMouse(x, y);
                    tempx=x; tempy=y;
                break;

                case CIRCLE:
                    x1 = x;
                    y1 = y;
                    while(b == 1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    saveUndo();
                    rx = abs(x - x1) / 2;
                    ry = abs(y - y1) / 2;
                    if((x > 100 && x < 800) && (y > 100 && y < 600))
                        ellipse(x1, y1 ,x, y, selectedColor1, thickness);
                    showMouse(x, y);
                break;

                case FILLEDCIRCLE:
                    x1 = x;
                    y1 = y;
                    while(b==1){
                        refreshMouse(&x, &y, &b, &tempx, &tempy);
                    }
                    hideMouse(x, y);
                    saveUndo();
                    rx = abs(x - x1) / 2;
                    ry = abs(y - y1) / 2;
                    xc = MIN(x1, x) + rx;
                    yc = MIN(y1, y) + ry;
                    if((x > 100 && x < 800) && (y > 100 && y < 600))
                        filledElipse(xc, yc, rx, ry, selectedColor1, selectedColor2, thickness);
                    showMouse(x, y);
                break;
            }
            
        }

        //Left click in canvas
        if((x > 100 && x < 800) && (y > 100 && y < 600) && b==2){
            switch(selectedAction){
                case BUCKET:
                    hideMouse(x, y);
                    saveUndo();
                    bucketFill(x, y, selectedColor2, 0);
                    showMouse(x, y);
                break;

                case EYEDROPPER:
                    if(b==1 && (x > 100 && x < 800) && (y > 100 && y < 600)){
                        selectedColor2 = getPixel(x - 1, y - 1);
                        drawFilledRectangle(57, 181, 96, 220, selectedColor2, selectedColor2, 1);
                    }
                break;
            }
        }

    } while (!((x > 776 && x < 800) && (y > 0 && y < 24) && b == 1));

    unsetVideoMode();
}