0
int __cdecl reassemble_21(int as21)
{
    int b_1_0   = (as21 & 0x000003) << 12; // Takes bits 1:0, moves to 13:12
    int b_6_2   = (as21 & 0x00007C) << 14; // Takes bits 6:2, moves to 20:16 (Note: overlaps with bit 12)
    int b_8_7   = (as21 & 0x000180) << 7;  // Takes bits 8:7, moves to 15:14
    int b_20_9  = (as21 & 0xFFE00) >> 8;   // Takes bits 20:9, moves to 12:1
    int b_20    = (as21 & 0x100000) >> 20; // Takes bit 20, moves to bit 0

    return b_1_0 | b_6_2 | b_8_7 | b_20_9 | b_20;
}