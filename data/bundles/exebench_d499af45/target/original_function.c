static inline void validate_rt_entry(unsigned long *entry)
{
 *entry &= ~0x20;
 *entry &= ~0xc0;
 *entry |= 0x00;
 *entry |= 0x3;
}