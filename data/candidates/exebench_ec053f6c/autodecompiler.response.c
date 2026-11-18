void swapIntEndian(int *integer) {
 char *ptr = (char *) integer;
 char temp = ptr[0];
 ptr[0] = ptr[3];
 ptr[3] = temp;

 temp = ptr[1];
 ptr[1] = ptr[2];
 ptr[2] = temp;
}