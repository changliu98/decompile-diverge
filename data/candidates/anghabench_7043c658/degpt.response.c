// Calculates the maximum speed from an array of speeds.
// If no valid speeds are found (all are 0), returns the default speed.
unsigned_short calc_speed(unsigned_short *speeds, int count, unsigned_short default_speed)
{
    unsigned_short max_speed = 0;
    for (int index = 0; index < count; index++) {
        // Find the maximum speed in the array
        if (max_speed < speeds[index]) {
            max_speed = speeds[index];
        }
    }
    // If no speed was found, use the default value
    if (max_speed == 0) {
        max_speed = default_speed;
    }
    return max_speed;
}