static int ad7192_get_temp_scale(int unipolar)
{
  if (unipolar)
    return 2 * (255 + 1);
  return 255 + 1;
}