int obdRevConvert_3C_3F (float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D) {
 val = val + 40.0f;
 val = val * 10.0f;
 *A = (unsigned int)((long)val / 256);
 *B = (unsigned int)((long)val % 256);
 return 2;
}