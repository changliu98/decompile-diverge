static inline int sios_ioapic_redir_entry(unsigned int channel)
{
  return (0x70 + (channel & 1) * 2);
}