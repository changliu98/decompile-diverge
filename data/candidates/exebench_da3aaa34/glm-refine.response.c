void __cdecl mtxLoadScale(float *mtx, float xScale, float yScale, float zScale)
{
    // Cast the flat array to a 4x4 matrix for better readability.
    // This assumes a standard row-major 4x4 matrix layout.
    float (*m)[4] = (float (*)[4])mtx;

    // Row 0
    m[0][0] = xScale;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    // Row 1
    m[1][0] = 0.0f;
    m[1][1] = yScale;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    // Row 2
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = zScale;
    m[2][3] = 0.0f;

    // Row 3
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}