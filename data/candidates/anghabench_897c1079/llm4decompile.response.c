float ramp_activate(float x)
{
    return (x * (x > 0) + x * 0.1);
}