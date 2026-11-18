void __cdecl c_saxpy(int n, double sa, double *sx, double *sy)
{
    // Early exit if the vector length is invalid or the scalar multiplier is zero
    if (n <= 0 || sa == 0.0)
        return;

    // Handle the remainder of elements (n % 4) that don't fit into the unrolled loop
    int m = n % 4;
    for (int i = 0; i < m; ++i)
    {
        sy[i] = sa * sx[i] + sy[i];
    }

    // Process the remaining elements in chunks of 4 (loop unrolling optimization)
    for (int ia = m; ia < n; ia += 4)
    {
        sy[ia]     = sa * sx[ia]     + sy[ia];
        sy[ia + 1] = sa * sx[ia + 1] + sy[ia + 1];
        sy[ia + 2] = sa * sx[ia + 2] + sy[ia + 2];
        sy[ia + 3] = sa * sx[ia + 3] + sy[ia + 3];
    }
}