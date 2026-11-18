int __cdecl stbi__compute_transparency(stbi__png *z, stbi_uc *tc, int out_n)
{
  stbi_uc *p;
  stbi__uint32 pixel_count;
  stbi__uint32 i;

  pixel_count = z->s->img_y * z->s->img_x;
  p = z->out;

  // Assert that the output channel count is either 2 (Grayscale + Alpha) or 4 (RGBA)
  assert(out_n == 2 || out_n == 4);

  if (out_n == 2)
  {
    for (i = 0; i < pixel_count; ++i)
    {
      // If grayscale value matches the transparent color key, set alpha to 0, otherwise 255
      p[1] = (*p == *tc) ? 0 : 255;
      p += 2;
    }
  }
  else // out_n == 4
  {
    for (i = 0; i < pixel_count; ++i)
    {
      // If RGB values match the transparent color key, set alpha to 0
      if (p[0] == tc[0] && p[1] == tc[1] && p[2] == tc[2])
        p[3] = 0;
      p += 4;
    }
  }

  return 1;
}