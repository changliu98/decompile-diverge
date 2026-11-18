int __cdecl vis5d_color_table_set_alpha(float *params, float alpha)
{
  if (alpha >= 0.0f)
  {
    // For valid alpha values, assign the same alpha to the min, max, and current alpha fields.
    params[3] = alpha;
    params[5] = alpha;
    params[6] = alpha;
  }
  else
  {
    // For invalid alpha values, set default min and max bounds.
    params[5] = 0.0f;
    params[6] = 255.0f;

    if (alpha == -2.0f)
    {
      params[2] = 0.0f;
      params[3] = -1.0f;
    }
    else
    {
      params[2] = 2.0f;
      params[3] = alpha; // Redundant assignment preserved to maintain original semantics.
    }
  }
  return 0;
}