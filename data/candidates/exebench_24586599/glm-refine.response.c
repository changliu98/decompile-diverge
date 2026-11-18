th bit of the integer pointed to by n
void __cdecl set_bit(int *value, const int bit_position)
{
    *value |= (1 << bit_position);
}