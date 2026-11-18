void __cdecl atmcpy(const double *in, double *out)
{
  *out = *in;
  out[1] = in[1];
  out[2] = in[2];
}