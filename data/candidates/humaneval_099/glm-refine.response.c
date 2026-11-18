int __cdecl func0(const char *value)
{
  double num = atof(value);
  
  if (num >= 0.0)
    return (int)floor(num + 0.5);
  else
    return (int)ceil(num - 0.5);
}