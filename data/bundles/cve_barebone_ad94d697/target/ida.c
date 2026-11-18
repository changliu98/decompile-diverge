void __cdecl ubik_print(netdissect_options *ndo, const u_char *bp_0)
{
  const char *v2; // rax
  const char *v3; // rdx
  int (*ndo_printf)(netdissect_options *, const char *, ...); // [rsp+10h] [rbp-1C0h]
  uint32_t counter_8; // [rsp+20h] [rbp-1B0h]
  uint32_t epoch_8; // [rsp+24h] [rbp-1ACh]
  uint32_t counter_7; // [rsp+28h] [rbp-1A8h]
  uint32_t epoch_7; // [rsp+2Ch] [rbp-1A4h]
  uint32_t counter_6; // [rsp+30h] [rbp-1A0h]
  uint32_t epoch_6; // [rsp+34h] [rbp-19Ch]
  unsigned int _i_9; // [rsp+38h] [rbp-198h]
  unsigned int _i_8; // [rsp+3Ch] [rbp-194h]
  uint32_t counter_5; // [rsp+40h] [rbp-190h]
  uint32_t epoch_5; // [rsp+44h] [rbp-18Ch]
  uint32_t counter_4; // [rsp+48h] [rbp-188h]
  uint32_t epoch_4; // [rsp+4Ch] [rbp-184h]
  unsigned int _i_7; // [rsp+50h] [rbp-180h]
  unsigned int _i_6; // [rsp+54h] [rbp-17Ch]
  unsigned int _i_5; // [rsp+58h] [rbp-178h]
  unsigned int _i_4; // [rsp+5Ch] [rbp-174h]
  unsigned int _i_3; // [rsp+60h] [rbp-170h]
  uint32_t counter_3; // [rsp+64h] [rbp-16Ch]
  uint32_t epoch_3; // [rsp+68h] [rbp-168h]
  unsigned int _i_2; // [rsp+6Ch] [rbp-164h]
  unsigned int _i_1; // [rsp+70h] [rbp-160h]
  unsigned int _i_0; // [rsp+74h] [rbp-15Ch]
  uint32_t counter_2; // [rsp+78h] [rbp-158h]
  uint32_t epoch_2; // [rsp+7Ch] [rbp-154h]
  uint32_t counter_1; // [rsp+80h] [rbp-150h]
  uint32_t epoch_1; // [rsp+84h] [rbp-14Ch]
  unsigned __int64 _i; // [rsp+88h] [rbp-148h]
  uint32_t counter_0; // [rsp+90h] [rbp-140h]
  uint32_t epoch_0; // [rsp+94h] [rbp-13Ch]
  uint32_t counter; // [rsp+98h] [rbp-138h]
  uint32_t epoch; // [rsp+9Ch] [rbp-134h]
  char str[256]; // [rsp+A0h] [rbp-130h] BYREF
  tm *tm; // [rsp+1A8h] [rbp-28h]
  time_t _t; // [rsp+1B0h] [rbp-20h] BYREF
  int32_t temp; // [rsp+1B8h] [rbp-18h]
  int ubik_op; // [rsp+1BCh] [rbp-14h]
  const u_char *bp_0a; // [rsp+1C0h] [rbp-10h]
  netdissect_options *ndoa; // [rsp+1C8h] [rbp-8h]

  ndoa = ndo;
  bp_0a = bp_0;
  ubik_op = EXTRACT_32BITS(bp_0 + 28);
  ndo_printf = ndo->ndo_printf;
  v2 = tok2str(&ubik_req, "op#%d", ubik_op);
  ndo_printf(ndo, " ubik call %s", v2);
  bp_0a = bp_0 + 32;
  if ( ubik_op == 10000 )
  {
    if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
    {
      temp = EXTRACT_32BITS(bp_0a);
      bp_0a += 4;
      v3 = "no";
      if ( temp )
        v3 = "yes";
      ndoa->ndo_printf(ndoa, " syncsite %s", v3);
      ndoa->ndo_printf(ndoa, " votestart");
      if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
      {
        _t = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        tm = localtime(&_t);
        strftime(str, 0x100uLL, "%Y/%m/%d %H:%M:%S", tm);
        ndoa->ndo_printf(ndoa, " %s", str);
        ndoa->ndo_printf(ndoa, " dbversion");
        if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
        {
          epoch = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          counter = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          ndoa->ndo_printf(ndoa, " %d.%d", epoch, counter);
          ndoa->ndo_printf(ndoa, " tid");
          if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
          {
            epoch_0 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            counter_0 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            ndoa->ndo_printf(ndoa, " %d.%d", epoch_0, counter_0);
            return;
          }
        }
      }
    }
trunc:
    ndoa->ndo_printf(ndoa, " [|ubik]");
    return;
  }
  if ( ubik_op == 10003 )
  {
    ndoa->ndo_printf(ndoa, " site");
    if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
    {
      _i = EXTRACT_32BITS(bp_0a);
      bp_0a += 4;
      ndoa->ndo_printf(ndoa, " %lu", _i);
      return;
    }
    goto trunc;
  }
  if ( (unsigned int)(ubik_op - 20000) < 2 )
    goto LABEL_32;
  switch ( ubik_op )
  {
    case 20002:
      ndoa->ndo_printf(ndoa, " tid");
      if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
      {
        epoch_2 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        counter_2 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        ndoa->ndo_printf(ndoa, " %d.%d", epoch_2, counter_2);
        ndoa->ndo_printf(ndoa, " file");
        if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
        {
          _i_0 = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          ndoa->ndo_printf(ndoa, " %d", _i_0);
          ndoa->ndo_printf(ndoa, " pos");
          if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
          {
            _i_1 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            ndoa->ndo_printf(ndoa, " %d", _i_1);
            ndoa->ndo_printf(ndoa, " length");
            if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
            {
              _i_2 = EXTRACT_32BITS(bp_0a);
              bp_0a += 4;
              ndoa->ndo_printf(ndoa, " %d", _i_2);
              temp = EXTRACT_32BITS(bp_0a);
              bp_0a += 4;
              tok2str(&ubik_lock_types, "type %d", temp);
              return;
            }
          }
        }
      }
      goto trunc;
    case 20003:
      ndoa->ndo_printf(ndoa, " tid");
      if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
      {
        epoch_3 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        counter_3 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        ndoa->ndo_printf(ndoa, " %d.%d", epoch_3, counter_3);
        ndoa->ndo_printf(ndoa, " file");
        if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
        {
          _i_3 = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          ndoa->ndo_printf(ndoa, " %d", _i_3);
          ndoa->ndo_printf(ndoa, " pos");
          if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
          {
            _i_4 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            ndoa->ndo_printf(ndoa, " %d", _i_4);
            return;
          }
        }
      }
      goto trunc;
    case 20005:
      ndoa->ndo_printf(ndoa, " file");
      if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
      {
        _i_5 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        ndoa->ndo_printf(ndoa, " %d", _i_5);
        return;
      }
      goto trunc;
    case 20006:
      ndoa->ndo_printf(ndoa, " file");
      if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
      {
        _i_6 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        ndoa->ndo_printf(ndoa, " %d", _i_6);
        ndoa->ndo_printf(ndoa, " length");
        if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
        {
          _i_7 = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          ndoa->ndo_printf(ndoa, " %d", _i_7);
          ndoa->ndo_printf(ndoa, " dbversion");
          if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
          {
            epoch_4 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            counter_4 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            ndoa->ndo_printf(ndoa, " %d.%d", epoch_4, counter_4);
            return;
          }
        }
      }
      goto trunc;
  }
  if ( (unsigned int)(ubik_op - 20007) < 2 )
    goto LABEL_32;
  switch ( ubik_op )
  {
    case 20009:
      ndoa->ndo_printf(ndoa, " tid");
      if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
      {
        epoch_5 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        counter_5 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        ndoa->ndo_printf(ndoa, " %d.%d", epoch_5, counter_5);
        ndoa->ndo_printf(ndoa, " file");
        if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
        {
          _i_8 = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          ndoa->ndo_printf(ndoa, " %d", _i_8);
          ndoa->ndo_printf(ndoa, " length");
          if ( ndoa->ndo_snapend - 4 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 4 )
          {
            _i_9 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            ndoa->ndo_printf(ndoa, " %d", _i_9);
            return;
          }
        }
      }
      goto trunc;
    case 20010:
LABEL_32:
      ndoa->ndo_printf(ndoa, " tid");
      if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
      {
        epoch_1 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        counter_1 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        ndoa->ndo_printf(ndoa, " %d.%d", epoch_1, counter_1);
        return;
      }
      goto trunc;
    case 20012:
      ndoa->ndo_printf(ndoa, " tid");
      if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
      {
        epoch_6 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        counter_6 = EXTRACT_32BITS(bp_0a);
        bp_0a += 4;
        ndoa->ndo_printf(ndoa, " %d.%d", epoch_6, counter_6);
        ndoa->ndo_printf(ndoa, " oldversion");
        if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
        {
          epoch_7 = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          counter_7 = EXTRACT_32BITS(bp_0a);
          bp_0a += 4;
          ndoa->ndo_printf(ndoa, " %d.%d", epoch_7, counter_7);
          ndoa->ndo_printf(ndoa, " newversion");
          if ( ndoa->ndo_snapend - 8 <= ndoa->ndo_snapend && bp_0a <= ndoa->ndo_snapend - 8 )
          {
            epoch_8 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            counter_8 = EXTRACT_32BITS(bp_0a);
            bp_0a += 4;
            ndoa->ndo_printf(ndoa, " %d.%d", epoch_8, counter_8);
            return;
          }
        }
      }
      goto trunc;
  }
}