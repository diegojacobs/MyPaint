#define sgn(x) ((x < 0) ? -1 : ( (x > 0) ? 1 : 0))

void drawLine(int x1, int y1, int x2, int y2, char color, int thickness);
void drawRectangle(int x1, int y1, int x2, int y2, char color,int thickness);
void drawFilledRectangle(int x1, int y1, int x2, int y2, char color1, char color2, int thickness);
void spray(int x, int y, char color);
void bucketFill(int x, int y, char fillColor, int pattern);
void scanline(int a[20][2], int n, char color1, char color2, int thickness);
void filledElipse(int xc, int yc, int rx, int ry, char color1, char color2, int thickness);
void ellipse(int xc, int yc, int rx, int ry, char color, int thickness);

typedef struct linkedList{
  int x;
  int y;
  struct Node* next;
}Node;

int * colores;

void drawLine(int x1, int y1, int x2, int y2, char color, int thickness){
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
			putGrossPixel(px, py, color, thickness);
		}
	}else{
		for(i=0; i<dy; i++){
			x += dx;
			if (x >= dy){
				x -= dy;
				px += sdx;
			}
			py+=sdy;
			putGrossPixel(px, py, color, thickness);
		}
	}
}

void drawRectangle(int x1, int y1, int x2, int y2, char color,int thickness){
	drawLine(x1, y1, x2, y1, color, thickness);
	drawLine(x1, y1, x1, y2, color, thickness);
	drawLine(x2, y1, x2, y2, color, thickness);
	drawLine(x1, y2, x2, y2, color, thickness);
}

void drawFilledRectangle(int x1, int y1, int x2, int y2, char color1, char color2, int thickness){
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
	drawRectangle(x1, y1, x2, y2, color1, thickness);
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

void push(int x, int y, Node ** finish){
	Node *node;
	node = (Node*) malloc(sizeof(Node));
	node->x=x;
	node->y=y;
	node->next=NULL;
	(*finish)->next=node;
	*finish = (*finish)->next;
}

void bucketFill(int x, int y, char fillColor, int pattern){
	Node *start, *finish, *tmp;
	char oldColor;
	int tempx, tempy;
	colores = (int*) malloc(sizeof(int)*4);
	colores[0] = 0;
	colores[1] = 20;
	colores[2] = 100;
	colores[3] = 120;
	oldColor = getPixel(x, y);

	if(fillColor == oldColor){
    	return;
  	}

	//Node de inicio y final de la lista.
	start = (Node*) malloc(sizeof(Node));
	start->x=x;
	start->y=y;
	start->next=NULL;
	finish = start;

	while(start!=NULL){

		if(pattern==1){
			fillColor = getPixel(100 + x%32, 550 + y%32);
		}else if(pattern == 2){
			fillColor = getPixel(100 + x%32, 510 + y%32);
		}else if(pattern==3){
			fillColor = colores[x%4];
		}

		putPixel(x,y,fillColor);
		//Izquierda
		tempx = x-1;
		if(getPixel(tempx,y) == oldColor && ((tempx)>100 && (tempx)<800 && y>100 && y<600)) {
			if(pattern==1){
				fillColor = getPixel(100 + tempx%32, 550 + y%32);
			}else if(pattern == 2){
				fillColor = getPixel(100 + tempx%32, 510 + y%32);
			}else if(pattern==3){
				fillColor = colores[tempx%4];
			}
			putPixel(tempx,y,fillColor);
			push(tempx, y, &finish);
		}
		//Arriba
		tempy = y+1;
		if(getPixel(x,tempy) == oldColor && (x>100 && x<800 && (tempy)>100 && (tempy)<600)){
			if(pattern==1){
				fillColor = getPixel(100 + x%32, 550 + tempy%32);
			}else if(pattern == 2){
				fillColor = getPixel(100 + x%32, 510 + tempy%32);
			}else if(pattern==3){
				fillColor = colores[x%4];
			}

			putPixel(x,tempy,fillColor);
			push(x, tempy, &finish);
		}
		//Derecha
		tempx = x+1;
		if(getPixel(tempx,y) == oldColor && ((tempx)>100 && (tempx)<800 && y>100 && y<600)){
			if(pattern==1){
				fillColor = getPixel(100 + tempx%32, 550 + y%32);
			}else if(pattern == 2){
				fillColor = getPixel(100 + tempx%32, 510 + y%32);
			}else if(pattern==3){
				fillColor = colores[tempx%4];
			}

			putPixel(tempx,y,fillColor);
			push(tempx,y, &finish);
		}
		//Abajo
		tempy = y-1;
		if(getPixel(x,tempy) == oldColor && (x>100 && x<800 && (tempy)>100 && (tempy)<600)){
			if(pattern==1){
				fillColor = getPixel(100 + x%32, 550 + tempy%32);
			}else if(pattern == 2){
				fillColor = getPixel(100 + x%32, 510 + tempy%32);
			}else if(pattern==3){
				fillColor = colores[x%4];
			}

			putPixel(x,tempy,fillColor);
			push(x,tempy, &finish);
		}
		//Se mueve al siguiente elemento de la lista.
		tmp=start;
		start=start->next;
		x=start->x;
		y=start->y;
		free(tmp);
	}
	free(start);
}

void scanline(int a[20][2], int n, char color1, char color2, int thickness){
	int i,j,k,gd,gm,dy,dx;
	int x,y,temp;
	int xi[20];
	float slope[20];

	for(i=0;i<n-1;i++)
	{
		dy=a[i+1][1]-a[i][1];
		dx=a[i+1][0]-a[i][0];

		if(dy==0) 
			slope[i]=1.0;
		if(dx==0) 
			slope[i]=0.0;

		if((dy!=0)&&(dx!=0)) /*- calculate inverse slope -*/ 
		{
			slope[i]=(float) dx/dy;
		}
	}

	for(y=0;y<600;y++)
	{
		k=0;
		for(i=0;i<n-1;i++)
		{

			if( ((a[i][1]<=y)&&(a[i+1][1]>y)) || ((a[i][1]>y)&&(a[i+1][1]<=y)))
			{
				xi[k]=(int)(a[i][0]+slope[i]*(y-a[i][1]));
				k++;
			}
		}

		for(j=0;j<k-1;j++) /*- Arrange x-intersections in order -*/
			for(i=0;i<k-1;i++)
			{
				if(xi[i]>xi[i+1])
				{
					temp=xi[i];
					xi[i]=xi[i+1];
					xi[i+1]=temp;
				}
			}

		for(i=0;i<k;i+=2)
		{
			drawLine(xi[i], y, xi[i+1]+1, y, color2, 1);
		}
	}

	for(i=0; i<n-1; i++) 
	{
		drawLine(a[i][0], a[i][1], a[i+1][0], a[i+1][1], color1, thickness);
	}
}

void ellipse(int xc, int yc, int rx, int ry, char color, int thickness){
  int x,y;
  float p;
  p=(ry*ry)-(rx*rx*ry)+((rx*rx)/4.0);
  x=0;
  y=ry;
  while(2.0*ry*ry*x <= 2.0*rx*rx*y){
    if(p < 0)
    {
      x++;
      p = p+2.0*ry*ry*x+(float)ry*ry;
    }
    else
    {
      x++;
      y--;
      p = p+2.0*ry*ry*x-2.0*rx*rx*y-(float)ry*ry;
    }
    putGrossPixel(xc+x,yc+y,color,thickness);
    putGrossPixel(xc+x,yc-y,color,thickness);
    putGrossPixel(xc-x,yc+y,color,thickness);
    putGrossPixel(xc-x,yc-y,color,thickness);
   }

  //Region 2
  p=((float)x+0.5)*((float)x+0.5)*ry*ry+((float)y-1.0)*((float)y-1.0)*rx*rx-(float)rx*rx*ry*ry;
  while(y > 0){
    if(p <= 0){
      x++;
      y--;
      p = p+2.0*ry*ry*x-2.0*rx*rx*y+(float)rx*rx;
    }
    else{
      y--;
      p = p-2.0*rx*rx*y+(float)rx*rx;
    }
    putGrossPixel(xc+x,yc+y,color,thickness);
    putGrossPixel(xc+x,yc-y,color,thickness);
    putGrossPixel(xc-x,yc+y,color,thickness);
    putGrossPixel(xc-x,yc-y,color,thickness);
  }
}

void filledElipse(int xc, int yc, int rx, int ry, char color1, char color2, int thickness){
  int x,y;
  double dx,dy;
  for( y=-ry; y<=ry; y++) {
    for( x=-rx; x<=rx; x++) {
        dx = (double)x / (double)rx;
        dy = (double)y / (double)ry;
        if(dx*dx+dy*dy <= 1)
            putGrossPixel(xc+x,yc+y,color2,1);
    }
}
  ellipse(xc,yc,rx,ry,color1,thickness);
}