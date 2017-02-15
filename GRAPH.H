
#define sgn(x) ((x < 0) ? -1 : ( (x > 0) ? 1 : 0))


void drawLine(int x1, int y1, int x2, int y2, char color, int tkn);
void drawRectangle(int x1, int y1, int x2, int y2, char color,int tkn);
void drawFilledRectangle(int x1, int y1, int x2, int y2, char color1, char color2, int tkn);
void spray(int x, int y, char color);


void drawLine(int x1, int y1, int x2, int y2, char color, int tkn){
int i, dx, dy, sdx, sdy, x, y, px, py;
	dx = x2 - x1;
	dy = y2 - y1;

	sdx = sgn(dx);
	sdy = sgn(dy);

	if (dx < 0){
		dx = dx * -1;
	}

	if (dy < 0){
		dy = dy * -1;
	}

	x = dy>>1;
	y = dx>>1;	

	px = x1;
	py = y1;

	if(dx >= dy){
		for(i=0; i<dx; i++){
			y += dy;
			if(y >= dx){
				y -= dx;
				py += sdy;
			}
			px+=sdx;
			putGrossPixel(px, py, color, tkn);
		}
	}else{
		for(i=0; i<dy; i++){
			x += dx;
			if (x >= dy){
				x -= dy;
				px += sdx;
			}
			py+=sdy;
			putGrossPixel(px, py, color, tkn);
		}
	}
}

void drawRectangle(int x1, int y1, int x2, int y2, char color,int tkn){
	drawLine(x1, y1, x2, y1, color, tkn);
	drawLine(x1, y1, x1, y2, color, tkn);
	drawLine(x2, y1, x2, y2, color, tkn);
	drawLine(x1, y2, x2, y2, color, tkn);
}

void drawFilledRectangle(int x1, int y1, int x2, int y2, char color1, char color2, int tkn){
	int y, temp;

	//Arregla los valores de y1 y y2 para que sean congruentes.
	if(y1 > y2){
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	//Se dibuja el relleno del rectangulo.
	for(y = y1; y <= y2; y++){
		drawLine(x1, y, x2, y, color2 ,1);
	}

	//Se dibuja el contorno.
	drawRectangle(x1, y1, x2, y2, color1, tkn);
}

void spray(int x, int y, char color){
  int i, randx, randy;
  time_t t;
  randx = 0;  
  randy = 0;      
  for(i = 0; i < 5000; i++){
    srand((unsigned) time(&t)+randx);
    randx = rand() % 20;
    randy = rand() % 20;
    putPixel(x-randx, y-randy, color);
  }
}