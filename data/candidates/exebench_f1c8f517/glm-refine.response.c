void __cdecl ml_multiply_mat4_vec4(float *mat, float *vec, float *out)
{
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];
    float w = vec[3];

    // The compiler evaluated the dot products in reverse order (w, z, y, x) 
    // and stored the first 3 results in temporary variables to avoid 
    // overwriting `vec` elements before they are fully consumed.
    float dot_y = mat[4] * x + mat[5] * y + mat[6] * z + mat[7] * w;
    float dot_z = mat[8] * x + mat[9] * y + mat[10] * z + mat[11] * w;
    float dot_w = mat[12] * x + mat[13] * y + mat[14] * z + mat[15] * w;
    
    float dot_x = mat[0] * x + mat[1] * y + mat[2] * z + mat[3] * w;

    out[0] = dot_x;
    out[1] = dot_y;
    out[2] = dot_z;
    out[3] = dot_w;
}