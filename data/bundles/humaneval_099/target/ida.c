int __cdecl func0(const char *value)
{
  double w; // [rsp+10h] [rbp-10h]

  w = atof(value);
  if ( w >= 0.0 )
    return (int)floor(w + 0.5);
  else
    return (int)ceil(w - 0.5);
}