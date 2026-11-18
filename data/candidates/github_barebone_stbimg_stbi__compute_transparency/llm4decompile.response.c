int stbi__compute_transparency(stbi__png *z, stbi_uc tc[3], int out_n)
{
   stbi_uc *p = z->out;
   stbi__uint32 i;
   stbi__uint32 pixel_count = z->s->img_x * z->s->img_y;
   (void)sizeof(stbi__png);
   ((out_n == 2 || out_n == 4) ? (void)0 : __assert_fail("out_n == 2 || out_n == 4", "func.c", 4914, "int stbi__compute_transparency(stbi__png *, stbi_uc *, int)"));
   if (out_n == 2) {
      for (i = 0; i < pixel_count; ++i) {
         p[1] = (stbi_uc)(255 * (p[0] != tc[0] || p[1] != tc[1] || p[2] != tc[2]));
         p += 2;
      }
   } else {
      for (i = 0; i < pixel_count; ++i) {
         if (p[0] == tc[0] && p[1] == tc[1] && p[2] == tc[2])
            p[3] = 0;
         p += 4;
      }
   }
   return 1;
}