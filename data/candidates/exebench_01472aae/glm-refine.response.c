void __cdecl mlMatrixLoadPositionTransposedRotation(float *m, const float *p, const float *r)
{
    // Cast the 1D arrays to 2D arrays to clearly represent rows and columns
    float (*mat)[4] = (float (*)[4])m;
    const float (*rot)[4] = (const float (*)[4])r;
    const float (*pos)[1] = (const float (*)[1])p;

    // Row 0: Transposed rotation X-axis
    mat[0][0] = rot[0][0];
    mat[0][1] = rot[1][0];
    mat[0][2] = rot[2][0];
    mat[0][3] = 0.0f;

    // Row 1: Transposed rotation Y-axis
    mat[1][0] = rot[0][1];
    mat[1][1] = rot[1][1];
    mat[1][2] = rot[2][1];
    mat[1][3] = 0.0f;

    // Row 2: Transposed rotation Z-axis
    mat[2][0] = rot[0][2];
    mat[2][1] = rot[1][2];
    mat[2][2] = rot[2][2];
    mat[2][3] = 0.0f;

    // Row 3: Position and homogeneous '1'
    mat[3][0] = pos[0][0];
    mat[3][1] = pos[1][0];
    mat[3][2] = pos[2][0];
    mat[3][3] = 1.0f;
}