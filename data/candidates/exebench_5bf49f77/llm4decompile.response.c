float catmull_rom_val(int n, float *x, float xval, float *y, float *tangents)
{
    int i;
    int i_low = n-2;
    for(i=0; i<n-2; i++)
    {
        if(xval < x[i+1])
        {
            i_low = i;
            break;
        }
    }

    float x_diff = x[i_low+1] - x[i_low];
    float t = (xval - x[i_low]) / x_diff;
    float t2 = t*t;
    float t3 = t2*t;


    float a0 = -0.5*t3 + t2 - 0.5*t;
    float a1 = 1.5*t3 - 2.5*t2 + 2.0*t;
    float a2 = -1.5*t3 + 2.0*t2 + 0.5*t;
    float a3 = 0.5*t3 - 0.5*t2;

    return a0*y[i_low] + a1*y[i_low+1] + a2*x_diff*tangents[i_low] +
            a3*x_diff*tangents[i_low+1];
}