float KBND_REPLICATE(const float *base, int width, int height, int x, int y) {
    // Clamp x to the valid range [0, width - 1]
    if (x < 0) {
        x = 0;
    } else if (x >= width) {
        x = width - 1;
    }
    
    // Clamp y to the valid range [0, height - 1]
    if (y < 0) {
        y = 0;
    } else if (y >= height) {
        y = height - 1;
    }
    
    // Return the clamped pixel value from the 2D array
    return base[y * width + x];
}