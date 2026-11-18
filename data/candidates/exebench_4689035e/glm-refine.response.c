void __cdecl rgb2hsv(double r, double g, double b, double *h, double *s, double *v)
{
  double hue = 0.0;
  double saturation = 0.0;
  
  // Find the minimum and maximum of the r, g, b components
  double min_val = fmin(fmin(r, g), b);
  double max_val = fmax(fmax(r, g), b);
  double delta = max_val - min_val;

  // Calculate Saturation
  if (max_val > 0.0)
    saturation = delta / max_val;

  // Calculate Hue
  if (saturation > 0.0)
  {
    double rc = (max_val - r) / delta;
    double gc = (max_val - g) / delta;
    double bc = (max_val - b) / delta;

    if (r == max_val)
    {
      hue = bc - gc;
    }
    else if (g == max_val)
    {
      hue = rc + 2.0 - bc;
    }
    else if (b == max_val)
    {
      hue = gc + 4.0 - rc;
    }

    hue = 60.0 * hue;
    if (hue < 0.0)
      hue += 360.0;
  }

  // Output normalized hue (0.0 - 1.0), saturation, and value
  *h = hue / 360.0;
  *v = max_val;
  *s = saturation;
}