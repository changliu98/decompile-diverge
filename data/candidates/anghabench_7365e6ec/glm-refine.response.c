int __cdecl llc_shdlc_w_used(int ns, int dnr)
{
    // Calculate the number of used window slots.
    // The modulo operator handles the sequence number wrap-around (mod 8).
    return (ns - dnr + 8) % 8;
}