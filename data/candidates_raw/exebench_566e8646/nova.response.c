static void func0(double *out, const double *in, const double *scale)
{
    double x = in[0];
    double y = in[1];
    double z = in[2];
    double x2 = x * x;
    double y2 = y * y;
    double z2 = z * z;
    double xy = x * y;
    double xz = x * z;
    double yz = y * z;

    out[0] = (x2 + y2) * scale[0] + (xy * 2.0 + z2) * scale[1];
    out[1] = (xy * 2.0 + z2) * scale[2] + (y2 + z2) * scale[3];
    out[2] = (xy * 2.0 + z2) * scale[4] + (x2 + z2) * scale[5];
    out[3] = (xy * 2.0 + z2) * scale[6] + (x2 + y2) * scale[7];
}