void __cdecl mtxScaleMatrix(Matrix4x4 *mtx, float xScale, float yScale, float zScale)
{
    // Iterate through each of the 4 columns
    for (int i = 0; i < 4; ++i)
    {
        // Scale the respective row vectors by their corresponding scale factors
        mtx->m[i][0] *= xScale;
        mtx->m[i][1] *= yScale;
        mtx->m[i][2] *= zScale;
        // mtx->m[i][3] is untouched, which corresponds to the translation row (w-axis)
    }
}