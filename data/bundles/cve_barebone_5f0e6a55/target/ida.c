u_int __cdecl ieee802_15_4_if_print(netdissect_options *ndo, const pcap_pkthdr *h, const u_char *p)
{
  const char *v3; // rax
  const char *v4; // rax
  int (*v6)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-60h]
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+30h] [rbp-40h]
  uint16_t panid; // [rsp+42h] [rbp-2Eh]
  uint8_t seq; // [rsp+45h] [rbp-2Bh]
  uint16_t fc; // [rsp+46h] [rbp-2Ah]
  u_int hdrlen; // [rsp+48h] [rbp-28h]
  bpf_u_int32 caplen; // [rsp+4Ch] [rbp-24h]
  u_int caplena; // [rsp+4Ch] [rbp-24h]
  u_int caplenb; // [rsp+4Ch] [rbp-24h]
  u_int caplenc; // [rsp+4Ch] [rbp-24h]
  const u_char *pa; // [rsp+50h] [rbp-20h]
  const u_char *pb; // [rsp+50h] [rbp-20h]
  const u_char *pc; // [rsp+50h] [rbp-20h]
  u_int v19; // [rsp+6Ch] [rbp-4h]

  caplen = h->caplen;
  panid = 0;
  if ( caplen >= 3 )
  {
    hdrlen = 3;
    fc = *(_WORD *)p;
    seq = p[2];
    pa = p + 3;
    caplena = caplen - 3;
    ndo->ndo_printf(ndo, "IEEE 802.15.4 %s packet ", (&ftypes)[*(_WORD *)p & 7]);
    if ( ndo->ndo_vflag )
      ndo->ndo_printf(ndo, "seq %02x ", seq);
    switch ( (fc >> 10) & 3 )
    {
      case 0:
        if ( (fc & 0x40) != 0 )
          goto LABEL_47;
        if ( ndo->ndo_vflag )
          ndo->ndo_printf(ndo, "none ");
        goto LABEL_25;
      case 1:
        if ( ndo->ndo_vflag )
          ndo->ndo_printf(ndo, "reserved destination addressing mode");
        return 3;
      case 2:
        if ( caplena < 2 )
          goto LABEL_47;
        panid = *(_WORD *)pa;
        pb = pa + 2;
        caplenb = caplena - 2;
        hdrlen = 5;
        if ( caplenb < 2 )
          goto LABEL_47;
        if ( ndo->ndo_vflag )
          ndo->ndo_printf(ndo, "%04x:%04x ", panid, *((unsigned __int16 *)pb + 1));
        pa = pb + 2;
        caplena = caplenb - 2;
        hdrlen = 7;
        goto LABEL_25;
      case 3:
        if ( caplena < 2 || (panid = *(_WORD *)pa, pc = pa + 2, caplenc = caplena - 2, hdrlen = 5, caplenc < 8) )
        {
LABEL_47:
          ndo->ndo_printf(ndo, "[|802.15.4]");
          v19 = hdrlen;
        }
        else
        {
          if ( ndo->ndo_vflag )
          {
            ndo_printf = ndo->ndo_printf;
            v3 = le64addr_string(ndo, pc);
            ndo_printf(ndo, "%04x:%s ", panid, v3);
          }
          pa = pc + 8;
          caplena = caplenc - 8;
          hdrlen = 13;
LABEL_25:
          if ( ndo->ndo_vflag )
            ndo->ndo_printf(ndo, "< ");
          switch ( fc >> 14 )
          {
            case 0:
              if ( ndo->ndo_vflag )
                ndo->ndo_printf(ndo, "none ");
              break;
            case 1:
              if ( ndo->ndo_vflag )
                ndo->ndo_printf(ndo, "reserved source addressing mode");
              return 0;
            case 2:
              if ( (fc & 0x40) != 0 )
                goto LABEL_38;
              if ( caplena < 2 )
                goto LABEL_47;
              panid = *(_WORD *)pa;
              pa += 2;
              caplena -= 2;
              hdrlen += 2;
LABEL_38:
              if ( caplena < 2 )
                goto LABEL_47;
              if ( ndo->ndo_vflag )
                ndo->ndo_printf(ndo, "%04x:%04x ", panid, *(unsigned __int16 *)pa);
              pa += 2;
              caplena -= 2;
              hdrlen += 2;
              break;
            case 3:
              if ( (fc & 0x40) != 0 )
                goto LABEL_46;
              if ( caplena < 2 )
                goto LABEL_47;
              panid = *(_WORD *)pa;
              pa += 2;
              caplena -= 2;
              hdrlen += 2;
LABEL_46:
              if ( caplena < 8 )
                goto LABEL_47;
              if ( ndo->ndo_vflag )
              {
                v6 = ndo->ndo_printf;
                v4 = le64addr_string(ndo, pa);
                v6(ndo, "%04x:%s ", panid, v4);
              }
              pa += 8;
              caplena -= 8;
              hdrlen += 8;
              break;
            default:
              break;
          }
          if ( !ndo->ndo_suppress_default_print )
            ndo->ndo_default_print(ndo, pa, caplena);
          v19 = hdrlen;
        }
        break;
      default:
        goto LABEL_25;
    }
  }
  else
  {
    ndo->ndo_printf(ndo, "[|802.15.4]");
    return caplen;
  }
  return v19;
}