void __cdecl validate_st_entry(unsigned __int64 *entry)
{
    *entry &= ~(1ULL << 5);
}