#define startXPalette            450
#define startYPalette            26
#define endXPalette              762
#define endYPalette              63
#define columns                  26
#define size                     12

void showPalette();
void closeButton();
void toolBar();
char getSelectedColor(int x, int y);
void canvas();

void toolBar(){
    BITMAP bmp;
    loadImage(0, 0, "MyPaint/Images/toolbar.bmp", &bmp);
}
void showPalette(){
    int i, j, k, l, color;
    int startX = startXPalette;
    int startY = startYPalette;
    color = 152;

    for(i = startX; color < 256; i = i + size, color++){
        if(color % columns == 0)
            i = startX;
        
        j = startY + ((color - 152) / columns) * size;

        for(k = 0;k < size; j++, k++)
            for (l = 0; l < size; l++)
                putPixel(i + l, j, color); 
    }
}

void canvas(){
    BITMAP bmp;
    loadImage(0, 100, "MyPaint/Images/canvas.bmp", &bmp);
}

char getSelectedColor(int x, int y){
    return ((x - startXPalette) / size) + columns * ((y - startYPalette) / size) + 152;
}

void closeButton(){
    int i, j;

    for(i=780;i<800;i++){
        for(j=0;j<20;j++){
            putPixel(i, j, 12);
        }
    }
}