void bitrv216(double *a) {
    // The array 'a' is treated as an array of 32 doubles (16 complex numbers).
    // The function swaps elements to achieve a bit-reversed permutation.
    
    // Swap a[1] and a[8]
    double tmp1 = a[1];
    a[1] = a[8];
    a[8] = tmp1;
    
    // Swap a[2] and a[4]
    double tmp2 = a[2];
    a[2] = a[4];
    a[4] = tmp2;
    
    // Swap a[3] and a[12]
    double tmp3 = a[3];
    a[3] = a[12];
    a[12] = tmp3;
    
    // Swap a[5] and a[10]
    double tmp5 = a[5];
    a[5] = a[10];
    a[10] = tmp5;
    
    // Swap a[7] and a[14]
    double tmp7 = a[7];
    a[7] = a[14];
    a[14] = tmp7;
    
    // Swap a[11] and a[13]
    double tmp11 = a[11];
    a[11] = a[13];
    a[13] = tmp11;
}