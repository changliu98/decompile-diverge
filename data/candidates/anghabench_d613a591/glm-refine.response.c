#include <math.h>

float __cdecl RGB(float H, float M1, float M2)
{
    // Wrap H into the range [0, 360)
    H = fmod(H, 360.0f);
    if (H < 0.0f) {
        H += 360.0f;
    }

    // Calculate the color component based on the hue sector
    if (H < 60.0f) {
        return M1 + (M2 - M1) * H / 60.0f;
    } else if (H < 180.0f) {
        return M2;
    } else if (H < 240.0f) {
        return M1 + (M2 - M1) * (240.0f - H) / 60.0f;
    } else {
        return M1;
    }
}