// Calculates the length of a single GL element (SG) for a given number of vertices n.
// Formula: ((n - 1) * 3 >> 1) + (n - 1 & 1) + 2
// This computes the number of bytes required to store n vertices in a specific packed format.
uint sgl_len(uint vertex_count)
{
  return ((vertex_count - 1) * 3 >> 1) + (vertex_count - 1 & 1) + 2;
}