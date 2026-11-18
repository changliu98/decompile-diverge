void __cdecl cspline2bezier(double *out, const double *in)
{
    // The decompiled matrix initialization corresponds to the following constant matrix:
    //      [ 1.0,   1.0,   0.0,   0.0 ]
    //      [ 0.0,   1/3,   0.0,   0.0 ]
    //      [ 0.0,   0.0,   1.0,   1.0 ]
    //      [ 0.0,   0.0,  -1/3,   0.0 ]
    static const double m[4][4] = {
        { 1.0,  1.0,  0.0,  0.0 },
        { 0.0,  1.0 / 3.0,  0.0,  0.0 },
        { 0.0,  0.0,  1.0,  1.0 },
        { 0.0,  0.0, -1.0 / 3.0,  0.0 }
    };

    // The nested loops compute a matrix-vector multiplication: out = m^T * in
    for (int i = 0; i < 4; ++i)
    {
        out[i] = 0.0;
        for (int j = 0; j < 4; ++j)
        {
            out[i] += m[j][i] * in[j];
        }
    }
}