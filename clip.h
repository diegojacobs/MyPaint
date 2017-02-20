typedef struct ClipLine{
    int x0;
    int y0;
    int x1;
    int y1;
}clipLine;
typedef unsigned int outCode;

enum {  
    TOP = 0x1,      //1000
    BOTTOM = 0x2,   //0010
    RIGHT = 0x4,    //0100
    LEFT = 0x8      //1000
};

/*Valores de verdad */
#define TRUE 1
#define FALSE 0

/*Funciones */
clipLine clipping(float x0, float y0, float x1, float y1, float xmin, float ymin, float xmax, float ymax);
outCode compOutCode(float x, float y, float xmin, float ymin, float xmax, float ymax);

//---------------------------------------------------------
// Realiza el clipping a la línea.
//---------------------------------------------------------
clipLine clipping(float x0,float y0,float x1,float y1, float xmin, float ymin, float xmax, float ymax){
    outCode outCode0, outCode1, outCodeOut;
    int acc, end;
    clipLine tmp;

    acc = FALSE;
    end = FALSE;
    //Compara los outcodees para revisar los límites.
    outCode0 = compOutCode(x0, y0, xmin, ymin, xmax, ymax);
    outCode1 = compOutCode(x1, y1, xmin, ymin, xmax, ymax);
    do{
        //Realización del OR es 0.
        if(!(outCode0|outCode1)){
          acc = TRUE;
          end = TRUE;
        }
        //Realización del AND no es 0.
        else if(outCode0 & outCode1){
            end = TRUE;
        }
        //Fallan las pruebas y se realiza el clipping.
        else{
            float x, y;
            outCodeOut = outCode0 ? outCode0 : outCode1;
            //El punto se encuentra arriba del canvas.
            if(outCodeOut & TOP){
                x = x0+(x1-x0)*(ymax-y0)/(y1-y0);
                y = ymax;
            //El punto se encuentra abajo del canvas.
            }else if(outCodeOut & BOTTOM){
                x = x0+(x1-x0)*(ymin-y0)/(y1-y0);
                y = ymin;
            //El punto se encuentra muy a la derecha del canvas.
            }else if(outCodeOut & RIGHT){
                y = y0+(y1-y0)*(xmax-x0)/(x1-x0);
                x = xmax;
            }
            //El punto se encuentra muy a la izquierda del canvas.
            else{
                y = y0+(y1-y0)*(xmin-x0)/(x1-x0);
                x = xmin;
            }
            //Se mueve para la siguiente pasada.
            if(outCodeOut == outCode0){
                x0 = x;
                y0 = y;
                outCode0 = compOutCode(x0, y0, xmin, ymin, xmax, ymax);
            }else{
                x1 = x;
                y1 = y;
                outCode1 = compOutCode(x1, y1, xmin, ymin, xmax, ymax);
            }
        }
    }
    while(end==FALSE);
    //Guarda los nuevos valores de la línea y la retorna.
    if(acc){
        tmp.x0 = x0;
        tmp.y0 = y0;
        tmp.x1 = x1;
        tmp.y1 = y1;
    }else{
        tmp.x0 = 0;
        tmp.y0 = 0;
        tmp.x1 = 0;
        tmp.y1 = 0;
    }
    return tmp;
}

//---------------------------------------------------------
// Comparación de dos outCodes.
//---------------------------------------------------------
outCode compOutCode(float x, float y, float xmin, float ymin, float xmax, float ymax)
{
    outCode code = 0;
    if(y>ymax){
      code|=TOP;
    }else if(y<ymin){
      code|=BOTTOM;
    }
    if(x>xmax){
      code|=RIGHT;
    }else if(x<xmin){
      code|=LEFT;
    }
    return code;
}