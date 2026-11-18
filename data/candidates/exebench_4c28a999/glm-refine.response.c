void __cdecl fb_hFixCoordsOrder(int *x1, int *y1, int *x2, int *y2)
{
    // Ensure x1 is the left coordinate and x2 is the right coordinate
    if (*x2 < *x1)
    {
        int temp = *x1;
        *x1 = *x2;
        *x2 = temp;
    }

    // Ensure y1 is the top coordinate and y2 is the bottom coordinate
    if (*y2 < *y1)
    {
        int temp = *y1;
        *y1 = *y2;
        *y2 = temp;
    }
}