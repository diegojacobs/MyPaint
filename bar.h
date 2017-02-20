#define SMALL                    1
#define MEDIUM                   2
#define BIG                      3

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
#define SPRAY                   22

// 0 = COLOR, 1 = Pattern1, 2 = Pattern2
#define COLOR                   0
#define PATTERN1                1
#define PATTERN2                2

void closeButton();
void toolBar();
void canvas();
char getSelectedColor1(int x, int y);
char getSelectedColor2(int x, int y);
void showSelectedThickness(int new, int old);


void toolBar(){
    BITMAP bmp;
    loadImage(0, 0, "MyPaint/Images/toolbar.bmp", &bmp);
}

void topToolBar(){
    BITMAP bmp;
    loadImage(0, 0, "MyPaint/Images/topbar.bmp", &bmp);
}

void leftToolBar(){
    BITMAP bmp;
    loadImage(0, 0, "MyPaint/Images/leftbar.bmp", &bmp);
}

void canvas(){
    BITMAP bmp;
    loadImage(100, 100, "MyPaint/Images/canvas.bmp", &bmp);
}

char getSelectedColor1(int x, int y){
    char color;
    if(y > 238 && y < 256)
        color = getPixel(x, y);
    if(y > 271 && y < 289)
        color = getPixel(x, y);
    if(y > 304 && y < 322)
        color = getPixel(x, y);
    if(y > 338 && y < 356)
        color = getPixel(x, y);
    if(y > 371 && y < 389)
        color = getPixel(x, y);
    if(y > 404 && y < 422)
        color = getPixel(x, y);
    if(y > 437 && y < 455)
        color = getPixel(x, y);
    if(y > 470 && y < 488)
        color = getPixel(x, y);
    if(y > 503 && y < 521)
        color = getPixel(x, y);
    if(y > 538 && y < 556)
        color = getPixel(x, y);
    if(y > 571 && y < 589)
        color = getPixel(x, y);  

    //Fill color 1 rectangle
    drawFilledRectangle(5, 181, 44, 220, color, color, SMALL, COLOR, COLOR);

    return color;
}

char getSelectedColor2(int x, int y){
    char color;

    if(y > 238 && y < 256)
        color = getPixel(x, y);
    if(y > 271 && y < 289)
        color = getPixel(x, y);
    if(y > 304 && y < 322)
        color = getPixel(x, y);
    if(y > 338 && y < 356)
        color = getPixel(x, y);
    if(y > 371 && y < 389)
        color = getPixel(x, y);
    if(y > 404 && y < 422)
        color = getPixel(x, y);
    if(y > 437 && y < 455)
        color = getPixel(x, y);
    if(y > 470 && y < 488)
        color = getPixel(x, y);
    if(y > 503 && y < 521)
        color = getPixel(x, y);
    if(y > 538 && y < 556)
        color = getPixel(x, y);
    if(y > 571 && y < 589)
        color = getPixel(x, y);  

    //Fill color 2 rectangle
    drawFilledRectangle(57, 181, 96, 220, color, color, SMALL, COLOR, COLOR);

    return color;
}

char getBarColor(){
    return getPixel(790, 50);
}

void closeButton(){
    int i, j;

    for(i=780;i<800;i++){
        for(j=0;j<20;j++){
            putPixel(i, j, 12);
        }
    }
}

void showSelectedThickness(int new, int old){
    if (new == old){
        return;
    }

    if (new == SMALL)
    {
        drawRectangle(120, 25, 167, 31, 0, MEDIUM, COLOR);
    }
    
    if (old == SMALL)
    {
        drawRectangle(120, 25, 167, 31, getBarColor(), MEDIUM, COLOR);
    }

    if (new == MEDIUM)
    {
        drawRectangle(120, 39, 167, 48, 0, MEDIUM, COLOR);
    }
    
    if (old == MEDIUM)
    {
        drawRectangle(120, 39, 167, 48, getBarColor(), MEDIUM, COLOR);
    }

    if (new == BIG)
    {
        drawRectangle(120, 54, 167, 64, 0, MEDIUM, COLOR);
    }
    
    if (old == BIG)
    {
        drawRectangle(120, 54, 167, 64, getBarColor(), MEDIUM, COLOR);
    }
}

void showSelectedAction(int new, int old){
    if (new == old){
        return;
    }

    if (new == PENCIL)
    {
        drawRectangle(191, 5, 229, 46, 0, MEDIUM, COLOR);
    }
    
    if (old == PENCIL)
    {
        drawRectangle(191, 5, 229, 46, getBarColor(), MEDIUM, COLOR);
    }

    if (new == LINE)
    {
        drawRectangle(191, 52, 229, 90, 0, MEDIUM, COLOR);
    }
    
    if (old == LINE)
    {
        drawRectangle(191, 52, 229, 90, getBarColor(), MEDIUM, COLOR);
    }

    if (new == RECTANGLE)
    {
        drawRectangle(236, 8, 275, 44, 0, MEDIUM, COLOR);
    }
    
    if (old == RECTANGLE)
    {
        drawRectangle(236, 8, 275, 44, getBarColor(), MEDIUM, COLOR);
    }

    if (new == FILLEDRECTANGLE)
    {
        drawRectangle(236, 54, 275, 90, 0, MEDIUM, COLOR);
    }
    
    if (old == FILLEDRECTANGLE)
    {
        drawRectangle(236, 54, 275, 90, getBarColor(), MEDIUM, COLOR);
    }

    if (new == CIRCLE)
    {
        drawRectangle(287, 6, 330, 48, 0, MEDIUM, COLOR);
    }
    
    if (old == CIRCLE)
    {
        drawRectangle(287, 6, 330, 48, getBarColor(), MEDIUM, COLOR);
    }

    if (new == FILLEDCIRCLE)
    {
        drawRectangle(287, 54, 330, 90, 0, MEDIUM, COLOR);
    }
    
    if (old == FILLEDCIRCLE)
    {
        drawRectangle(287, 54, 330, 90, getBarColor(), MEDIUM, COLOR);
    }

    if (new == POLYGON)
    {
        drawRectangle(334, 6, 379, 49, 0, MEDIUM, COLOR);
    }
    
    if (old == POLYGON)
    {
        drawRectangle(334, 6, 379, 49, getBarColor(), MEDIUM, COLOR);
    }

    if (new == FILLEDPOLYGON)
    {
        drawRectangle(334, 47, 379, 90, 0, MEDIUM, COLOR);
    }
    
    if (old == FILLEDPOLYGON)
    {
        drawRectangle(334, 47, 379, 90, getBarColor(), MEDIUM, COLOR);
    }

    if (new == ERASER)
    {
        drawRectangle(423, 8, 464, 48, 0, MEDIUM, COLOR);
    }
    
    if (old == ERASER)
    {
        drawRectangle(423, 8, 464, 48, getBarColor(), MEDIUM, COLOR);
    }

    if (new == BUCKET)
    {
        drawRectangle(423, 51, 464, 92, 0, MEDIUM, COLOR);
    }
    
    if (old == BUCKET)
    {
        drawRectangle(423, 51, 464, 92, getBarColor(), MEDIUM, COLOR);
    }

    if (new == SPRAY)
    {
        drawRectangle(382, 6, 424, 46, 0, MEDIUM, COLOR);
    }
    
    if (old == SPRAY)
    {
        drawRectangle(382, 6, 424, 46, getBarColor(), MEDIUM, COLOR);
    }

    if (new == EYEDROPPER)
    {
        drawRectangle(382, 53, 424, 94, 0, MEDIUM, COLOR);
    }
    
    if (old == EYEDROPPER)
    {
        drawRectangle(382, 53, 424, 94, getBarColor(), MEDIUM, COLOR);
    }

    if (new == TEXT)
    {
        drawRectangle(465, 10, 502, 52, 0, MEDIUM, COLOR);
    }
    
    if (old == TEXT)
    {
        drawRectangle(465, 10, 502, 52, getBarColor(), MEDIUM, COLOR);
    }

    if (new == COPY)
    {
        drawRectangle(573, 6, 613, 45, 0, MEDIUM, COLOR);
    }
    
    if (old == COPY)
    {
        drawRectangle(573, 6, 613, 45, getBarColor(), MEDIUM, COLOR);
    }

    if (new == CUT)
    {
        drawRectangle(573, 52, 613, 91, 0, MEDIUM, COLOR);
    }
    
    if (old == CUT)
    {
        drawRectangle(573, 52, 613, 91, getBarColor(), MEDIUM, COLOR);
    }

    if (new == PASTE)
    {
        drawRectangle(614, 7, 649, 48, 0, MEDIUM, COLOR);
    }
    
    if (old == PASTE)
    {
        drawRectangle(614, 7, 649, 48, getBarColor(), MEDIUM, COLOR);
    }
}