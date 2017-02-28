typedef unsigned char  byte;
typedef unsigned short word;

typedef struct tagBITMAP{
    word width;
    word height;
    char palette[256*3];
    byte *data;
}BITMAP;

void fskip(FILE *fp, int num_bytes);
void setPalette(char far *palette);
void loadImage(int x, int y, char *file, BITMAP *b);
void saveImage(int x, int y, int width, int height, char file[]);

//---------------------------------------------------------
// Carga un archivo BMP.
//---------------------------------------------------------
void loadImage(int x, int y,char *file, BITMAP *b){
    FILE *fp;
    long index;
    word colorNum;
    int i,j, tempi;

    //Abre el archivo.
    if((fp = fopen(file, "rb"))==NULL)
        exit(1);

    //Verifica si es una BMP válida
    if(fgetc(fp)!= 'B' || fgetc(fp) != 'M')
    {
        fclose(fp);
        exit(1);
    }

    //Lee el tamaño de la imagen y el número de colores.
    fskip(fp,16);
    fread(&b->width,sizeof(word), 1, fp);
    fskip(fp,2);
    fread(&b->height,sizeof(word), 1, fp);
    fskip(fp,22);
    fread(&colorNum,sizeof(word), 1, fp);
    fskip(fp,6);

    //Asume que se está trabajando con un archivo de 8-bit.
    if(colorNum==0)
        colorNum = 256;


    //Lee la información de la paleta.
    for(index=0; index<colorNum; index++)
    {
        b->palette[(int)(index*3+2)] = fgetc(fp) >> 2;
        b->palette[(int)(index*3+1)] = fgetc(fp) >> 2;
        b->palette[(int)(index*3+0)] = fgetc(fp) >> 2;
        fgetc(fp);
    }

    setPalette(b->palette);
    //Lee el bitmap
    for(j=(b->height + y); j>=y ; j--)
    {
        for(i=0; i<(b->width); i++)
        {
          putPixel(i+x, j, fgetc(fp));

          if(i+x==300 && j ==300)
            printf("C: %d\n", getPixel(i+x,y));
        }
    }

    fclose(fp);
}

void loadPalette(char *file, BITMAP *b){
    FILE *fp;
    long index;
    word colorNum;
    int x, y,i,j;

    //Abre el archivo.
    if((fp = fopen(file, "rb"))==NULL)
        exit(1);

    //Verifica si es una BMP válida
    if(fgetc(fp)!= 'B' || fgetc(fp) != 'M')
    {
        fclose(fp);
        exit(1);
    }

    //Lee el tamaño de la imagen y el número de colores.
    fskip(fp,16);
    fread(&b->width,sizeof(word), 1, fp);
    fskip(fp,2);
    fread(&b->height,sizeof(word), 1, fp);
    fskip(fp,22);
    fread(&colorNum,sizeof(word), 1, fp);
    fskip(fp,6);

    //Asume que se está trabajando con un archivo de 8-bit.
    if(colorNum == 0)
        colorNum = 256;


    //Lee la información de la paleta.
    for(index=0;index<colorNum;index++)
    {
        b->palette[(int)(index*3+2)] = fgetc(fp) >> 2;
        b->palette[(int)(index*3+1)] = fgetc(fp) >> 2;
        b->palette[(int)(index*3+0)] = fgetc(fp) >> 2;
        x=fgetc(fp);
    }

    setPalette(b->palette);
}

//---------------------------------------------------------
// Ignora cierta información.
//---------------------------------------------------------
void fskip(FILE *fp, int num_bytes){
    int i;
    for (i=0; i<num_bytes; i++)
        fgetc(fp);
}

//---------------------------------------------------------
// Determina la paleta.
//---------------------------------------------------------
void setPalette(char far *palette){
    asm {
        les dx, [palette]
        mov ax, 0x1012
        mov bx, 0
        mov cx, 256
        int 0x10
    }
}

//---------------------------------------------------------
// Obtiene la paleta.
//---------------------------------------------------------
void getPalette ( char far *palette){
    asm {
        les dx, [palette]
        mov ax, 0x1017
        mov bx, 0
        mov cx, 256
        int 0x10
    }
}

//---------------------------------------------------------
// Guarda una imágen BMP.
//---------------------------------------------------------
void saveImage(int x, int y, int width, int height, char file[]){
    FILE *fp;
    int count, i, j, tempi;
    unsigned char c, ch;
    unsigned long toWrite[13];
    unsigned long palette[256];
    char xInf[2] = "BM";
    //Abre el archivo a escribir.
    fp = fopen(file, "wb");

    //Escribe BM (archivo BMP)
    fwrite(xInf, sizeof(xInf[0]),2,fp);
    x--; y--;
    
    //Escribe el resto del header.
    toWrite[0] = width * height + 1024 + 54;  //Tamaño
    toWrite[1] = 0;             // Reservado
    toWrite[2] = 1024 + 54;         // offset
    toWrite[3] = 40;            // Tamaño del header
    toWrite[4] = width;           // width
    toWrite[5] = height;          // height
    toWrite[6] = 0x80001;         // word planes
    toWrite[7] = 0;             // Compresión
    toWrite[8] = width*height;        // Tamaño del bmp
    toWrite[9] = 0;             // HPPM
    toWrite[10] = 0;            // VPPM
    toWrite[11] = 256;            // Colores utilizados
    toWrite[12] = 256;            // Importa colores
    fwrite(toWrite, sizeof(toWrite[0]), 13, fp);
    
    //Escribe la información de la paleta.
    getPalette(palette);
    palette[0] = 0;
    palette[1] = 0x8;
    palette[2] = 0x800;
    palette[3] = 0x808;
    palette[4] = 0x80000;
    palette[5] = 0x80008;
    palette[6] = 0x80400;
    palette[7] = 0xC0C0C;
    palette[8] = 0x80808;
    palette[9] = 0xFF;
    palette[10] = 0xFF00;
    palette[11] = 0xFFFF;
    palette[12] = 0xFF0000;
    palette[13] = 0xFF00FF;
    palette[14] = 0xFFFF00;
    palette[15] = 0xFFFFFF;
    fwrite(palette, sizeof(unsigned long), 256, fp);
    
    //Escribe los pixeles
    count=0;
    for(j=(y+height); j>=y; j--){
        count++;
        for(i=x; i<=(width+x)-1; i++){
            c=getPixel(i, j);
            fwrite(&c,1,1,fp);
        }
    }

    count--;
    fclose(fp);
}