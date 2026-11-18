// base91 encodes a 16-bit integer into two printable ASCII characters.
// It divides the integer by 91, storing the quotient and remainder 
// (each mapped to the printable ASCII range starting at 33 '!') in the buffer.
// Returns a pointer to the memory location immediately after the written characters.
char *__cdecl base91_encode_pair(char *p, int i)
{
  p[0] = (char)(i / 91 + 33); // Quotient mapped to ASCII 33-124
  p[1] = (char)(i % 91 + 33); // Remainder mapped to ASCII 33-124
  return p + 2;
}