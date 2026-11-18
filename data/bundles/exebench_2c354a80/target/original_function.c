static inline void entry_clr_protected(unsigned long *entry)
{
 *entry &= ~0x200;
 *entry |= 0x000;
}