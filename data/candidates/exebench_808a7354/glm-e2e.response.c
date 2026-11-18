void Mat4_affine_inv(Mat4 *mat) {
    // Transpose the 3x3 upper-left linear part of the matrix
    // Swap m[1] and m[4]
    float temp = mat->m[1];
    mat->m[1] = mat->m[4];
    mat->m[4] = temp;

    // Swap m[2] and m[8]
    temp = mat->m[2];
    mat->m[2] = mat->m[8];
    mat->m[8] = temp;

    // Swap m[6] and m[9]
    temp = mat->m[6];
    mat->m[6] = mat->m[9];
    mat->m[9] = temp;

    // Compute the new translation vector
    // tx' = -(m[0]*m[12] + m[4]*m[13] + m[8]*m[14])
    float tx = mat->m[0] * mat->m[12] + mat->m[4] * mat->m[13] + mat->m[8] * mat->m[14];
    
    // ty' = -(m[1]*m[12] + m[5]*m[13] + m[9]*m[14])
    float ty = mat->m[1] * mat->m[12] + mat->m[5] * mat->m[13] + mat->m[9] * mat->m[14];
    
    // tz' = -(m[2]*m[12] + m[6]*m[13] + m[10]*m[14])
    float tz = mat->m[2] * mat->m[12] + mat->m[6] * mat->m[13] + mat->m[10] * mat->m[14];

    // Negate the results and store them back into the translation vector
    // The XOR with 0x80000000 flips the sign bit of the IEEE 754 float
    mat->m[12] = -tx;
    mat->m[13] = -ty;
    mat->m[14] = -tz;
}