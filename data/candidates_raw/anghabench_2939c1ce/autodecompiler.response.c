void swapIntEndian(unsigned int *integer) {
 char *intAsChar = (char *) integer;
 char tmp;

 tmp = intAsChar[0];
 intAsChar[0] = intAsChar[3];
 intAsChar[3] = tmp;

 tmp = intAsChar[1];
 intAsChar[1] = intAsChar[2];
 intAsChar[2] = tmp;
}