static void faad_resetbits(struct bitstream *bs, int bits)
{
 int words = bits >> 5;
 int remainder = bits & 31;

 bs->bytes_left = bs->size - (words << 2);
 if (bs->bytes_left >= sizeof(unsigned int)) {
  unsigned int word = getdword(bs->data + words);
  bs->bytes_left -= sizeof(unsigned int);
  bs->word0 = word;
 } else {
  unsigned int word = getdword_n(bs->data + words, bs->bytes_left);
  bs->bytes_left = 0;
  bs->word0 = word;
 }

 if (bs->bytes_left >= sizeof(unsigned int)) {
  unsigned int word = getdword(bs->data + words + 1);
  bs->bytes_left -= sizeof(unsigned int);
  bs->word1 = word;
 } else {
  unsigned int word = getdword_n(bs->data + words + 1, bs->bytes_left);
  bs->bytes_left = 0;
  bs->word1 = word;
 }

 bs->bit_left = 32 - remainder;
 bs->next_byte = bs->data + words + 2;
 bs->done = 0;
}