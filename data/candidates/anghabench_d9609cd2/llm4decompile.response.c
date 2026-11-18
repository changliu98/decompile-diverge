uint32_t reassemble_21(uint32_t as21)
{
 uint32_t r;

 r = (as21 & 0x00100000) >> 20;
 r |= (as21 & 0x000ffe00) >> 8;
 r |= (as21 & 0x0000180) << 7;
 r |= (as21 & 0x000007c) << 14;
 r |= (as21 & 0x0000003) << 12;

 return r;
}