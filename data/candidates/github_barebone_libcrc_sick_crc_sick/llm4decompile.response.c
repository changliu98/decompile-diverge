uint16_t crc_sick(const unsigned char *input_str, size_t num_bytes)
{




 uint16_t crc;
 uint16_t short_c;
 uint16_t short_p;
 size_t a;

 crc = 0x0000;
 short_p = 0x0000;

 if (input_str != NULL)
 {
  for (a = 0; a < num_bytes; a++)
  {

   if (crc & 0x8000)
   {
    crc = (crc << 1) ^ 0x8005;
   }
   else
   {
    crc = crc << 1;
   }

   short_c = 0x00ff & (uint16_t) input_str[a];
   crc &= 0xffff;
   crc ^= (short_c | short_p);
   short_p = input_str[a] << 8;
  }
 }

 return ((((crc & 0xff00) >> 8) | ((crc & 0x00ff) << 8)));
}