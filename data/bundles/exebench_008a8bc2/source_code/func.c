
int obdRevConvert_42 (float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D) {
 val = val * 1000.0f;
 *A = (unsigned int)((long)val / 256);
 *B = (unsigned int)((long)val % 256);
 return 2;
}
