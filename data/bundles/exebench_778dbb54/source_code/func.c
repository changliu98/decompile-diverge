
int obdRevConvert_43 (float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D) {
 val = val * 255.0f / 100.0f;
 *A = (unsigned int)((long)val / 256);
 *B = (unsigned int)((long)val % 256);
 return 2;
}
