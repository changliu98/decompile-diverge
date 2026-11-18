int stbi__compute_transparency(stbi__png *z,stbi_uc *tc,int out_n)

{
  stbi_uc sVar1;
  uint uVar2;
  stbi_uc *p;
  stbi__uint32 pixel_count;
  stbi__uint32 i;
  stbi__context *s;
  int out_n_local;
  stbi_uc *tc_local;
  stbi__png *z_local;
  
  uVar2 = z->s->img_x * z->s->img_y;
  p = z->out;
  if ((out_n != 2) && (out_n != 4)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("out_n == 2 || out_n == 4","func.c",0x1332,
                  "int stbi__compute_transparency(stbi__png *, stbi_uc *, int)");
  }
  if (out_n == 2) {
    for (i = 0; i < uVar2; i = i + 1) {
      sVar1 = 0xff;
      if (*p == *tc) {
        sVar1 = '\0';
      }
      p[1] = sVar1;
      p = p + 2;
    }
  }
  else {
    for (i = 0; i < uVar2; i = i + 1) {
      if (((*p == *tc) && (p[1] == tc[1])) && (p[2] == tc[2])) {
        p[3] = '\0';
      }
      p = p + 4;
    }
  }
  return 1;
}