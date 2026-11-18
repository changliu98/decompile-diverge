double __cdecl func0(double r, double h)
{
  double slant_height = sqrt(r * r + h * h);
  return M_PI * r * slant_height;
}