void build_huffman_decoder(struct huff *h)
{
 int max_symbol, i, j, k, l;
 unsigned int x, y;

 for (i = 0; ; i++) {
  if (i >= 1024) break;
  h->decode[i] = -1;
 }
 if ((unsigned char)h[1].bits != 0) {
  max_symbol = h[128].symbol;
 } else {
  max_symbol = h[1].symbol;
 }
 if (max_symbol >= 32768) max_symbol = 32767;
 for (i = 0; ; i++) {
  if (i >= max_symbol) break;
  if ((unsigned char)h[1].bits > 10) {
   continue;
  }
  if ((unsigned char)h[1].bits != 0) {
   x = bit_reverse(h[128 + i].symbol);
  } else {
   x = h[1].symbol;
  }
  y = x;
  while (y < 1024) {
   h[y + 128] = i;
   y += (1 << (h[1].bits));
  }
 }
}