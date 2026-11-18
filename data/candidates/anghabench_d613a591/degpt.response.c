// Helper function to calculate one component of RGB from HSL/HSV values
// H: Hue value (normalized, expected to be in range [0, 1))
// M1: First intermediate color value
// M2: Second intermediate color value
// Returns the calculated RGB component value
float _RGB(float hue, float min_val, float max_val)
{
    // Normalize H to be within the range [0, 1)
    // If H is negative, wrap it around by adding the full cycle value
    if (hue < 0.0f) {
        hue += one; // DAT_00102008 represents 1.0f (full cycle)
    } else if (hue >= one) {
        // If H is >= 1.0, subtract the full cycle to bring it back into range
        hue -= one;
    }

    // Determine the RGB component based on the normalized H value
    // Thresholds define different regions for color interpolation
    if (hue >= one_third) { // H >= 1/3 (approx 0.3333)
        if (hue < one_half) { // H < 1/2 (approx 0.5)
            // In the range [1/3, 1/2), return M2
            return max_val;
        } else if (hue < two_thirds) { // H < 2/3 (approx 0.6667)
            // In the range [1/2, 2/3), linearly interpolate between M1 and M2
            // Formula: M1 + (M2 - M1) * (2/3 - H) / (1/6)
            // DAT_00102038 is 2/3, DAT_00102010 is 1/6 (approx 0.1667)
            return (float)((double)min_val + (double)((max_val - min_val) * (two_thirds - hue)) / one_sixth);
        } else {
            // In the range [2/3, 1), return M1
            return min_val;
        }
    } else {
        // In the range [0, 1/3), linearly interpolate between M1 and M2
        // Formula: M1 + (M2 - M1) * H / (1/6)
        return (float)((double)min_val + (double)((max_val - min_val) * hue) / one_sixth);
    }
}