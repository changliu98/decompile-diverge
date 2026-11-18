void __cdecl SN_set_residual(double *dparam, double res)
{
    // dparam[1] corresponds to the 2nd double (bytes 8-15) in the dparam array.
    dparam[1] = res;
}