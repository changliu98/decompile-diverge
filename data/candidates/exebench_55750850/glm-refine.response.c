void __cdecl rotate_point(float *point)
{
    // Cache the original coordinates
    float x = point[0];
    float y = point[1];
    float z = point[2];

    // Step 1: Convert Z to radians (though mathematically odd, preserved from original)
    float z_rad = z * 0.0174524f;

    // Step 2: Rotate 1 degree around the Y-axis
    // y' = y * cos(1°) - z_rad * sin(1°)
    float y_rotated = (y * 0.99984771f) - z_rad;

    // z_intermediate = y * sin(1°) + z_rad * cos(1°)
    float z_intermediate = (y * 0.0174524f) + (z * 0.99984771f);

    // Step 3: Rotate 4 degrees around the X-axis
    // x' = x * cos(4°) - z_intermediate * sin(4°)
    float x_rotated = (x * 0.99756408f) - (z_intermediate * 0.069756471f);

    // z'' = x * sin(4°) + z_intermediate * cos(4°)
    float z_final = (x * 0.069756471f) + (z_intermediate * 0.99756408f);

    // Write the transformed coordinates back to the pointer
    point[0] = x_rotated;
    point[1] = y_rotated;
    point[2] = z_final;
}