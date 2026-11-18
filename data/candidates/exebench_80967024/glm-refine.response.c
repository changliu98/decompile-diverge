void __cdecl upcoef_len_cal(int sigInLength, int filterLen, int stride, int *sigOutLength, int *sigOutLengthDefault)
{
    // Guard against potential null pointer dereferences
    if (!sigOutLength || !sigOutLengthDefault)
        return;

    // Initialize both output lengths with the input signal length
    int len = sigInLength;
    int len_default = sigInLength;

    // The original loop applies an affine transformation `y = 2y + C` for `stride` iterations.
    // This unrolls the loop into an O(1) mathematical formula:
    // After `stride` iterations:
    //   len = (sigInLength - (filterLen - 2)) * 2^stride + (filterLen - 2)
    //   len_default = (sigInLength - (filterLen - 1)) * 2^stride + (filterLen - 1)
    
    int shift = stride;
    while (shift > 0)
    {
        // Using bitwise shift for powers of 2 is generally faster and clearer for binary scaling
        len = (len << 1) + filterLen - 2;
        len_default = (len_default << 1) + filterLen - 1;
        --shift;
    }

    *sigOutLength = len;
    *sigOutLengthDefault = len_default;
}