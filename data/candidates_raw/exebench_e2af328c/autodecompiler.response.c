void _rshift_1bit(struct bit_iterator *bi, int *bit_pos)
{
 bi->cur_byte >>= 1;
 (*bit_pos)++;
}