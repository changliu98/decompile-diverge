void __cdecl validate_rt_entry(unsigned __int64 *entry)
{
  // 1. Clear bits 5 and 6 (0x20 and 0x40)
  // The original code did this in two steps:
  // *entry &= ~0x20uLL;
  // *entry &= 0xFFFFFFFFFFFFFF3FLL; (which is ~(0x20 | 0x40))
  *entry &= ~(0x20uLL | 0x40uLL);

  // 2. No-op self-assignment removed
  // *entry = *entry;

  // 3. Set bits 0 and 1 (0x3)
  *entry |= 3uLL;
}