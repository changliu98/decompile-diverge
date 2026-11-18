void __cdecl ripng_print(netdissect_options *ndo, const u_char *dat, unsigned int length)
{
  unsigned __int64 v3; // rdx
  unsigned __int64 v4; // rdx
  unsigned __int64 v5; // rdx
  bool v6; // [rsp+3h] [rbp-4Dh]
  int v7; // [rsp+4h] [rbp-4Ch]
  unsigned int v8; // [rsp+8h] [rbp-48h]
  int trunc; // [rsp+18h] [rbp-38h]
  unsigned int j; // [rsp+1Ch] [rbp-34h]
  unsigned int ja; // [rsp+1Ch] [rbp-34h]
  u_int i; // [rsp+20h] [rbp-30h]
  const netinfo6 *ni; // [rsp+28h] [rbp-28h]
  const netinfo6 *nia; // [rsp+28h] [rbp-28h]

  if ( ndo->ndo_snapend >= dat )
  {
    v8 = length <= (unsigned int)ndo->ndo_snapend - (unsigned int)dat
       ? length
       : (unsigned int)&ndo->ndo_snapend[-(_DWORD)dat];
    if ( v8 >= 4uLL )
    {
      i = v8 - 4;
      v7 = *dat;
      if ( v7 == 1 )
      {
        v3 = length % 0x14uLL;
        j = length / 0x14;
        if ( length / 0x14 != 1 || dat[23] != 16 )
          goto LABEL_17;
        v6 = 0;
        if ( !*((_DWORD *)dat + 1) )
        {
          v6 = 0;
          if ( !*((_DWORD *)dat + 2) )
          {
            v6 = 0;
            if ( !*((_DWORD *)dat + 3) )
              v6 = *((_DWORD *)dat + 4) == 0;
          }
        }
        if ( v6 )
        {
          ndo->ndo_printf(ndo, " ripng-req dump", v3);
        }
        else
        {
LABEL_17:
          if ( 20LL * (int)j == length - 4 )
            ndo->ndo_printf(ndo, " ripng-req %d:", j);
          else
            ndo->ndo_printf(ndo, " ripng-req %d[%u]:", j, length);
          v4 = i % 0x14uLL;
          ni = (const netinfo6 *)(dat + 4);
          while ( i >= 0x14uLL )
          {
            if ( ndo->ndo_vflag <= 1 )
              ndo->ndo_printf(ndo, " ", v4);
            else
              ndo->ndo_printf(ndo, "\n\t", v4);
            rip6_entry_print(ndo, ni, 0);
            i -= 20;
            ++ni;
          }
        }
      }
      else if ( v7 == 2 )
      {
        ja = length / 0x14;
        if ( 20LL * (length / 0x14) == length - 4 )
          ndo->ndo_printf(ndo, " ripng-resp %d:", ja);
        else
          ndo->ndo_printf(ndo, " ripng-resp %d[%u]:", ja, length);
        v5 = i % 0x14uLL;
        trunc = 20 * (i / 0x14uLL) != i;
        nia = (const netinfo6 *)(dat + 4);
        while ( i >= 0x14uLL )
        {
          if ( ndo->ndo_vflag <= 1 )
            ndo->ndo_printf(ndo, " ", v5);
          else
            ndo->ndo_printf(ndo, "\n\t", v5);
          rip6_entry_print(ndo, nia, nia->rip6_metric);
          i -= 20;
          ++nia;
        }
        if ( trunc )
          ndo->ndo_printf(ndo, "[|ripng]", v5);
      }
      else
      {
        ndo->ndo_printf(ndo, " ripng-%d ?? %u", *dat, length);
      }
      if ( dat[1] != 1 )
        ndo->ndo_printf(ndo, " [vers %d]", dat[1]);
    }
  }
}