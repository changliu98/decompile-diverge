int xiph_len(int length)
{
    return length + (length / 255) + 1;
}