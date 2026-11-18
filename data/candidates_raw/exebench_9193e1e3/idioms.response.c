void check_coord(int *coord, int min, int max)
{
    int val;
    if (*coord < min)
        val = min;
    else
        val = *coord;
    if (val > max)
        val = max;
    *coord = val;
}