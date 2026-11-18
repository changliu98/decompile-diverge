int func0(int a, int b)
{
    int ret = 0;
    int i = b / 2;
    ret += i * (b / 2 + 1);
    ret -= (a - 1) / 2 * (a + 1) / 2;
    return ret;
}