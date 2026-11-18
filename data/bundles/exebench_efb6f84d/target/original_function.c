int obdRevConvert_2D (float val, unsigned int *A, unsigned int *B, unsigned int *C, unsigned int *D) {
 *A = (unsigned int)((val + 100.0f) / 0.78125f);
 return 1;
}