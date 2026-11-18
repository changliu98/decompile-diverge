void __cdecl DoAdjust(int *x, int *y, int dx_0, int dy, int cols, int rows)
{
    // Convert from 1-based to 0-based indexing
    *x -= 1;
    *y -= 1;

    // Apply horizontal delta
    *x += dx_0;

    // Handle negative wrap-around (when moving left past the beginning)
    if (*x < 0)
    {
        // Convert the negative index to its positive equivalent in the grid
        *x = cols - *x;
        // Adjust the row (y) accordingly and normalize x within the column bounds
        *y -= *x / cols;
        *x = cols - (*x % cols);
    }

    // Normalize x to be within [0, cols-1] and carry over any overflow into y (the row)
    *y += *x / cols;
    *x %= cols;

    // Apply vertical delta
    *y += dy;

    // Convert back from 0-based to 1-based indexing
    *x += 1;
    *y += 1;
}