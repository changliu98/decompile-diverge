static inline void validate_st_entry(unsigned long *entry)
{
 *entry &= ~0x20;
 *entry |= 0x00;
}