void stb_linear_controller(float *curpos, float target_pos, float acc, float deacc, float dt)
{
   float sign = 1;
   if (*curpos == target_pos) return;
   if (*curpos > target_pos) {
      *curpos = -*curpos;
      target_pos = -target_pos;
      sign = -1;
   }

   if (*curpos < 0) {
      float p = *curpos + deacc * dt;
      if (p < 0) {
         dt = 0;
      } else {
         dt -= *curpos / deacc;
         if (dt < 0) dt = 0;
         *curpos = 0;
      }
   }

   *curpos += acc * dt;
   if (*curpos > target_pos)
      *curpos = target_pos;
   *curpos *= sign;
}