void __cdecl geom_matvec4d(const double m[4][4], const double u[4], double v[4])
{
    // Row 0
    v[0] = m[0][0] * u[0] + m[1][0] * u[1] + m[2][0] * u[2] + m[3][0] * u[3];
    
    // Row 1
    v[1] = m[0][1] * u[0] + m[1][1] * u[1] + m[2][1] * u[2] + m[3][1] * u[3];
    
    // Row 2
    v[2] = m[0][2] * u[0] + m[1][2] * u[1] + m[2][2] * u[2] + m[3][2] * u[3];
    
    // Row 3
    v[3] = m[0][3] * u[0] + m[1][3] * u[1] + m[2][3] * u[2] + m[3][3] * u[3];
}