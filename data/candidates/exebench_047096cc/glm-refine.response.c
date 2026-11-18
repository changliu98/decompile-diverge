void __cdecl endian_swap32bit(unsigned int *x)
{
  unsigned int val = *x;
  
  val = ((val & 0x000000FF) << 24) | 
        ((val & 0x0000FF00) << 8)  | 
        ((val & 0x00FF0000) >> 8)  | 
        ((val & 0xFF000000) >> 24);
        
  *x = val;
}