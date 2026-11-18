void __cdecl WordToHex(unsigned int Number, char *String)
{
    unsigned int Value = Number;

    // Process 4 nibbles (4 bits each) to form a 4-character hex string
    for (int i = 3; i >= 0; --i)
    {
        unsigned int Nibble = Value & 0xF;
        
        // Convert nibble to its ASCII representation
        if (Nibble >= 0xA)
            String[i] = (char)(Nibble + 55);  // 55 = 'A' - 10
        else
            String[i] = (char)(Nibble + 48);  // 48 = '0' - 0
            
        Value >>= 4;
    }
    
    // Null-terminate the string
    String[4] = 0;
}