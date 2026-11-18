int vis5d_color_table_set_alpha( float params[], float alpha )
{
   params[3] = alpha;
   if (alpha<0) {
      params[5] = 0;
      params[6] = 255;

      if (alpha == -2.0){
         params[2] = 0.0;
         params[3] = -1.0;
      }
      else{
         params[2] = 2.0;
      }
   }
   else {
      params[5] = alpha;
      params[6] = alpha;
      params[3] = alpha;
   }
   return 0;
}