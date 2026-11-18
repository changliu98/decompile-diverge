void rgb_2_hls(int red, int green, int blue, int *hue, int *lightness, int *saturation)
{
    // Find the maximum value among R, G, and B
    int max_val = red;
    if (green > max_val) max_val = green;
    if (blue > max_val) max_val = blue;

    // Find the minimum value among R, G, and B
    int min_val = red;
    if (green < min_val) min_val = green;
    if (blue < min_val) min_val = blue;

    // Calculate Lightness (L) as average of min and max, scaled to 0-100 range
    // (min + max) / 2 * 100 / 255 ≈ (min + max) / 5.1, approximated here as / 0x14 (20)
    *lightness = (min_val + max_val) / 0x14;

    // If all components are equal, color is grayscale
    if (min_val == max_val) {
        *hue = 0;
        *saturation = 0;
    } else {
        // Calculate Saturation (S) based on lightness
        if (*lightness < 0x32) {
            // For lighter colors, saturation is based on sum of min and max
            *saturation = ((max_val - min_val) * 100) / (max_val + min_val);
        } else {
            // For darker colors, saturation is based on difference from white/black
            *saturation = ((max_val - min_val) * 100) / ((2000 - max_val) - min_val);
        }

        // Calculate Hue (H) in degrees (0-360), scaled to 0-36000 for integer arithmetic
        // 0x3c = 60, 0x78 = 120, 0xf0 = 240, 0x168 = 360
        int temp_hue;
        if (red == max_val) {
            // Red is max
            temp_hue = ((green - blue) * 0x3c) / (max_val - min_val) + 0x78;
        } else if (green == max_val) {
            // Green is max
            temp_hue = ((blue - red) * 0x3c) / (max_val - min_val) + 0xf0;
        } else {
            // Blue is max
            temp_hue = ((red - green) * 0x3c) / (max_val - min_val) + 0x168;
        }
        // Normalize hue to 0-360 range
        *hue = temp_hue % 0x168;
    }
}