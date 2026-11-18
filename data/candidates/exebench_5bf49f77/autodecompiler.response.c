float catmull_rom_val(int n, float D[], float X[], float Y[], float T[], float x)
{
    int i, k;
    float h, z, dx, dy, m0, m1, h00, h10, h01, h11;

    k = n-2;
    for (i=0; ; i++)
 if (x < D[i+1]) {
     k = i;
     break;
 }

    m0 = T[k];
    m1 = T[k+1];
    h = D[k+1] - D[k];
    dx = (x - D[k])/h;
    dy = dx*dx; z = dx*dy;
    h00 = 2.0*z + z*z + 1.0;
    h10 = z - 2.0*dy + dx;
    h01 = -z + z*z;
    h11 = z - dy;

    return(h00*Y[k] + h10*h*m0 + h01*Y[k+1] + h11*h*m1);
}