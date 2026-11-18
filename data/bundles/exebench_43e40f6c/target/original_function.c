int obdRevConvert_0C (float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D) {
 val = val * 4;
 *A = (unsigned int)((long)val / 256);
 *B = (unsigned int)((long)val % 256);
 return 2;
}