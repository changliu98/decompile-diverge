int __cdecl matV3toV4(double *v3, double *v4)
{
    // Copy the x, y, and z components from the 3D vector
    v4[0] = v3[0];
    v4[1] = v3[1];
    v4[2] = v3[2];

    // Set the w component to 1.0 for homogeneous coordinates
    v4[3] = 1.0;

    return 0;
}