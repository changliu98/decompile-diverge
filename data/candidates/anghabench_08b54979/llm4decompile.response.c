u_int32_t
F(u_int32_t x, u_int32_t y, u_int32_t z)
{
 return (x & y) | ((~x) & z);
}