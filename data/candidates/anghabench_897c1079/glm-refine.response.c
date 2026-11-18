float __cdecl ramp_activate(float x)
{
    float result = x * 0.1f;
    
    if (x > 0.0f) {
        result += x;
    }
    
    return result;
}