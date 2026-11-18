static inline unsigned int i2c_id(unsigned int id)
{
  return (id * 2 + 0x14000 + 0xe00);
}