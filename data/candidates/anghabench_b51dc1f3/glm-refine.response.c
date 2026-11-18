int get_sorting_mode(int c)
{
    // Cast to unsigned to correctly handle characters with the high bit set 
    // (e.g., extended ASCII) without triggering the < 0x80 condition.
    if ((unsigned int)c < 0x80) {
        return tbl_sorting_mode[c];
    }
    
    return -1;
}