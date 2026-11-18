int __cdecl smacker_decode_tree(BitstreamContext *bc, HuffContext *hc, uint32_t prefix, int length)
{
  int r; // [rsp+Ch] [rbp-24h]
  int lengthb; // [rsp+10h] [rbp-20h]

  if ( bitstream_read_bit(bc) )
  {
    lengthb = length + 1;
    r = smacker_decode_tree(bc, hc, prefix, lengthb);
    if ( r )
      return r;
    else
      return smacker_decode_tree(bc, hc, (1 << (lengthb - 1)) | prefix, lengthb);
  }
  else if ( hc->current < 256 )
  {
    if ( length )
    {
      hc->bits[hc->current] = prefix;
      hc->lengths[hc->current] = length;
    }
    else
    {
      hc->bits[hc->current] = 0;
      hc->lengths[hc->current] = 0;
    }
    hc->values[hc->current++] = bitstream_read(bc, 8u);
    if ( hc->maxlength < length )
      hc->maxlength = length;
    return 0;
  }
  else
  {
    av_log(0LL, 16, "Tree size exceeded!\n");
    return -1094995529;
  }
}