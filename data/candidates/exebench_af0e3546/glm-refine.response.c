Optimized and annotated for reverse engineering
void __cdecl set_mac(unsigned char *setto, const unsigned char *from)
{
  // The function copies exactly 6 bytes, which corresponds to the size of a standard MAC address.
  // The loop has been replaced with a direct memory copy to make the intent clearer.
  *(unsigned int *)setto = *(const unsigned int *)from;
  *(unsigned short *)(setto + 4) = *(const unsigned short *)(from + 4);
}