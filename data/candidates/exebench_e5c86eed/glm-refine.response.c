00390625f

int __cdecl SeekPoint(unsigned __int8 *TOC, int file_bytes, float percent)
{
    float clamped_percent;
    int index;

    // Clamp the percentage between 0.0 and 100.0
    clamped_percent = percent;
    if (clamped_percent < 0.0f)
        clamped_percent = 0.0f;
    if (clamped_percent > 100.0f)
        clamped_percent = 100.0f;

    // Determine the integer index into the TOC array
    index = (int)clamped_percent;
    if (index > 99)
        index = 99;

    // Retrieve the start and end points from the TOC.
    // If the index is at the very end (99), the end point is implicitly 256.
    float start_val = (float)TOC[index];
    float end_val   = (index >= 99) ? 256.0f : (float)TOC[index + 1];

    // Calculate the fractional progress between the current and next TOC entries
    float fraction  = clamped_percent - (float)index;
    float interpolated_val = start_val + (end_val - start_val) * fraction;

    // Scale the 0-255/256 range value to the actual file byte size
    return (int)(interpolated_val * INV_256 * (float)file_bytes);
}