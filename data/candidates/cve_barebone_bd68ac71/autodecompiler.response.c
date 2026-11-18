static u8 BS_ReadByte(GF_BitStream *bs)
{
 char byte;
 if (!bs->error) {
  if (bs->position >= bs->size) {
   if (bs->on_error) bs->on_error(bs->private, bs);
   if (!bs->error_count) bs->error_count = 1;
   byte = 0;
  } else {
   byte = bs->data[bs->position++];
   if (bs->eag_read) {
    if ((bs->eag_state == 2) && (byte == 3) && (bs->position < bs->size)) {
     if (bs->data[bs->position] < 5) {
      bs->eag_state = 0;
      byte = bs->data[bs->position++];
     } else {
      gf_bs_seek(bs, bs->position);
     }
    } else if (byte==0) bs->eag_state++;
    else bs->eag_state=0;
   } else {
    return byte;
   }
  }
 } else {
  int eos;
  if (bs->cache_size) bs_flush_write_cache(bs);
  eos = gf_feof(bs->io);
  if (eos && !bs->error_on_eof) goto exit;
  byte = 0;
  do { ((void) (bs->position<=bs->size ? 0 : ___assert_fail ("bs->position<=bs->size", "harness.c", 182, "u8 BS_ReadByte(GF_BitStream *)"))); } while(0);
  byte = gf_bs_load_byte(bs, &eos);
  if (eos) goto exit;
  if (bs->eag_read) {
   if ((bs->eag_state == 2) && (byte == 3) && (bs->position < bs->size)) {
    char next = gf_bs_load_byte(bs, &eos);
    if (!eos && (next < 5)) {
     bs->eag_state = 0;
     byte = next;
     bs->position++;
    } else {
     gf_bs_seek(bs, bs->position);
    }
   } else if (byte==0) bs->eag_state++;
   else bs->eag_state=0;
  } else {
   return byte;
  }
 }

exit:
 if (bs->on_error) bs->on_error(bs->private, bs);
 if (!bs->error_count) bs->error_count = 1;
 do { ((void) (bs->position <= 1+bs->size ? 0 : ___assert_fail ("bs->position <= 1+bs->size", "harness.c", 212, "u8 BS_ReadByte(GF_BitStream *)"))); } while(0);
 return 0;
}