void Float_Overlay_To_Network_Order(union Float_Overlay *f)
{
   union Float_Overlay f_temp;
   int32_t *i;

   i = (int32_t *)f;
   f_temp.i = *i;
   *i = htonl(f_temp.i);
}