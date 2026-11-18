int
func0(int x, int y, int z)
{
    int q, r;

    if (z < ((y) - 1))
        q = ((y) - 1);
    else
        q = z;
    r = x * q / y;
    return r;
}