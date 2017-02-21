
void copyFile(int x1, int y1, int x2, int y2);
void cutFile(int x1, int y1, int x2, int y2, int color, int pattern);
void pasteFile(int x1, int y1);

void copyFile(int x1, int y1, int x2, int y2){
	int i,j,dx,dy;
	FILE *f;

	// Se obtiene el ancho
	dx = abs(x2 - x1);
	// Se obtiene el largo
	dy = abs(y2 - y1);

	// Se abre el archivo
	f = fopen("MyPaint/Buffer/COPY.TXT","w");

	// Se escribe las dimensiones para recorrer el archivo
	fprintf(f, "%i\n", dx);
	fprintf(f, "%i\n", dy);

	// Se recorren los pixeles en y
	for (j=0; j<=dy; j++){
		// Se recorren los pixeles en x
		for (i=0; i<=dx; i++){
			// Se escribe en el archivo el color obtenido
			fprintf(f, "%i\n", getPixel(x1+i,y1+j));
		}
	}
	
	// Se cierra el archivo
	fclose(f);
}


void cutFile(int x1, int y1, int x2, int y2, int color, int pattern){
	int i,j,dx,dy;
	FILE *f1;

	// Se obtiene el ancho
	dx = abs(x2 - x1);
	// Se obtiene el largo
	dy = abs(y2 - y1);

	// Abre el archivo
	f1 = fopen("MyPaint/Buffer/COPY.TXT","w");

	// Se escribe las dimensiones para recorrer el archivo
	fprintf(f1, "%i\n", dx);
	fprintf(f1, "%i\n", dy);

	if (x1 > x2) x1 = x2;
	if (y1 > y2) y1 = y2;

	// Se recorren los pixeles en y
	for (j=0; j<=dy; j++){
		// Se recorren los pixeles en x
		for (i=0; i<=dx; i++){
			// Se escribe en el archivo el color obtenido
			fprintf(f1, "%i\n", getPixel(x1 + i, y1 + j));
			// Se pinta del color predeterminado
			putThicknessPixel(x1 + i, y1 + j, color, SMALL, pattern);
		}
	}
	
	// Se cierra el archivo
	fclose(f1);
}


void pasteFile(int x1, int y1){
	int x, y,
		dx, dy;
	FILE *f1;
	char line[20];

	// Abre el archivo
	f1 = fopen("MyPaint/Buffer/COPY.TXT","r");

	// Se determinan las variables de dx,dy,x,y
	x = 0; y = 0;
	sscanf(fgets(line,sizeof(line),f1), "%i", &dx);
	sscanf(fgets(line,sizeof(line),f1), "%i", &dy);

	// Mientras hayan lineas en el archivo
	while(fgets(line,sizeof(line),f1) != NULL){
		// Se recorre y
		if (y < dy){
			// Se recorre x
			if (x < dx){
				int i;
				// Se obtiene el color de la linea como union de caracteres
				sscanf(line, "%i", &i);
				// Se determina si esta dentro del canvas para poder pintar
				if (x1 + x<800 && y1 + y<600){
					// Pinta el pixel
					putPixel(x1 + x, y1 + y, i);
				}
				x += 1;
			}else{
				x = 0;
				y += 1;
			}
		}
	}

	// Se cierra el archivo
	fclose(f1);
}