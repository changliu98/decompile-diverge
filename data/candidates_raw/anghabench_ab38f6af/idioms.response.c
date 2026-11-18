static int get_max_val(int unipolar)
{
  if (unipolar)
    return 2 * (255 + 1);
  return 255 + 1;
}