void __cdecl atmcpy(const double *in, double *out)
{
    memcpy(out, in, 3 * sizeof(double));
}