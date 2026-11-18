void load_scl_mat(float M[], float x, float y, float z)
{
    M[0] = x;
    M[1] = 0.0f;
    M[2] = 0.0f;
    M[3] = 0.0f;

    M[4] = 0.0f;
    M[5] = y;
    M[6] = 0.0f;
    M[7] = 0.0f;

    M[8] = 0.0f;
    M[9] = 0.0f;
    M[10] = z;
    M[11] = 0.0f;

    M[12] = 0.0f;
    M[13] = 0.0f;
    M[14] = 0.0f;
    M[15] = 1.0f;
}