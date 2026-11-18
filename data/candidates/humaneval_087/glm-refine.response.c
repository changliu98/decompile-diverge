Coordinate** func0(int **lst, int lst_size, int *row_sizes, int x, int *return_size) {
    int j, i, count;
    Coordinate **out;

    // 0x320 bytes = 800 bytes = 200 pointers. 
    // This allocates space for an array of 200 Coordinate pointers.
    out = (Coordinate **)calloc(200, sizeof(Coordinate *)); 
    count = 0;

    // Iterate through each row of the 2D array
    for (i = 0; i < lst_size; ++i) {
        // Iterate backwards through the columns of the current row
        for (j = row_sizes[i] - 1; j >= 0; --j) {
            // If we find a match for x
            if (lst[i][j] == x) {
                // Allocate space for one Coordinate struct (8 bytes)
                out[count] = (Coordinate *)malloc(sizeof(Coordinate));
                out[count]->row = i;
                out[count]->col = j;
                count++;
            }
        }
    }

    *return_size = count;
    return out;
}