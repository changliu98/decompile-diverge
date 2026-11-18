void load_scl_mat(float M[16], float x, float y, float z)
{
    M[0] = x; M[4] = 0; M[8] = 0; M[12] = 0;
    M[1] = 0; M[5] = y; M[9] = 0; M[13] = 0;
    M[2] = 0; M[6] = 0; M[10] = z; M[14] = 0;
    M[3] = 0; M[7] = 0; M[11] = 0; M[15] = 1;
}