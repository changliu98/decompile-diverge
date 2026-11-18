float __cdecl map(int x, int in_min, int in_max, float out_min, float out_max)
{
    float in_range = in_max - in_min;
    float out_range = out_max - out_min;
    float progress = (x - in_min) / in_range;
    
    return out_min + (progress * out_range);
}