void peneira(int m, int *v)
{
    int f = 2;
    int p = 1;
    int t = v[1];
    while (f <= m)
    {
        if (f < m && v[f] < v[f+1])
            f++;
        if (t <= v[f])
            break;
        v[p] = v[f];
        p = f;
        f = f * 2;
    }
    v[p] = t;
}