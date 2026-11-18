static int genx(unsigned char dst[256], unsigned char field[256])
{
 int error = 0;
 short int index[256];
 int i;
 unsigned int e;
 int x;


 for (i = 0; i < 256; i++)
  index[i] = -1;


 for (i = 0; i < 256; i++) {
  e = field[i];
  x = index[e];
  if (x != -1) {



   error = 1;
  } else {
   index[e] = i;
  }
 }




 for (i = 0; i < 256; i++)
  dst[i] = index[i];

 return (error == 0)? 0: -1;
}