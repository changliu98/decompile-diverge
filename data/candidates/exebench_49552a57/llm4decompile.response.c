int matV4toV3(const double v4[4], double v3[3])
{
    int i;
    for(i = 0; i < 3; i++)
        v3[i] = v4[i];

    return 0;
}