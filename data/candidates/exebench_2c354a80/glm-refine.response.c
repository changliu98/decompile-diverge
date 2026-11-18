void __cdecl entry_clr_protected(unsigned __int64 *entry)
{
    *entry &= ~0x200ULL;
}