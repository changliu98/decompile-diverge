int matV3toV4(double v3[3], double v4[4])
{
    int i;
    for(i = 0; i < 3; i++)
        v4[i] = v3[i];
    v4[3] = 1.0;
    return 0;
}