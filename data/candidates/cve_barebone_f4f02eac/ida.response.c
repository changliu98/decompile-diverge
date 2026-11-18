int __cdecl match(Reinst *pc, const char *sp_0, const char *bol, int flags, Resub *out)
{
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  Rune v9; // ax
  int v10; // eax
  Rune v11; // ax
  bool v13; // [rsp+6h] [rbp-FAh]
  bool v14; // [rsp+7h] [rbp-F9h]
  Reclass *v15; // [rsp+8h] [rbp-F8h]
  Reclass *cc; // [rsp+10h] [rbp-F0h]
  Rune c; // [rsp+22h] [rbp-DEh] BYREF
  int i; // [rsp+24h] [rbp-DCh]
  Resub scratch; // [rsp+28h] [rbp-D8h] BYREF
  Resub *outa; // [rsp+D0h] [rbp-30h]
  int flagsa; // [rsp+DCh] [rbp-24h]
  const char *bola; // [rsp+E0h] [rbp-20h]
  const char *sp_0a; // [rsp+E8h] [rbp-18h]
  Reinst *pca; // [rsp+F0h] [rbp-10h]

  pca = pc;
  sp_0a = sp_0;
  bola = bol;
  flagsa = flags;
  outa = out;
  while ( 2 )
  {
    switch ( pca->opcode )
    {
      case 0u:
        return 1;
      case 1u:
        pca = pca->x;
        continue;
      case 2u:
        memcpy(&scratch, outa, sizeof(scratch));
        if ( !match(pca->x, sp_0a, bola, flagsa, &scratch) )
        {
          pca = pca->y;
          continue;
        }
        memcpy(outa, &scratch, sizeof(Resub));
        return 1;
      case 3u:
        if ( !match(pca->x, sp_0a, bola, flagsa, outa) )
          return 0;
        pca = pca->y;
        continue;
      case 4u:
        memcpy(&scratch, outa, sizeof(scratch));
        if ( match(pca->x, sp_0a, bola, flagsa, &scratch) )
          return 0;
        pca = pca->y;
        continue;
      case 5u:
        v5 = chartorune(&c, sp_0a);
        sp_0a += v5;
        if ( !c )
          return 0;
        ++pca;
        continue;
      case 6u:
        v6 = chartorune(&c, sp_0a);
        sp_0a += v6;
        if ( !c )
          return 0;
        if ( isnewline(c) )
          return 0;
        ++pca;
        continue;
      case 7u:
        v7 = chartorune(&c, sp_0a);
        sp_0a += v7;
        if ( !c )
          return 0;
        if ( (flagsa & 1) != 0 )
          c = canon(c);
        if ( c != pca->c )
          return 0;
        ++pca;
        continue;
      case 8u:
        v8 = chartorune(&c, sp_0a);
        sp_0a += v8;
        if ( !c )
          return 0;
        if ( (flagsa & 1) != 0 )
        {
          cc = pca->cc;
          v9 = canon(c);
          if ( !incclasscanon(cc, v9) )
            return 0;
        }
        else if ( !incclass(pca->cc, c) )
        {
          return 0;
        }
        ++pca;
        continue;
      case 9u:
        v10 = chartorune(&c, sp_0a);
        sp_0a += v10;
        if ( !c )
          return 0;
        if ( (flagsa & 1) != 0 )
        {
          v15 = pca->cc;
          v11 = canon(c);
          if ( incclasscanon(v15, v11) )
            return 0;
        }
        else if ( incclass(pca->cc, c) )
        {
          return 0;
        }
        ++pca;
        continue;
      case 0xAu:
        i = outa->sub[pca->n].ep - outa->sub[pca->n].sp;
        if ( (flagsa & 1) != 0 )
        {
          if ( strncmpcanon(sp_0a, outa->sub[pca->n].sp, i) )
            return 0;
        }
        else if ( strncmp(sp_0a, outa->sub[pca->n].sp, i) )
        {
          return 0;
        }
        if ( i > 0 )
          sp_0a += i;
        ++pca;
        continue;
      case 0xBu:
        if ( sp_0a != bola || (flagsa & 4) != 0 )
        {
          if ( (flagsa & 2) == 0 || sp_0a <= bola || !isnewline(*(sp_0a - 1)) )
            return 0;
          ++pca;
        }
        else
        {
          ++pca;
        }
        continue;
      case 0xCu:
        if ( *sp_0a )
        {
          if ( (flagsa & 2) == 0 || !isnewline(*sp_0a) )
            return 0;
          ++pca;
        }
        else
        {
          ++pca;
        }
        continue;
      case 0xDu:
        v14 = 0;
        if ( sp_0a > bola )
          v14 = iswordchar(*(sp_0a - 1)) != 0;
        i = v14;
        i ^= iswordchar(*sp_0a);
        if ( !i )
          return 0;
        ++pca;
        continue;
      case 0xEu:
        v13 = 0;
        if ( sp_0a > bola )
          v13 = iswordchar(*(sp_0a - 1)) != 0;
        i = v13;
        i ^= iswordchar(*sp_0a);
        if ( i )
          return 0;
        ++pca;
        continue;
      case 0xFu:
        outa->sub[pca->n].sp = sp_0a;
        ++pca;
        continue;
      case 0x10u:
        outa->sub[pca->n].ep = sp_0a;
        ++pca;
        continue;
      default:
        return 0;
    }
  }
}