void aodv_extension(netdissect_options *ndo,aodv_ext *ep,u_int length)

{
  aodv_hello *ah;
  u_int length_local;
  aodv_ext *ep_local;
  netdissect_options *ndo_local;
  
  if (ep->type == '\x01') {
    if (((ndo->ndo_snapend < ndo->ndo_snapend + -6) || ((aodv_ext *)(ndo->ndo_snapend + -6) < ep))
       || (length < 6)) {
      (*ndo->ndo_printf)(ndo," [|hello]");
    }
    else {
      (*ndo->ndo_printf)(ndo,"\n\text HELLO %ld ms",
                         (ulong)((uint)ep[1].type << 0x18 | (uint)ep[1].length << 0x10 |
                                 (uint)ep[2].type << 8 | (uint)ep[2].length));
    }
  }
  else {
    (*ndo->ndo_printf)(ndo,"\n\text %u %u",(ulong)ep->type,(ulong)ep->length);
  }
  return;
}