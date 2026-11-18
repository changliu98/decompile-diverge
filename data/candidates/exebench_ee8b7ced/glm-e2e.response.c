void get_neighbors(int *neighbors, int width, int index, int height) {
    int col = index % width;
    int row = (index - col) / width;
    
    int up = row - 1;
    if (up < 0) {
        up = height + up; // Wrap around to the bottom
    }
    
    int left = col - 1;
    if (left < 0) {
        left = width + left; // Wrap around to the right
    }
    
    int down = (row + 1) % height;
    int right = (col + 1) % width;
    
    // Store the 1D indices of the neighbors into the array
    neighbors[0] = up * width + col;
    neighbors[1] = down * width + col;
    neighbors[2] = row * width + left;
    neighbors[3] = row * width + right;
}