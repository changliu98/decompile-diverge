int __cdecl isis_print_mt_capability_subtlv(netdissect_options *ndo, const uint8_t *tptr, int len)
{
  int tmp;
  unsigned int stlv_len;
  unsigned int stlv_type;
  const uint8_t *tptr2;

  while (1)
  {
    while (1)
    {
      if (len <= 2)
        return 0;

      stlv_type = *tptr;
      stlv_len = tptr[1];
      tptr += 2;
      len -= 2;

      ndo->ndo_printf(
        ndo,
        "\n\t      %s subTLV #%u, length: %u",
        tok2str(&isis_mt_capability_subtlv_values, "unknown", stlv_type),
        stlv_type,
        stlv_len
      );

      if (stlv_type == 1)
        break;

      if (stlv_type == 3)
      {
        if (ndo->ndo_snapend - 8 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 8)
          goto trunc;

        ndo->ndo_printf(ndo, (const char *)&unk_210D, _byteswap_ulong(*(_DWORD *)tptr));
        tptr2 = tptr + 4;
        ndo->ndo_printf(ndo, "%04x", _byteswap_ushort(*(_WORD *)tptr2));
        tptr2 += 2;
        
        uint16_t word_val = _byteswap_ushort(*(_WORD *)tptr2);
        ndo->ndo_printf(
          ndo,
          ", RES: %d, VID: %d",
          (int)(word_val) >> 12,
          word_val & 0xFFF
        );
        
        tptr = tptr2 + 2;
        len -= 8;

        for (int stlv_lena = stlv_len - 8; stlv_lena >= 4; stlv_lena -= 4)
        {
          if (ndo->ndo_snapend - 4 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 4)
            goto trunc;

          uint32_t dword_val = _byteswap_ulong(*(_DWORD *)tptr);
          ndo->ndo_printf(
            ndo,
            "\n\t        T: %d, R: %d, RES: %d, ISID: %d",
            dword_val >> 31,
            (dword_val >> 30) & 1,
            (dword_val >> 24) & 0x3F,
            dword_val & 0xFFFFFF
          );
          
          tptr += 4;
          len -= 4;
        }
      }
    }

    if (ndo->ndo_snapend - 19 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 19)
      break;

    ndo->ndo_printf(ndo, "\n\t        CIST Root-ID: %08x", _byteswap_ulong(*(_DWORD *)tptr));
    tptr2 = tptr + 4;
    ndo->ndo_printf(ndo, " %08x", _byteswap_ulong(*(_DWORD *)tptr2));
    tptr2 += 4;
    ndo->ndo_printf(ndo, ", Path Cost: %08x", _byteswap_ulong(*(_DWORD *)tptr2));
    tptr2 += 4;
    ndo->ndo_printf(ndo, ", Prio: %d", _byteswap_ushort(*(_WORD *)tptr2));
    tptr2 += 2;

    uint16_t word_val = _byteswap_ushort(*(_WORD *)tptr2);
    uint32_t dword_val = _byteswap_ulong(*(_DWORD *)tptr2);
    ndo->ndo_printf(ndo, "\n\t        RES: %d", (int)word_val >> 5);
    ndo->ndo_printf(ndo, ", V: %d", ((int)word_val >> 4) & 1);
    ndo->ndo_printf(ndo, ", SPSource-ID: %d", dword_val & 0xFFFFF);
    
    tptr2 += 4;
    tmp = *tptr2;
    ndo->ndo_printf(ndo, ", No of Trees: %x", tmp);
    
    tptr = tptr2 + 1;
    len -= 19;

    while (tmp)
    {
      if (ndo->ndo_snapend - 8 > ndo->ndo_snapend || tptr > ndo->ndo_snapend - 8)
        goto trunc;

      uint8_t byte_val = *tptr;
      ndo->ndo_printf(
        ndo,
        "\n\t         U:%d, M:%d, A:%d, RES:%d",
        (int)byte_val >> 7,
        ((int)byte_val >> 6) & 1,
        ((int)byte_val >> 5) & 1,
        byte_val & 0x1F
      );

      tptr2 = tptr + 1;
      ndo->ndo_printf(ndo, ", ECT: %08x", _byteswap_ulong(*(_DWORD *)tptr2));
      tptr2 += 4;

      uint32_t bvid_val = (tptr2[2] | (tptr2[1] << 8) | (*tptr2 << 16));
      uint16_t spvid_val = _byteswap_ushort(*(_WORD *)(tptr2 + 1));
      ndo->ndo_printf(
        ndo,
        ", BVID: %d, SPVID: %d",
        (bvid_val >> 12) & 0xFFF,
        spvid_val & 0xFFF
      );

      tptr = tptr2 + 3;
      len -= 8;
      --tmp;
    }
  }

trunc:
  ndo->ndo_printf(ndo, "\n\t\t");
  ndo->ndo_printf(ndo, "%s", " [|isis]");
  return 1;
}