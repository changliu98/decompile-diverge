int hex_to_int(char *hex, int length)
{
 int i;
 int out = 0;

 if(length > 5) {
  printf__bench("hex_to_int(): Length of input string is too large!\n");
  return 0;
 }

 for(i = 0; i < length; i++) {
  out = out*100 + (hex[i]/16)*10 + hex[i]%16;
 }

 return out;
}