float __cdecl spline_cubic_val(int n, float *t, float tval, float *y, float *ypp)
{
    int ival;
    int i;
    float h;
    float dt;

    // Find the interval index `ival` such that t[ival] <= tval < t[ival+1]
    ival = n - 2;
    for (i = 0; i < n - 1; ++i)
    {
        if (t[i + 1] > tval)
        {
            ival = i;
            break;
        }
    }

    // Calculate the local distance `dt` and the interval width `h`
    dt = tval - t[ival];
    h = t[ival + 1] - t[ival];

    // Evaluate the cubic spline polynomial using the second derivatives (ypp)
    float a = ypp[ival] * 0.5f + dt * ((ypp[ival + 1] - ypp[ival]) / (6.0f * h));
    float b = -(ypp[ival + 1] / 6.0f + ypp[ival] / 3.0f) * h;
    float c = (y[ival + 1] - y[ival]) / h;

    return dt * (dt * a + b + c) + y[ival];
}