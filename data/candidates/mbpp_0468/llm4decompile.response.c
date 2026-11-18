int func0(int *mpis, int n)
{
    int mpis2[200];
    int i, j;
    for (i = 0; i < n; i++)
        mpis2[i] = mpis[i];
    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++)
            if (mpis[j] < mpis[i] && mpis2[i] < mpis2[j] * mpis[i])
                mpis2[i] = mpis2[j] * mpis[i];
    int maxVal = mpis2[0];
    for (i = 1; i < n; i++)
        if (mpis2[i] > maxVal)
            maxVal = mpis2[i];
    return maxVal;
}