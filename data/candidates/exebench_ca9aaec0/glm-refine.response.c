void __cdecl cross(double *va, double *vb, double *vc)
{
    // vc = va x vb
    vc[0] = (va[1] * vb[2]) - (va[2] * vb[1]); // X-axis
    vc[1] = (va[2] * vb[0]) - (va[0] * vb[2]); // Y-axis
    vc[2] = (va[0] * vb[1]) - (va[1] * vb[0]); // Z-axis
}