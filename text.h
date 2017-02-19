/* Variables */
int asciiI = 32;
int fontW, fontH;			
unsigned int * tempLine;

/* Funciones */
void setDimensions(int width, int height);
int putChar(int x, int y, int nchar, char color, char masc, char font[][16*16]);
void printText(int x, int y, char color, char font[][16*16]);

//---------------------------------------------------------
// Cambia las dimensiones de la fuente.
//---------------------------------------------------------
void setDimensions(int width, int height){
	fontW = width;				//Ancho de la fuente.
	fontH = height;				//Alto de la fuente.
}

//---------------------------------------------------------
// Permite colocar un caracter en pantalla.
//---------------------------------------------------------
int putChar(int x, int y, int nchar, char color, char masc, char font[][16*16]){
	int charOffs;
	char w, h;
	if(nchar>31 && nchar<91){
		charOffs = nchar-asciiI;
	}else if(nchar>96 && nchar<123){
		charOffs = nchar-2*asciiI;
	}else{
		return 1;
	}
	
	for(h=0; h<fontH; h++){
		for(w=0; w<fontW; w++){
			if(font[charOffs][h*fontW+w] != masc){
				putPixel(x+w, y+h, color);
			}
		}
	}
	return 0;
}


void printText(int x, int y, char color, char font[][16*16]){
  char texto;
  int tempx, tempy;
  int x1 = x;
  int y1 = y;
  unsigned char backspace[16][16];
  tcline(x1,y1,x1,y1+16,color,1);
  delay(100);
  texto = 0;
  while(texto!=13){
    rcline(x1,y1,x1,y1+16,1);
    delay(100);
    if(kbhit()){
      texto = getch();
      if(!(x1+16<800)&&texto!=8){
        if(y1+18<600){
          x1 = x;
          y1 += 18;
        }else{
          tcline(x1,y1,x1,y1+16,color,1);
          delay(100);
          break;
        }
      }
      if(texto!=13 && texto!=8){
        for(tempx=0; tempx<16; tempx++){
          for(tempy=0; tempy<16; tempy++){
            backspace[tempx][tempy]=getPixel(x1+tempx,y1+tempy);
          }
        }
        putChar(x1, y1, texto, color, 0, font);
        x1+=17;
      }else if(texto==8 && x1!=x){
        x1 += -17;
        for(tempx=0; tempx<16; tempx++){
          for(tempy=0; tempy<16; tempy++){
            putPixel(x1+tempx, y1+tempy,backspace[tempx][tempy]);
          }
        }
      }
    }
    tcline(x1,y1,x1,y1+16,color,1);
    delay(100);
  }
  rcline(x1,y1,x1,y1+16,1);
}

//---------------------------------------------------------
// Linea temporal con cliping.
//---------------------------------------------------------
int tcline(int x0, int y0, int x1, int y1, char drawcolor, int thickness){
  int dx, dy, err, d, sgnx, sgny, tmp, h, i;
  clipLine l = clipping((float) x0, (float) y0, (float) x1, (float) y1,
      201, 31, 768, 469);
  x0=l.x0; y0=l.y0; x1=l.x1; y1=l.y1;
  dx = abs(x1-x0);              //Distancia horizontal.
  dy = abs(y1-y0);              //Distancia vertical.
  sgnx = 1;                     //Valor a sumar en x.
  h = dx*dy+2;
  tempLine = (int*) malloc(sizeof(int)*h);
  i=0;
  //Intercambio de coordenadas en x.
  if(x0>x1){
    tmp = x0;
    x0 = x1;
    x1 = tmp;
    tmp = y0;
    y0 = y1;
    y1 = tmp;
  }
  sgny = y0<y1 ? 1 : -1;        //Valor a sumar en y.
  //Cambio que define si la recta es más horizontal o vertical.
  err = dx-dy;
  do{
    tempLine[i++] = getPixel(x0,y0);
    putGrossPixel(x0,y0, drawcolor,thickness);
    d = 2*err;
    if (d > -dy){               //Línea más horizontal.
      err -= dy;                //Balancea el cambio.
      x0 += sgnx;               //Aumenta en x.
    }
    if (d < dx){                //Línea más vertical.
      err += dx;                //Balancea el cambio.
      y0 += sgny;               //Aumenta en y.
    }
  }while ((x0 != x1) || (y0 != y1));
  tempLine[i++] = getPixel(x0,y0);
  putGrossPixel(x0,y0, drawcolor,thickness);
  return 0;
}

//---------------------------------------------------------
// Línea para remover.
//---------------------------------------------------------
int rcline(int x0, int y0, int x1, int y1, int thickness){
  int dx, dy, err, d, sgnx, sgny, tmp,i;
  clipLine l = clipping((float) x0, (float) y0, (float) x1, (float) y1,
      201, 31, 768, 469);
  x0=l.x0; y0=l.y0; x1=l.x1; y1=l.y1;
  dx = abs(x1-x0);              //Distancia horizontal.
  dy = abs(y1-y0);              //Distancia vertical.
  sgnx = 1;                     //Valor a sumar en x.
  i=0;
  //Intercambio de coordenadas en x.
  if(x0>x1){
    tmp = x0;
    x0 = x1;
    x1 = tmp;
    tmp = y0;
    y0 = y1;
    y1 = tmp;
  }
  sgny = y0<y1 ? 1 : -1;        //Valor a sumar en y.
  //Cambio que define si la recta es más horizontal o vertical.
  err = dx-dy;
  do{
    putGrossPixel(x0,y0, tempLine[i++],thickness);
    d = 2*err;
    if (d > -dy){               //Línea más horizontal.
      err -= dy;                //Balancea el cambio.
      x0 += sgnx;               //Aumenta en x.
    }
    if (d < dx){                //Línea más vertical.
      err += dx;                //Balancea el cambio.
      y0 += sgny;               //Aumenta en y.
    }
  }while ((x0 != x1) || (y0 != y1));
  putGrossPixel(x0,y0, tempLine[i++],thickness);
  free(tempLine);
  tempLine = 0;
  return 0;
}