void set_bit(unsigned int *array, int index)
{
 array[index/32] = array[index/32] & ~(0x80000000 >> (index % 32));
}