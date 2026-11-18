int __cdecl epindex_to_epnum(int epindex, int *epdir)
{
  int is_in_endpoint = epindex & 1; // Equivalent to epindex % 2, but faster

  if ( epdir )
    *epdir = is_in_endpoint;

  // Mathematically equivalent to (epindex + (epindex % 2)) / 2
  // This effectively maps: 0->0, 1->1, 2->1, 3->2, 4->2, 5->3...
  return (epindex + is_in_endpoint) >> 1; 
}