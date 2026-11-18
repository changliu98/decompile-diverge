void atmtns(const double delta[3], double v[3])
{
    int k;
    for (k = 0; k < 3; k++) {
        v[k] += delta[k];
    }
}