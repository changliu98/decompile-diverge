uint16_t calc_speed(uint16_t *speeds, int32_t count, uint16_t default_speed) {
    uint16_t max_speed = 0;
    
    // Find the maximum speed in the array
    for (int i = 0; i < count; i++) {
        if (max_speed < speeds[i]) {
            max_speed = speeds[i];
        }
    }
    
    // If no speeds were found (or max is 0), return the default speed
    if (max_speed == 0) {
        return default_speed;
    }
    
    return max_speed;
}