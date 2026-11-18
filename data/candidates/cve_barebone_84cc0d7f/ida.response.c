void __cdecl faad_resetbits(bitfile *ld, int bits)
{
  int words; // [rsp+Ch] [rbp-14h]
  uint32_t tmp; // [rsp+10h] [rbp-10h]
  uint32_t tmpa; // [rsp+10h] [rbp-10h]

  words = bits >> 5;
  ld->bytes_left = ld->buffer_size - 4 * (bits >> 5);
  if ( ld->bytes_left < 4 )
  {
    tmp = getdword_n(&ld->start[words], ld->bytes_left);
    ld->bytes_left = 0;
  }
  else
  {
    tmp = getdword(&ld->start[words]);
    ld->bytes_left -= 4;
  }
  ld->bufa = tmp;
  if ( ld->bytes_left < 4 )
  {
    tmpa = getdword_n(&ld->start[words + 1], ld->bytes_left);
    ld->bytes_left = 0;
  }
  else
  {
    tmpa = getdword(&ld->start[words + 1]);
    ld->bytes_left -= 4;
  }
  ld->bufb = tmpa;
  ld->bits_left = 32 - (bits & 0x1F);
  ld->tail = &ld->start[words + 2];
  ld->error = 0;
}