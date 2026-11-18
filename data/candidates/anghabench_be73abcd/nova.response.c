static int val_seg(int x)
{
    int count = 0;
    x >>= 7;
    if (x) {
        x >>= 4;
        count += 4;
    }
    if (x) {
        x >>= 2;
        count += 2;
    }
    if (x) {
        x >>= 1;
        count += 1;
    }
    return count;
}