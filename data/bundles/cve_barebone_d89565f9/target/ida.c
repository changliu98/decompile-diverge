void __cdecl print_attr_string(netdissect_options *ndo, const u_char *data, u_int length, u_short attr_code)
{
  const char *v4; // rdx
  unsigned int v5; // [rsp+4h] [rbp-4Ch]
  bool v6; // [rsp+1Fh] [rbp-31h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-28h]
  u_int i; // [rsp+34h] [rbp-1Ch]
  u_int lengtha; // [rsp+3Ch] [rbp-14h]
  const u_char *dataa; // [rsp+40h] [rbp-10h]

  dataa = data;
  lengtha = length;
  if ( &ndo->ndo_snapend[-(unsigned __int64)length] > ndo->ndo_snapend
    || data > &ndo->ndo_snapend[-(unsigned __int64)length] )
  {
    goto LABEL_18;
  }
  if ( attr_code == 58 )
  {
    ndo_printf = ndo->ndo_printf;
    v4 = tok2str(&rfc4675_tagged, "Unknown tag", *data);
    ndo_printf(ndo, "%s (0x%02x) ", v4, *data);
    dataa = data + 1;
    --lengtha;
    goto LABEL_25;
  }
  if ( (unsigned int)attr_code - 66 >= 2 )
  {
    if ( attr_code == 69 )
    {
      if ( length < 3 )
        goto LABEL_18;
      if ( *data && *data <= 0x1Fu )
        ndo->ndo_printf(ndo, "Tag[%u] ", *data);
      else
        ndo->ndo_printf(ndo, "Tag[Unused] ");
      ndo->ndo_printf(ndo, "Salt %u ", _byteswap_ushort(*(_WORD *)(data + 1)));
      dataa = data + 3;
      lengtha -= 3;
      goto LABEL_25;
    }
    if ( (unsigned int)attr_code - 81 >= 2 && (unsigned int)attr_code - 90 >= 2 )
      goto LABEL_25;
  }
  if ( *data > 0x1Fu )
    goto LABEL_25;
  if ( !length )
  {
LABEL_18:
    ndo->ndo_printf(ndo, "%s", " [|radius]");
    return;
  }
  if ( *data )
    ndo->ndo_printf(ndo, "Tag[%u] ", *data);
  else
    ndo->ndo_printf(ndo, "Tag[Unused] ");
  dataa = data + 1;
  --lengtha;
LABEL_25:
  for ( i = 0; ; ++i )
  {
    v6 = 0;
    if ( *dataa )
      v6 = i < lengtha;
    if ( !v6 )
      break;
    if ( *dataa >= 0x20u && *dataa <= 0x7Eu )
      v5 = *dataa;
    else
      v5 = 46;
    ndo->ndo_printf(ndo, "%c", v5);
    ++dataa;
  }
}