void __cdecl zywrle_calc_size(int *w, int *h, int level)
{
    // Calculate the alignment mask. 
    // For example, if level = 2, (1 << 2) - 1 = 3 (0b00000011).
    // Bitwise ANDing with the inverse of this mask (~3 = 0b11111100) 
    // effectively rounds the dimension down to the nearest multiple of 4.
    int align_mask = (1 << level) - 1;

    *w &= ~align_mask;
    *h &= ~align_mask;
}