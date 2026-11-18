int aligned(int number)
{
 return (((number + (1 << 6) - 1) >> 6) << 6);
}