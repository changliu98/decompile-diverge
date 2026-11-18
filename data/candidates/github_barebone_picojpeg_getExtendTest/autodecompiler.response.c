unsigned short int getExtendTest(char c){
 unsigned short int temp;
 switch(c){
  case 0:
   temp = 0;
   break;
  case 1:
   temp = 1;
   break;
  case 2:
   temp = 2;
   break;
  case 3:
   temp = 4;
   break;
  case 4:
   temp = 8;
   break;
  case 5:
   temp = 16;
   break;
  case 6:
   temp = 32;
   break;
  case 7:
   temp = 64;
   break;
  case 8:
   temp = 128;
   break;
  case 9:
   temp = 256;
   break;
  case 10:
   temp = 512;
   break;
  case 11:
   temp = 1024;
   break;
  case 12:
   temp = 2048;
   break;
  case 13:
   temp = 4096;
   break;
  case 14:
   temp = 8192;
   break;
  case 15:
   temp = 16384;
   break;
  default:
   temp = 0;
 }
 return temp;
}