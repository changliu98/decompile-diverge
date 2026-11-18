void __cdecl normalize_angle(double *angle)
{
    // Normalize the angle to be within the range [0.0, 2*PI)
    while (*angle > 2.0 * M_PI)
        *angle -= 2.0 * M_PI;
        
    while (*angle < 0.0)
        *angle += 2.0 * M_PI;
}