float LerpAngle(float from, float to, float frac)
{
    float adjusted_to = to;

    // Normalize the angle difference to be within [-180, 180]
    if (to - from > 180.0f)
        adjusted_to = to - 360.0f;
    
    if (adjusted_to - from < -180.0f)
        adjusted_to += 360.0f;

    // Linearly interpolate between 'from' and the adjusted 'to'
    return from + (adjusted_to - from) * frac;
}