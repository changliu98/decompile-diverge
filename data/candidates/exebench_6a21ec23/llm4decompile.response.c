void set_mask(int *mask, int size, int offset, int length)
{
    int i;
    int j;

    i = 0;
    if (offset > 0)
        mask[i++] = -offset;
    mask[i++] = length;
    mask[i++] = -(size - offset - length);
    mask[i++] = 0;
}