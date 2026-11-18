void __cdecl aodv_extension(netdissect_options *ndo, const aodv_ext *ep, u_int length)
{
  if (ep->type == 1)
  {
    // Original bounds check:
    // 1. (ndo->ndo_snapend - 6 > ndo->ndo_snapend) checks for pointer underflow (if snapend < 6)
    // 2. ((const u_char *)ep > ndo->ndo_snapend - 6) checks if ep is safely within bounds
    // 3. (length < 6uLL) ensures the claimed packet length is large enough
    if (length < 6 || ndo->ndo_snapend < 6 || (const u_char *)ep > ndo->ndo_snapend - 6)
    {
      ndo->ndo_printf(ndo, " [|hello]");
    }
    else
    {
      // ep[1].type effectively acts as an offset to read the 32-bit integer immediately 
      // following the base aodv_ext header. We use a clean cast to extract the next DWORD.
      const u_int32_t *hello_ext = (const u_int32_t *)(ep + 1);
      ndo->ndo_printf(ndo, "\n\text HELLO %ld ms", (long)_byteswap_ulong(*hello_ext));
    }
  }
  else
  {
    ndo->ndo_printf(ndo, "\n\text %u %u", ep->type, ep->length);
  }
}