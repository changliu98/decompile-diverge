int new_height(int old_width, int new_width, int old_height)
{
  return (int)(old_height * (new_width / (double)old_width) + 0.5);
}