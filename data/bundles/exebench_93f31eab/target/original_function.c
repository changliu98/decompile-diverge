int obdRevConvert_10 (float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D) {
 val = val * 100;
 *A = (unsigned int)((long)val / 256);
 *B = (unsigned int)((long)val % 256);
 return 2;
}