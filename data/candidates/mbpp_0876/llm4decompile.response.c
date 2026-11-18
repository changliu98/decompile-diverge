int func0(int x, int y)
{
    int z;

    for (z = (x > y ? x : y); ; z++)
        if (z % x == 0 && z % y == 0)
            return z;
}