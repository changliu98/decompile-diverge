static inline unsigned int XXH32_endian(unsigned int acc, unsigned int input)
{
    return (acc - (input * 2048144777UL))
        * (unsigned int) 0x9e370001UL;
}