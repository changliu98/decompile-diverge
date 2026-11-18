int stb_div_eucl(int v1, int v2)
{
   int q,r;
   #ifdef C_INTEGER_DIVISION_TRUNCATES
   q = v1/v2;
   r = v1%v2;
   #else
   // handle every quadrant separately, since we can't rely on q and r flor
   if (v1 >= 0)
      if (v2 >= 0)
         return stb__div(v1,v2);
      else if (v2 != INT_MIN)
         q = -stb__div(v1,-v2), r = stb__mod(v1,-v2);
      else
         q = 0, r = v1;
   else if (v1 != INT_MIN)
      if (v2 >= 0)
         q = -stb__div(-v1,v2), r = -stb__mod(-v1,v2);
      else if (v2 != INT_MIN)
         q = stb__div(-v1,-v2), r = -stb__mod(-v1,-v2);
      else // if v2 is INT_MIN, then we can't use -v2, but we can't divide by v2
         q = 1, r = v1-q*v2;
   else // if v1 is INT_MIN, we have to move away from overflow place
      if (v2 >= 0)
         q = -stb__div(-(v1+v2),v2)-1, r = -stb__mod(-(v1+v2),v2);
      else if (v2 != INT_MIN)
         q = stb__div(-(v1-v2),-v2)+1, r = -stb__mod(-(v1-v2),-v2);
      else // for INT_MIN / INT_MIN, we need to be extra-careful to avoid overflow
         q = 1, r = 0;
   #endif
   if (r >= 0)
      return q;
   else
      return q + (v2 > 0 ? -1 : 1);
}