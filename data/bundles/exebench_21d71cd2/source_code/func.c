
int obdRevConvert_23 (float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D) {
 val = val / 10.0f;
 *A = (unsigned int)((long)val / 256);
 *B = (unsigned int)((long)val % 256);
 return 2;
}
