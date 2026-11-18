void __cdecl mlMatrixTransposeTo(const float a[4][4], float result[4][4])
{
    for (unsigned int j = 0; j < 4; ++j)
    {
        for (unsigned int i = 0; i < 4; ++i)
        {
            result[j][i] = a[i][j];
        }
    }
}