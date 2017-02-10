long resY, resX, limitX, limitY, numberOfBanks;
char currentBank;

#define v800x600x256     0x103
#define v1024x768x256    0x105
#define v1280x1024x256   0x107

int setVideoSVGA(int mode, long w, long h);
void unsetVideoSVGA();
void switchBankSVGA(char banco);
void putPixel(int x, int y, char drawcolor);
char getPixel(int x, int y);

int setVideoSVGA(int mode, long w, long h){
   resY = h;
   resX = w;
   numberOfBanks = ((resX*resY)/65536L);
   limitX = resX-1;
   limitY = resY-1;
   asm{
      MOV AX, 4F02H
      MOV BX, [mode]
      INT 10H                     
      CMP AX, 004FH
      JNE Error
   }
   return(1);
   Error:;
   return(0);
}

void unSetVideoSVGA(){
   asm{
      MOV AX, 0003H
      XOR BX, BX
      INT 10H
   }
}

void setSVGABank(char banco){
   asm{
      MOV AL, [banco]
      CMP[currentBank], AL
      JE noSwitchBank
      MOV [currentBank], AL
      MOV AX, 4F05H
      XOR BX, BX 
      XOR DX, DX
      MOV DL, [banco]
      INT 10H
   }
   noSwitchBank:;
}

void putPixel(int x, int y, char drawcolor){
   long memoryPosition;
   int pixelOffset;
   char bank;

   //Verificación de los límites de la pantalla.
   if(x>limitX || x<0 || y>limitY || y<0){
      return;
   }

   memoryPosition = (y*resX)+x;
   bank = memoryPosition>>16;
   pixelOffset = memoryPosition-(bank<<16);

   //Se cambia al banco correcto.
   if(bank != currentBank){
      setSVGABank(bank);
      currentBank = bank;
   }

   asm{
      MOV AX, 0A000H
      MOV ES, AX
      MOV DI, [pixelOffset]
      MOV AL, [drawcolor]
      MOV ES:[DI], AL
   }
}

void putGrossPixel(int x, int y, char drawcolor, int tkn){
  int i,j, px, py;                      
  //Coloca el grosor del pixel alrededor.
  for(i=0; i<tkn; i++){
    for(j=0; j<tkn; j++){
         px = x + j; 
         py = y + i;
         putPixel(px, py, drawcolor);
    }
  }
}

char getPixel(int x, int y){
  long memoryPosition;
  int pixelOffset;
  char bank, color;

  /*
  y*resX = y*800 = y*512+y*256 + y*32 = y*2**9 + y*2**8 + y*2**5
  */
  memoryPosition = (y*resX)+x;
  bank = memoryPosition>>16;
  pixelOffset = memoryPosition-(bank<<16);

  if(bank != currentBank){
    setSVGABank(bank);
    currentBank = bank;
  }

  asm{
    MOV AX, 0A000H
    MOV ES, AX
    MOV DI, [pixelOffset]
    MOV AL, ES: [DI]
    MOV [color], AL 
  }
  return (color);
}