void __cdecl eap_print(netdissect_options *ndo, const u_char *cp, u_int length)
{
  const char *v3; // rax
  const char *v4; // rax
  const char *v5; // rdx
  const char *v6; // rax
  const char *v7; // rdx
  char *v8; // rdx
  char *v9; // rdx
  const char *v10; // rdx
  int (*v11)(netdissect_options *, const char *, ...); // [rsp+8h] [rbp-C8h]
  int (*v12)(netdissect_options *, const char *, ...); // [rsp+18h] [rbp-B8h]
  int (*v13)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-A8h]
  int (*v14)(netdissect_options *, const char *, ...); // [rsp+38h] [rbp-98h]
  int (*v15)(netdissect_options *, const char *, ...); // [rsp+48h] [rbp-88h]
  int (*v16)(netdissect_options *, const char *, ...); // [rsp+60h] [rbp-70h]
  int (*v17)(netdissect_options *, const char *, ...); // [rsp+70h] [rbp-60h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+88h] [rbp-48h]
  int len; // [rsp+94h] [rbp-3Ch]
  int count; // [rsp+98h] [rbp-38h]
  u_int subtype; // [rsp+9Ch] [rbp-34h]
  u_int type; // [rsp+A0h] [rbp-30h]
  const u_char *tptr; // [rsp+A8h] [rbp-28h]

  if ( ndo->ndo_snapend - 4 > ndo->ndo_snapend || cp > ndo->ndo_snapend - 4 )
    goto trunc;
  if ( ndo->ndo_vflag < 1 )
  {
    ndo_printf = ndo->ndo_printf;
    v3 = tok2str(&eap_frame_type_values, "unknown", cp[1]);
    ndo_printf(ndo, "%s (%u) v%u, len %u", v3, cp[1], *cp, _byteswap_ushort(*((_WORD *)cp + 1)));
    return;
  }
  v17 = ndo->ndo_printf;
  v4 = tok2str(&eap_frame_type_values, "unknown", cp[1]);
  v17(ndo, "%s (%u) v%u, len %u", v4, cp[1], *cp, _byteswap_ulong(*((unsigned __int16 *)cp + 1) << 16));
  tptr = cp + 4;
  if ( !cp[1] )
  {
    type = *tptr;
    len = _byteswap_ushort(*((_WORD *)cp + 3));
    v16 = ndo->ndo_printf;
    v5 = tok2str(&eap_code_values, "unknown", type);
    v16(ndo, ", %s (%u), id %u, len %u", v5, type, cp[5], (unsigned int)len);
    if ( &ndo->ndo_snapend[-len] > ndo->ndo_snapend || tptr > &ndo->ndo_snapend[-len] )
    {
trunc:
      ndo->ndo_printf(ndo, "\n\t[|EAP]");
      return;
    }
    if ( type <= 2 )
    {
      subtype = cp[8];
      v15 = ndo->ndo_printf;
      v6 = tok2str(&eap_type_values, "unknown", subtype);
      v15(ndo, "\n\t\t Type %s (%u)", v6, cp[8]);
      switch ( subtype )
      {
        case 1u:
          if ( len - 5 > 0 )
          {
            ndo->ndo_printf(ndo, ", Identity: ");
            safeputs(ndo, cp + 9, len - 5);
          }
          break;
        case 2u:
          if ( len - 5 > 0 )
          {
            ndo->ndo_printf(ndo, ", Notification: ");
            safeputs(ndo, cp + 9, len - 5);
          }
          break;
        case 3u:
          for ( count = 5; count < len; ++count )
          {
            v14 = ndo->ndo_printf;
            v7 = tok2str(&eap_type_values, "unknown", tptr[count]);
            v14(ndo, " %s (%u),", v7, tptr[count]);
          }
          return;
        default:
          if ( subtype - 4 < 3 )
            return;
          if ( subtype != 13 )
          {
            if ( subtype == 18 )
              goto LABEL_38;
            if ( subtype != 21 )
            {
              if ( subtype != 23 )
              {
                if ( subtype == 43 )
                {
                  ndo->ndo_printf(ndo, " FASTv%u", cp[9] & 7);
                  v12 = ndo->ndo_printf;
                  v9 = bittok2str(&eap_tls_flags_values, "none", cp[9]);
                  v12(ndo, " flags [%s] 0x%02x,", v9, cp[9]);
                  if ( (cp[9] & 0x80) >> 7 )
                    ndo->ndo_printf(ndo, " len %u", _byteswap_ulong(*(_DWORD *)(cp + 10)));
                }
                return;
              }
LABEL_38:
              v11 = ndo->ndo_printf;
              v10 = tok2str(&eap_aka_subtype_values, "unknown", cp[9]);
              v11(ndo, " subtype [%s] 0x%02x,", v10, cp[9]);
              return;
            }
            ndo->ndo_printf(ndo, " TTLSv%u", cp[9] & 7);
          }
          v13 = ndo->ndo_printf;
          v8 = bittok2str(&eap_tls_flags_values, "none", cp[9]);
          v13(ndo, " flags [%s] 0x%02x,", v8, cp[9]);
          if ( (cp[9] & 0x80) >> 7 )
            ndo->ndo_printf(ndo, " len %u", _byteswap_ulong(*(_DWORD *)(cp + 10)));
          break;
      }
    }
  }
}