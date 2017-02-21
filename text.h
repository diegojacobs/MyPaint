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

int putChar(int x, int y, int nchar, char color, char masc, char font[][16*16]){
	int charOffset;
	char w, h;
	if(nchar>31 && nchar<91){
		charOffset = nchar-asciiI;
	}else if(nchar>96 && nchar<123){
		charOffset = nchar-2*asciiI;
	}else{
		return 1;
	}
	
	for(h=0; h<fontH; h++){
		for(w=0; w<fontW; w++){
			if(font[charOffset][h*fontW+w] != masc){
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
  unsigned char background[16][16];
  delay(100);
  texto = 0;
  while(texto != 13){
    delay(100);
    if(kbhit()){
      texto = getch();
      if(!(x1 + 16 < 800)&& texto != 8){
        if(y1 + 18 < 600){
          x1 = x;
          y1 += 18;
        }else{
          delay(100);
          break;
        }
      }
      if(texto != 13 && texto != 8){
        for(tempx = 0; tempx < 16; tempx++){
          for(tempy = 0; tempy < 16; tempy++){
            background[tempx][tempy] = getPixel(x1 + tempx, y1 + tempy);
          }
        }
        putChar(x1, y1, texto, color, 0, font);
        x1+=17;
      }else if(texto == 8 && x1 != x){
        x1 += -17;
        for(tempx = 0; tempx < 16; tempx++){
          for(tempy = 0; tempy < 16; tempy++){
            putPixel(x1+tempx, y1+tempy, background[tempx][tempy]);
          }
        }
      }
    }
    delay(100);
  }
}