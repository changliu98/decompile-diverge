int __cdecl isis_print_extd_ip_reach(netdissect_options *ndo, const uint8_t *tptr, const char *ident, uint16_t afi)
{
  const uint8_t *v4; // rax
  const uint8_t *v5; // rax
  unsigned __int8 *v6; // rax
  const char *v7; // rax
  const char *v8; // rax
  const char *v9; // rdx
  const char *v10; // rdx
  const char *v11; // rcx
  unsigned __int8 *v12; // rax
  const uint8_t *v13; // rax
  const uint8_t *v14; // rax
  netdissect_options *v16; // [rsp+0h] [rbp-A0h]
  const char *v17; // [rsp+8h] [rbp-98h]
  int (*v18)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-90h]
  netdissect_options *v19; // [rsp+18h] [rbp-88h]
  const char *v20; // [rsp+20h] [rbp-80h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-78h]
  unsigned int subtlvlen; // [rsp+30h] [rbp-70h]
  int subtlvtype; // [rsp+34h] [rbp-6Ch]
  u_int processed; // [rsp+38h] [rbp-68h]
  int processeda; // [rsp+38h] [rbp-68h]
  u_int sublen; // [rsp+3Ch] [rbp-64h]
  unsigned int byte_length; // [rsp+40h] [rbp-60h]
  unsigned int bit_length; // [rsp+44h] [rbp-5Ch]
  uint8_t status_byte; // [rsp+48h] [rbp-58h]
  u_int metric; // [rsp+4Ch] [rbp-54h]
  uint8_t prefix[16]; // [rsp+50h] [rbp-50h] BYREF
  char ident_buffer[20]; // [rsp+60h] [rbp-40h] BYREF
  uint16_t afia; // [rsp+7Eh] [rbp-22h]
  const char *identa; // [rsp+80h] [rbp-20h]
  const uint8_t *tptra; // [rsp+88h] [rbp-18h]
  netdissect_options *ndoa; // [rsp+90h] [rbp-10h]

  ndoa = ndo;
  tptra = tptr;
  identa = ident;
  afia = afi;
  if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || tptra > ndoa->ndo_snapend - 4 )
    return 0;
  metric = _byteswap_ulong(*(_DWORD *)tptra);
  tptra += 4;
  if ( afia == 2 )
  {
    if ( ndoa->ndo_snapend - 1 > ndoa->ndo_snapend || tptra > ndoa->ndo_snapend - 1 )
      return 0;
    v4 = tptra++;
    status_byte = *v4;
    bit_length = *v4 & 0x3F;
    if ( bit_length > 0x20 )
    {
      ndoa->ndo_printf(ndoa, "%sIPv4 prefix: bad bit length %u", identa, *v4 & 0x3F);
      return 0;
    }
    processed = 5;
  }
  else
  {
    if ( afia != 10 )
      return 0;
    if ( ndoa->ndo_snapend - 1 > ndoa->ndo_snapend || tptra > ndoa->ndo_snapend - 1 )
      return 0;
    v5 = tptra++;
    status_byte = *v5;
    v6 = (unsigned __int8 *)tptra++;
    bit_length = *v6;
    if ( bit_length > 0x80 )
    {
      ndoa->ndo_printf(ndoa, "%sIPv6 prefix: bad bit length %u", identa, *v6);
      return 0;
    }
    processed = 6;
  }
  byte_length = (bit_length + 7) >> 3;
  if ( &ndoa->ndo_snapend[-(unsigned __int64)byte_length] <= ndoa->ndo_snapend
    && tptra <= &ndoa->ndo_snapend[-(unsigned __int64)byte_length] )
  {
    memset(prefix, 0, sizeof(prefix));
    memcpy(prefix, tptra, byte_length);
    tptra += byte_length;
    processeda = processed + byte_length;
    if ( afia == 2 )
    {
      ndo_printf = ndoa->ndo_printf;
      v19 = ndoa;
      v20 = identa;
      v7 = ipaddr_string(ndoa, prefix);
      ndo_printf(v19, "%sIPv4 prefix: %15s/%u", v20, v7, bit_length);
    }
    else if ( afia == 10 )
    {
      v18 = ndoa->ndo_printf;
      v16 = ndoa;
      v17 = identa;
      v8 = ip6addr_string(ndoa, prefix);
      v18(v16, "%sIPv6 prefix: %s/%u", v17, v8, bit_length);
    }
    v9 = "up";
    if ( (status_byte & 0x80) != 0 )
      v9 = "down";
    ndoa->ndo_printf(ndoa, ", Distribution: %s, Metric: %u", v9, metric);
    if ( afia == 2 && (status_byte & 0x40) != 0 )
    {
      ndoa->ndo_printf(ndoa, ", sub-TLVs present");
    }
    else if ( afia == 10 )
    {
      v10 = "Internal";
      if ( (status_byte & 0x40) != 0 )
        v10 = "External";
      v11 = "";
      if ( (status_byte & 0x20) != 0 )
        v11 = ", sub-TLVs present";
      ndoa->ndo_printf(ndoa, ", %s%s", v10, v11);
    }
    if ( afia == 2 && (status_byte & 0x40) != 0 || afia == 10 && (status_byte & 0x20) != 0 )
    {
      if ( ndoa->ndo_snapend - 1 > ndoa->ndo_snapend || tptra > ndoa->ndo_snapend - 1 )
        return 0;
      v12 = (unsigned __int8 *)tptra++;
      sublen = *v12;
      processeda += sublen + 1;
      ndoa->ndo_printf(ndoa, " (%u)", *v12);
      while ( sublen )
      {
        if ( ndoa->ndo_snapend - 2 > ndoa->ndo_snapend || tptra > ndoa->ndo_snapend - 2 )
          return 0;
        v13 = tptra++;
        subtlvtype = *v13;
        v14 = tptra++;
        subtlvlen = *v14;
        snprintf(ident_buffer, 0x14uLL, "%s  ", identa);
        if ( !isis_print_ip_reach_subtlv(ndoa, tptra, subtlvtype, subtlvlen, ident_buffer) )
          return 0;
        tptra += subtlvlen;
        sublen -= subtlvlen + 2;
      }
    }
    return processeda;
  }
  return 0;
}