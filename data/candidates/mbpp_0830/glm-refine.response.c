double __cdecl func0(double a, int digits)
{
  double scale_down = pow(10.0, (double)-digits);
  double rounded_up = ceil(a / scale_down) * scale_down;
  
  double scale_up = pow(10.0, (double)digits);
  double scaled = round(rounded_up * scale_up);
  
  return scaled / scale_up;
}