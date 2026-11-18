void swap(struct Grid *grid) {
    int *min_ptr = &grid->data[0];
    int *max_ptr = &grid->data[0];
    
    // Find the minimum and maximum elements in the 5x5 grid
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (*min_ptr > grid->data[i * 5 + j]) {
                min_ptr = &grid->data[i * 5 + j];
            }
            if (*max_ptr < grid->data[i * 5 + j]) {
                max_ptr = &grid->data[i * 5 + j];
            }
        }
    }
    
    // Swap the minimum element with the top-left corner (data[0])
    int temp = grid->data[0];
    grid->data[0] = *min_ptr;
    *min_ptr = temp;
    
    // Swap the maximum element with the top-right corner (data[1])
    int *max_ptr2 = &grid->data[1];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 0 && j == 0) continue;
            if (*max_ptr2 > grid->data[i * 5 + j]) {
                max_ptr2 = &grid->data[i * 5 + j];
            }
        }
    }
    
    int temp2 = *max_ptr2;
    *max_ptr2 = grid->corners[0];
    grid->corners[0] = temp2;
    
    // Find the minimum element excluding the top row corners
    int *min_ptr2 = &grid->data[1];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == 4)) continue;
            if (*min_ptr2 > grid->data[i * 5 + j]) {
                min_ptr2 = &grid->data[i * 5 + j];
            }
        }
    }
    
    // Swap the found minimum with the bottom-left corner (corners[1])
    int temp3 = *min_ptr2;
    *min_ptr2 = grid->corners[1];
    grid->corners[1] = temp3;
    
    // Find the minimum element excluding all corners
    int *min_ptr3 = &grid->data[1];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == 4) || (i == 4 && j == 0)) continue;
            if (*min_ptr3 > grid->data[i * 5 + j]) {
                min_ptr3 = &grid->data[i * 5 + j];
            }
        }
    }
    
    // Swap the found minimum with the bottom-right corner (corners[2])
    int temp4 = *min_ptr3;
    *min_ptr3 = grid->corners[2];
    grid->corners[2] = temp4;
    
    // Find the minimum element excluding all corners
    int *min_ptr4 = &grid->data[1];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == 4) || (i == 4 && j == 0) || (i == 4 && j == 4)) continue;
            if (*min_ptr4 > grid->data[i * 5 + j]) {
                min_ptr4 = &grid->data[i * 5 + j];
            }
        }
    }
    
    // Swap the found minimum with the center element (center)
    int temp5 = *min_ptr4;
    *min_ptr4 = grid->center;
    grid->center = temp5;
}