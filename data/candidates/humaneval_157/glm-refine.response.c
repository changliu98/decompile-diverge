int __cdecl func0(float a, float b, float c)
{
    // Check if the plane is parallel to the X-axis
    if (fabsf(-a * a + b * b + c * c) >= 0.0001f)
    {
        // Check if the plane is parallel to the Y-axis
        if (fabsf(a * a - b * b + c * c) >= 0.0001f)
        {
            // Check if the plane is parallel to the Z-axis
            if (fabsf(a * a + b * b - c * c) >= 0.0001f)
                return 0; // Not parallel to any axis
        }
    }
    return 1; // Parallel to at least one axis
}