// local variable allocation has failed, the output may be wrong!
void __cdecl ex_history(exarg_T *eap)
{
  size_t v1; // rax
  char *v2; // rax
  __int64 v3; // rdx
  int v4; // eax
  char_u *v5; // [rsp+0h] [rbp-90h]
  char_u *s; // [rsp+8h] [rbp-88h]
  char_u *buf; // [rsp+10h] [rbp-80h]
  int room_in; // [rsp+1Ch] [rbp-74h]
  int v9; // [rsp+2Ch] [rbp-64h]
  int hisnum; // [rsp+38h] [rbp-58h]
  bool v11; // [rsp+3Fh] [rbp-51h]
  bool v12; // [rsp+4Fh] [rbp-41h]
  char_u *arg; // [rsp+50h] [rbp-40h]
  char_u *end; // [rsp+58h] [rbp-38h] BYREF
  unsigned __int64 k; // [rsp+60h] [rbp-30h] OVERLAPPED
  int i; // [rsp+68h] [rbp-28h]
  int idx; // [rsp+6Ch] [rbp-24h]
  int hisidx2; // [rsp+70h] [rbp-20h] BYREF
  int hisidx1; // [rsp+74h] [rbp-1Ch] BYREF
  int histype2; // [rsp+78h] [rbp-18h]
  int histype1; // [rsp+7Ch] [rbp-14h]
  histentry_T *hist; // [rsp+80h] [rbp-10h]
  exarg_T *eapa; // [rsp+88h] [rbp-8h]

  eapa = eap;
  histype1 = 0;
  histype2 = 0;
  hisidx1 = 1;
  hisidx2 = -1;
  arg = eap->arg;
  if ( !hislen )
  {
    msg("'history' option is zero");
    return;
  }
  if ( (unsigned int)*arg - 48 < 0xA || *arg == 45 || *arg == 44 )
  {
    end = eap->arg;
  }
  else
  {
    for ( end = eap->arg; ; ++end )
    {
      if ( *end < 0x41u || (v12 = 1, *end > 0x5Au) )
      {
        if ( *end < 0x61u || (v12 = 1, *end > 0x7Au) )
          v12 = vim_strchr((char_u *)":=@>/?", *end) != 0LL;
      }
      if ( !v12 )
        break;
    }
    i = *end;
    *end = 0;
    histype1 = get_histtype(arg);
    if ( histype1 == -1 )
    {
      v1 = strlen((const char *)arg);
      if ( strncasecmp((const char *)arg, "all", v1) )
      {
        *end = i;
        semsg("E488: Trailing characters: %s", (const char *)arg);
        return;
      }
      histype1 = 0;
      histype2 = 4;
    }
    else
    {
      histype2 = histype1;
    }
    *end = i;
  }
  if ( get_list_range(&end, &hisidx1, &hisidx2) && !*end )
  {
    while ( 1 )
    {
      v11 = 0;
      if ( !got_int )
        v11 = histype1 <= histype2;
      if ( !v11 )
        break;
      strcpy((char *)IObuff, "\n      #  ");
      v2 = strcat((char *)IObuff, history_names[histype1]);
      strcat(v2, " history");
      msg_puts_title((char *)IObuff);
      idx = hisidx[histype1];
      hist = (histentry_T *)history[histype1];
      k = __PAIR64__(hisidx1, hisidx2);
      if ( hisidx1 < 0 )
      {
        if ( -HIDWORD(k) <= hislen )
          hisnum = hist[(idx + HIDWORD(k) + hislen + 1) % hislen].hisnum;
        else
          hisnum = 0;
        HIDWORD(k) = hisnum;
      }
      if ( (k & 0x80000000) != 0LL )
      {
        if ( -(int)k <= hislen )
          v9 = hist[(idx + (int)k + hislen + 1) % hislen].hisnum;
        else
          v9 = 0;
        LODWORD(k) = v9;
      }
      if ( idx >= 0 && SHIDWORD(k) <= (int)k )
      {
        for ( i = idx + 1; !got_int; ++i )
        {
          if ( i == hislen )
            i = 0;
          if ( hist[i].hisstr && hist[i].hisnum >= SHIDWORD(k) && hist[i].hisnum <= (int)k )
          {
            msg_putchar(10);
            v3 = 32LL;
            if ( i == idx )
              v3 = 62LL;
            sprintf((char *)IObuff, "%c%6d  ", v3, (unsigned int)hist[i].hisnum);
            if ( vim_strsize(hist[i].hisstr) <= (int)Columns - 10 )
            {
              strcat((char *)IObuff, (const char *)hist[i].hisstr);
            }
            else
            {
              s = hist[i].hisstr;
              v5 = IObuff;
              buf = &v5[strlen((const char *)IObuff)];
              room_in = (_DWORD)Columns - 10;
              v4 = strlen((const char *)IObuff);
              trunc_string(s, buf, room_in, 1025 - v4);
            }
            msg_outtrans(IObuff);
            out_flush();
          }
          if ( i == idx )
            break;
        }
      }
      ++histype1;
    }
  }
  else
  {
    semsg("E488: Trailing characters: %s", (const char *)end);
  }
}