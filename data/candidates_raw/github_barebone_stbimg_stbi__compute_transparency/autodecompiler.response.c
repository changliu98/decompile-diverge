int stbi__compute_transparency(stbi__png *z, stbi_uc tc[3], int out_n)
{
   stbi__context *s = z->s;
   unsigned x,y, pixel_count = s->img_x * s->img_y;
   stbi_uc *p = z->out;



   int has_alpha = 0;

   int out_alpha = 0xff;
   int alpha_threshold = 0;
   switch (out_n) {
      case 2: has_alpha = 1; out_alpha = 0; alpha_threshold = 0; break;
      case 4: has_alpha = 1; out_alpha = 0; alpha_threshold = 0; break;
      default: ___assert_fail("out_n == 2 || out_n == 4","./func.c",4914,"int stbi__compute_transparency(stbi__png *, stbi_uc *, int)"); break;
   }

   if (has_alpha) {

      for (x=0; x < pixel_count; ++x) {
         p[1] = (p[0] == tc[0] ? 0 : 255);
         p += 2;
      }
   } else {

      for (x=0; x < pixel_count; ++x) {
         if (p[0] == tc[0] && p[1] == tc[1] && p[2] == tc[2])
            p[3] = 0;
         p += 4;
      }
   }
   return 1;
}