void __cdecl aodv_extension(netdissect_options *ndo, const aodv_ext *ep, u_int length)
{
  if ( ep->type == 1 )
  {
    if ( ndo->ndo_snapend - 6 > ndo->ndo_snapend || (const u_char *)ep > ndo->ndo_snapend - 6 || length < 6uLL )
      ndo->ndo_printf(ndo, " [|hello]");
    else
      ndo->ndo_printf(ndo, "\n\text HELLO %ld ms", _byteswap_ulong(*(_DWORD *)&ep[1].type));
  }
  else
  {
    ndo->ndo_printf(ndo, "\n\text %u %u", ep->type, ep->length);
  }
}