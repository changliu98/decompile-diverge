void set_elmt(int *dst, const int *src)
{
  // The function signature accepts two pointers, but the second pointer ('src') 
  // is completely unused. The compiler has optimized away any operations 
  // involving 'src', resulting in a dead parameter.
  
  // Unconditionally sets the destination integer to 3.
  *dst = 3;
}