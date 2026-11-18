int stbhw__change_color(int color, int num_colors, int *weights) {
    int new_color;
    
    if (weights != NULL) {
        int sum = 0;
        int i;
        
        // First pass: calculate the sum of weights for all colors except the current one
        for (i = 0; i < num_colors; i++) {
            if (i != color) {
                sum += weights[i];
            }
        }
        
        // Generate a random number and take modulo the total sum of weights
        int r = (rand() >> 4) % sum;
        
        sum = 0;
        // Second pass: find the color corresponding to the random number
        for (i = 0; i < num_colors; i++) {
            if (i != color) {
                sum += weights[i];
                if (r < sum) {
                    break;
                }
            }
        }
        
        // If the loop finished without breaking (e.g., sum is 0 or r >= sum due to edge cases)
        if (i >= num_colors) {
            stbhw__assert_failure("stbhw_change_color", "i < num_colors", 681, "stbhw.c");
        }
        
        new_color = i;
    } else {
        // If no weights are provided, pick a random color different from the current one
        int offset = ((rand() >> 4) % (num_colors - 1)) + 1;
        new_color = (color + offset) % num_colors;
    }
    
    return new_color;
}