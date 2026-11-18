void bitmap_free(unsigned int *array, int index)
{
    int offset = index % 32;
    array[index / 32] &= ~(1 << (31 - offset));
}