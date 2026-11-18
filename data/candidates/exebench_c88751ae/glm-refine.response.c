int __cdecl hmsra(int hours, int minutes, float seconds, double *degrees)
{
    // Convert time (hms) to decimal degrees
    *degrees = 15.0 * ((double)hours + (double)minutes / 60.0 + (double)seconds / 3600.0);
    
    // Return 1 (true) if the resulting degree is out of the valid [0, 360] range
    return *degrees < 0.0 || *degrees > 360.0;
}