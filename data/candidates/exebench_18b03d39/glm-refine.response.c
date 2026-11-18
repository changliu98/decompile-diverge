void __cdecl si_swapl(int *d)
{
  // Swap the 4 bytes of the integer to convert between little-endian and big-endian
  *d = ((*d & 0x000000FF) << 24) | 
       ((*d & 0x0000FF00) << 8)  | 
       ((*d & 0x00FF0000) >> 8)  | 
       ((*d & 0xFF000000) >> 24);
}