int __cdecl stbi__compute_transparency(stbi__png *z, stbi_uc *tc, int out_n)
{
  char v3; // al
  stbi_uc *p; // [rsp+0h] [rbp-30h]
  stbi__uint32 pixel_count; // [rsp+8h] [rbp-28h]
  stbi__uint32 i; // [rsp+Ch] [rbp-24h]
  stbi__uint32 ia; // [rsp+Ch] [rbp-24h]

  pixel_count = z->s->img_y * z->s->img_x;
  p = z->out;
  if ( out_n != 2 && out_n != 4 )
    _assert_fail(
      "out_n == 2 || out_n == 4",
      "func.c",
      0x1332u,
      "int stbi__compute_transparency(stbi__png *, stbi_uc *, int)");
  if ( out_n == 2 )
  {
    for ( i = 0; i < pixel_count; ++i )
    {
      v3 = -1;
      if ( *p == *tc )
        v3 = 0;
      p[1] = v3;
      p += 2;
    }
  }
  else
  {
    for ( ia = 0; ia < pixel_count; ++ia )
    {
      if ( *p == *tc && p[1] == tc[1] && p[2] == tc[2] )
        p[3] = 0;
      p += 4;
    }
  }
  return 1;
}