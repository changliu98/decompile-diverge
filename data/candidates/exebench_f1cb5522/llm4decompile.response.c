void argorder(int ix1, int ix2, int *ox1, int *ox2)
{
    if (ix1 > ix2) {
        *ox1 = ix2;
        *ox2 = ix1;
    } else {
        *ox1 = ix1;
        *ox2 = ix2;
    }
}