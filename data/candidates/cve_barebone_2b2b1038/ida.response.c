void __cdecl vqp_print(netdissect_options *ndo, const u_char *pptr, u_int len)
{
  const char *v3; // rax
  const char *v4; // rax
  uint32_t v5; // eax
  const char *v6; // rax
  u_int v7; // [rsp+0h] [rbp-100h]
  uint32_t v8; // [rsp+0h] [rbp-100h]
  int v9; // [rsp+8h] [rbp-F8h]
  u_int v10; // [rsp+10h] [rbp-F0h]
  int (*v11)(netdissect_options *, const char *, ...); // [rsp+28h] [rbp-D8h]
  const char *v12; // [rsp+38h] [rbp-C8h]
  int (*v13)(netdissect_options *, const char *, ...); // [rsp+40h] [rbp-C0h]
  int (*v14)(netdissect_options *, const char *, ...); // [rsp+58h] [rbp-A8h]
  bool v15; // [rsp+67h] [rbp-99h]
  unsigned int v16; // [rsp+74h] [rbp-8Ch]
  const char *v17; // [rsp+78h] [rbp-88h]
  const char *v18; // [rsp+80h] [rbp-80h]
  unsigned int v19; // [rsp+8Ch] [rbp-74h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+90h] [rbp-70h]
  unsigned int v21; // [rsp+A4h] [rbp-5Ch]
  const char *v22; // [rsp+A8h] [rbp-58h]
  int (*v23)(netdissect_options *, const char *, ...); // [rsp+B0h] [rbp-50h]
  uint8_t nitems; // [rsp+BBh] [rbp-45h]
  int tlena; // [rsp+BCh] [rbp-44h]
  int tlenb; // [rsp+BCh] [rbp-44h]
  u_int vqp_obj_type; // [rsp+C0h] [rbp-40h]
  uint16_t vqp_obj_len; // [rsp+C6h] [rbp-3Ah]
  const u_char *tptr; // [rsp+C8h] [rbp-38h]
  const u_char *tptra; // [rsp+C8h] [rbp-38h]

  if ( ndo->ndo_snapend - 8 <= ndo->ndo_snapend && pptr <= ndo->ndo_snapend - 8 )
  {
    if ( *pptr == 1 )
    {
      if ( ndo->ndo_vflag >= 1 )
      {
        nitems = pptr[3];
        ndo_printf = ndo->ndo_printf;
        v16 = *pptr;
        v17 = tok2str(&vqp_msg_type_values, "unknown (%u)", pptr[1]);
        v18 = tok2str(&vqp_error_code_values, "unknown (%u)", pptr[2]);
        v19 = pptr[2];
        v8 = EXTRACT_32BITS(pptr + 4);
        v9 = nitems;
        v10 = len;
        ndo_printf(
          ndo,
          "\n\tVQPv%u, %s Message, error-code %s (%u), seq 0x%08x, items %u, length %u",
          v16,
          v17,
          v18,
          v19,
          v8,
          v9,
          v10);
        tptr = pptr + 8;
        tlena = len - 8;
        while ( 1 )
        {
          v15 = 0;
          if ( nitems )
            v15 = tlena > 0;
          if ( !v15 )
            break;
          vqp_obj_type = EXTRACT_32BITS(tptr);
          vqp_obj_len = EXTRACT_16BITS(tptr + 4);
          tptra = tptr + 6;
          tlenb = tlena - 6;
          v14 = ndo->ndo_printf;
          v4 = tok2str(&vqp_obj_values, "Unknown", vqp_obj_type);
          v14(ndo, "\n\t  %s Object (0x%08x), length %u, value: ", v4, vqp_obj_type, vqp_obj_len);
          if ( !vqp_obj_type || !vqp_obj_len )
            break;
          if ( &ndo->ndo_snapend[-(unsigned __int64)vqp_obj_len] > ndo->ndo_snapend
            || tptra > &ndo->ndo_snapend[-(unsigned __int64)vqp_obj_len] )
          {
            goto trunc;
          }
          switch ( vqp_obj_type )
          {
            case 0xC01u:
              v13 = ndo->ndo_printf;
              v12 = ipaddr_string(ndo, tptra);
              v5 = EXTRACT_32BITS(tptra);
              v13(ndo, "%s (0x%08x)", v12, v5);
              break;
            case 0xC02u:
            case 0xC03u:
            case 0xC04u:
            case 0xC05u:
              safeputs(ndo, tptra, vqp_obj_len);
              break;
            case 0xC06u:
            case 0xC08u:
              v11 = ndo->ndo_printf;
              v6 = etheraddr_string(ndo, tptra);
              v11(ndo, "%s", v6);
              break;
            default:
              if ( ndo->ndo_vflag <= 1 )
                print_unknown_data(ndo, tptra, "\n\t    ", vqp_obj_len);
              break;
          }
          tptr = &tptra[vqp_obj_len];
          tlena = tlenb - vqp_obj_len;
          --nitems;
        }
      }
      else
      {
        v23 = ndo->ndo_printf;
        v21 = *pptr;
        v22 = tok2str(&vqp_msg_type_values, "unknown (%u)", pptr[1]);
        v3 = tok2str(&vqp_error_code_values, "unknown (%u)", pptr[2]);
        v7 = len;
        v23(ndo, "VQPv%u %s Message, error-code %s (%u), length %u", v21, v22, v3, pptr[2], v7);
      }
    }
    else
    {
      ndo->ndo_printf(ndo, "VQP version %u packet not supported", *pptr);
    }
  }
  else
  {
trunc:
    ndo->ndo_printf(ndo, "\n\t[|VQP]");
  }
}