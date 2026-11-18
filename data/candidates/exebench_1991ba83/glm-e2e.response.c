int obdRevConvert_52(float param1, int32_t *param2, void *param3, void *param4) {
    // Multiply param1 by constant at 0x2004, then divide by constant at 0x2008
    // Truncate to 32-bit integer and store in the address pointed to by param2
    *param2 = (int32_t)((param1 * 1.0f) / 1.0f); 
    
    return 1;
}