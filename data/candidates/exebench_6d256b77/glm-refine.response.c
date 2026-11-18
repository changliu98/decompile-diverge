float __cdecl Intersect(float *S, int i1, int i2, int N)
{
    float inter = 0.0f;
    float interS1 = 0.0f;
    float interS2 = 0.0f;

    // Evaluate the intersection and individual set sizes
    for (int i = 0; i < N; ++i)
    {
        float val1 = S[i + N * i1];
        float val2 = S[i + N * i2];

        if (val1 == 1.0f && val2 == 1.0f)
            inter += 1.0f;
        if (val1 == 1.0f)
            interS1 += 1.0f;
        if (val2 == 1.0f)
            interS2 += 1.0f;
    }

    // Return the ratio of the intersection to the smaller set size.
    // Note: fminf is used to perfectly match the original control flow without 
    // introducing division-by-zero edge case differences (e.g. if both are 0.0f).
    return inter / fminf(interS1, interS2);
}