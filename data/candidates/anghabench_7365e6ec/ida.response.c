int __cdecl llc_shdlc_w_used(int ns, int dnr)
{
  if ( dnr > ns )
    return ns + 8 - dnr;
  else
    return ns - dnr;
}