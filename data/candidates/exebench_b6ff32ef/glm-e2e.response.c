void xformMultiply(Matrix2x3 *a, Matrix2x3 *b) {
    // Calculate new element 0: a[0]*b[0] + a[1]*b[2]
    float r0 = a->m[0] * b->m[0] + a->m[1] * b->m[2];
    
    // Calculate new element 1: a[0]*b[1] + a[1]*b[3]
    float r1 = a->m[0] * b->m[1] + a->m[1] * b->m[3];
    
    // Calculate new element 2: a[2]*b[0] + a[3]*b[2]
    float r2 = a->m[2] * b->m[0] + a->m[3] * b->m[2];
    
    // Calculate new element 3: a[2]*b[1] + a[3]*b[3]
    float r3 = a->m[2] * b->m[1] + a->m[3] * b->m[3];
    
    // Calculate new element 4: a[4]*b[0] + a[5]*b[2] + b[4]
    float r4 = a->m[4] * b->m[0] + a->m[5] * b->m[2] + b->m[4];
    
    // Calculate new element 5: a[4]*b[1] + a[5]*b[3] + b[5]
    float r5 = a->m[4] * b->m[1] + a->m[5] * b->m[3] + b->m[5];

    // Store the results back into the first matrix
    a->m[0] = r0;
    a->m[1] = r1;
    a->m[2] = r2;
    a->m[3] = r3;
    a->m[4] = r4;
    a->m[5] = r5;
}