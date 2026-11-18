unsigned int __cdecl swizzle(unsigned int in, unsigned int limit)
{
  unsigned int out = 0;
  
  while (limit)
  {
    // Extract the lowest bit of 'in' and append it to 'out'
    out = (out << 1) | (in & 1);
    
    // Shift the inputs for the next iteration
    in >>= 1;
    limit >>= 1;
  }
  
  return out;
}