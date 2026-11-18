// Calculates the length of a Xiph-encoded integer.
// The formula computes the number of bytes required to store 'l'
// using a variable-length encoding scheme where each byte stores 7 bits
// of data, plus one byte for the length indicator.
// Specifically: (l / 0xff) + 1 + l simplifies the byte count calculation
// for this specific encoding logic.
int xiph_len(int length)
{
  return length / 0xff + 1 + length;
}