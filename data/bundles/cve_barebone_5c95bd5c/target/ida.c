int __cdecl rpki_rtr_pdu_print(netdissect_options *ndo, const u_char *tptr, u_int indent)
{
  const char *v3; // rax
  char *v4; // rax
  char *v5; // rax
  const char *v6; // rax
  const char *v7; // rax
  const char *v8; // rax
  char *v9; // rax
  char *v10; // rax
  __int64 v12; // [rsp+0h] [rbp-130h]
  int (*v13)(netdissect_options *, const char *, ...); // [rsp+20h] [rbp-110h]
  int (*v14)(netdissect_options *, const char *, ...); // [rsp+30h] [rbp-100h]
  char *v15; // [rsp+40h] [rbp-F0h]
  int (*v16)(netdissect_options *, const char *, ...); // [rsp+48h] [rbp-E8h]
  char *v17; // [rsp+58h] [rbp-D8h]
  int (*v18)(netdissect_options *, const char *, ...); // [rsp+60h] [rbp-D0h]
  char *v19; // [rsp+70h] [rbp-C0h]
  int (*v20)(netdissect_options *, const char *, ...); // [rsp+78h] [rbp-B8h]
  int (*v21)(netdissect_options *, const char *, ...); // [rsp+88h] [rbp-A8h]
  int (*v22)(netdissect_options *, const char *, ...); // [rsp+98h] [rbp-98h]
  char *v23; // [rsp+A8h] [rbp-88h]
  unsigned int v24; // [rsp+B4h] [rbp-7Ch]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+B8h] [rbp-78h]
  u_int error_code; // [rsp+C8h] [rbp-68h]
  u_int tlen; // [rsp+CCh] [rbp-64h]
  u_int tlena; // [rsp+CCh] [rbp-64h]
  unsigned int text_length; // [rsp+D0h] [rbp-60h]
  u_int encapsulated_pdu_length; // [rsp+D4h] [rbp-5Ch]
  u_int hexdump; // [rsp+FCh] [rbp-34h]
  unsigned int pdu_len; // [rsp+100h] [rbp-30h]
  u_int pdu_type; // [rsp+104h] [rbp-2Ch]
  const u_char *tptra; // [rsp+118h] [rbp-18h]
  const u_char *tptrb; // [rsp+118h] [rbp-18h]

  tptra = tptr;
  pdu_type = tptr[1];
  pdu_len = _byteswap_ulong(*((_DWORD *)tptr + 1));
  if ( &ndo->ndo_snapend[-(unsigned __int64)pdu_len] > ndo->ndo_snapend
    || tptr > &ndo->ndo_snapend[-(unsigned __int64)pdu_len] )
  {
    return 1;
  }
  hexdump = 0;
  ndo_printf = ndo->ndo_printf;
  v23 = indent_string(8u);
  v24 = *tptr;
  v3 = tok2str(&rpki_rtr_pdu_values, "Unknown", pdu_type);
  ndo_printf(ndo, "%sRPKI-RTRv%u, %s PDU (%u), length: %u", v23, v24, v3, pdu_type, pdu_len);
  switch ( pdu_type )
  {
    case 0u:
    case 1u:
    case 7u:
      v22 = ndo->ndo_printf;
      v4 = indent_string(indent + 2);
      v22(
        ndo,
        "%sSession ID: 0x%04x, Serial: %u",
        v4,
        _byteswap_ushort(*((_WORD *)tptr + 1)),
        _byteswap_ulong(*((_DWORD *)tptr + 2)));
      break;
    case 2u:
    case 8u:
      break;
    case 3u:
      v21 = ndo->ndo_printf;
      v5 = indent_string(indent + 2);
      v21(ndo, "%sSession ID: 0x%04x", v5, _byteswap_ushort(*((_WORD *)tptr + 1)));
      break;
    case 4u:
      v20 = ndo->ndo_printf;
      v19 = indent_string(indent + 2);
      v6 = getname(ndo, tptr + 12);
      LODWORD(v12) = _byteswap_ulong(*((_DWORD *)tptr + 4));
      v20(ndo, "%sIPv4 Prefix %s/%u-%u, origin-as %u, flags 0x%02x", v19, v6, tptr[9], tptr[10], v12, tptr[8]);
      break;
    case 6u:
      v18 = ndo->ndo_printf;
      v17 = indent_string(indent + 2);
      v7 = getname6(ndo, tptr + 12);
      LODWORD(v12) = _byteswap_ulong(*((_DWORD *)tptr + 7));
      v18(ndo, "%sIPv6 Prefix %s/%u-%u, origin-as %u, flags 0x%02x", v17, v7, tptr[9], tptr[10], v12, tptr[8]);
      break;
    case 0xAu:
      encapsulated_pdu_length = _byteswap_ulong(*((_DWORD *)tptr + 2));
      if ( &ndo->ndo_snapend[-(unsigned __int64)encapsulated_pdu_length] > ndo->ndo_snapend )
        return 1;
      if ( tptr > &ndo->ndo_snapend[-(unsigned __int64)encapsulated_pdu_length] )
        return 1;
      error_code = _byteswap_ushort(*((_WORD *)tptr + 1));
      v16 = ndo->ndo_printf;
      v15 = indent_string(indent + 2);
      v8 = tok2str(&rpki_rtr_error_codes, "Unknown", error_code);
      v16(ndo, "%sError code: %s (%u), Encapsulated PDU length: %u", v15, v8, error_code, encapsulated_pdu_length);
      tptrb = tptr + 12;
      tlen = pdu_len - 12;
      if ( encapsulated_pdu_length )
      {
        if ( encapsulated_pdu_length <= tlen )
        {
          v14 = ndo->ndo_printf;
          v9 = indent_string(indent + 4);
          v14(ndo, "%s-----encapsulated PDU-----", v9);
          if ( rpki_rtr_pdu_print(ndo, tptrb, indent + 2) )
            return 1;
        }
      }
      tptra = &tptrb[encapsulated_pdu_length];
      tlena = tlen - encapsulated_pdu_length;
      text_length = 0;
      if ( tlena > 4 )
      {
        text_length = _byteswap_ulong(*(_DWORD *)tptra);
        tptra += 4;
        tlena -= 4;
      }
      if ( &ndo->ndo_snapend[-(unsigned __int64)text_length] > ndo->ndo_snapend )
        return 1;
      if ( tptra > &ndo->ndo_snapend[-(unsigned __int64)text_length] )
        return 1;
      if ( text_length )
      {
        if ( text_length <= tlena )
        {
          v13 = ndo->ndo_printf;
          v10 = indent_string(indent + 2);
          v13(ndo, "%sError text: ", v10);
          if ( fn_printn(ndo, tptra, text_length, ndo->ndo_snapend) )
            return 1;
        }
      }
      break;
    default:
      hexdump = 1;
      break;
  }
  if ( ndo->ndo_vflag > 1 || ndo->ndo_vflag && hexdump )
    print_unknown_data(ndo, tptra, "\n\t  ", pdu_len);
  return 0;
}