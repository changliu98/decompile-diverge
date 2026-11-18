void __cdecl next(int *row, int *col, int width)
{
    (*col)++;
    if (*col == width)
    {
        *col = 0;
        (*row)++;
    }
}