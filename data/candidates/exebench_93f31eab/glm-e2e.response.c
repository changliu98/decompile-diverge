int obdRevConvert_10(float val, int* out1, int* out2, int* out3) {
    val *= 256.0f; // Multiplied by a constant loaded from memory (0x100)
    
    int temp = (int)val;
    *out1 = temp / 256;
    *out2 = temp % 256;
    
    return 2;
}