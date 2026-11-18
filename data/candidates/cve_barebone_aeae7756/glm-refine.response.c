void __cdecl ex_history(exarg_T *eap)
{
  char_u *v5;
  char_u *s;
  char_u *buf;
  int room_in;
  int v9;
  int hisnum;
  bool v11;
  bool v12;
  char_u *arg;
  char_u *end;
  char_u end_char;
  int i;
  int idx;
  int hisidx2;
  int hisidx1;
  int histype2;
  int histype1;
  histentry_T *hist;

  histype1 = 0;
  histype2 = 0;
  hisidx1 = 1;
  hisidx2 = -1;
  arg = eap->arg;

  if (!hislen)
  {
    msg("'history' option is zero");
    return;
  }

  // Check if the first character is a digit (0-9), '-' (45), or ',' (44)
  if ((unsigned int)*arg - 48 < 0xA || *arg == 45 || *arg == 44)
  {
    end = eap->arg;
  }
  else
  {
    // Parse the history type string
    for (end = eap->arg; ; ++end)
    {
      v12 = 0;
      if (*end >= 0x41 && *end <= 0x5A)      // A-Z
        v12 = 1;
      else if (*end >= 0x61 && *end <= 0x7A) // a-z
        v12 = 1;
      else
        v12 = vim_strchr((char_u *)":=@>/?", *end) != 0LL;

      if (!v12)
        break;
    }

    end_char = *end;
    *end = 0;
    histype1 = get_histtype(arg);

    if (histype1 == -1)
    {
      if (strncasecmp((const char *)arg, "all", strlen((const char *)arg)))
      {
        *end = end_char;
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
    *end = end_char;
  }

  if (get_list_range(&end, &hisidx1, &hisidx2) && !*end)
  {
    while (1)
    {
      v11 = 0;
      if (!got_int)
        v11 = histype1 <= histype2;

      if (!v11)
        break;

      strcpy((char *)IObuff, "\n      #  ");
      strcat((char *)IObuff, history_names[histype1]);
      strcat((char *)IObuff, " history");
      msg_puts_title((char *)IObuff);

      idx = hisidx[histype1];
      hist = (histentry_T *)history[histype1];

      // Reconstruct the 64-bit overlapping variable `k` used by IDA
      unsigned __int64 k = PAIR64(hisidx1, hisidx2);
      int k_hi = hisidx1;
      int k_lo = hisidx2;

      if (k_hi < 0)
      {
        if (-k_hi <= hislen)
          hisnum = hist[(idx + k_hi + hislen + 1) % hislen].hisnum;
        else
          hisnum = 0;
        k_hi = hisnum;
      }

      if (k_lo < 0)
      {
        if (-k_lo <= hislen)
          v9 = hist[(idx + k_lo + hislen + 1) % hislen].hisnum;
        else
          v9 = 0;
        k_lo = v9;
      }

      if (idx >= 0 && k_hi <= k_lo)
      {
        for (i = idx + 1; !got_int; ++i)
        {
          if (i == hislen)
            i = 0;

          if (hist[i].hisstr && hist[i].hisnum >= k_hi && hist[i].hisnum <= k_lo)
          {
            msg_putchar(10);
            
            unsigned __int64 v3 = 32LL; // space character
            if (i == idx)
              v3 = 62LL;               // '>' character

            sprintf((char *)IObuff, "%c%6d  ", v3, (unsigned int)hist[i].hisnum);

            if (vim_strsize(hist[i].hisstr) <= (int)Columns - 10)
            {
              strcat((char *)IObuff, (const char *)hist[i].hisstr);
            }
            else
            {
              s = hist[i].hisstr;
              v5 = IObuff;
              buf = &v5[strlen((const char *)IObuff)];
              room_in = (int)Columns - 10;
              int v4 = strlen((const char *)IObuff);
              trunc_string(s, buf, room_in, 1025 - v4);
            }
            msg_outtrans(IObuff);
            out_flush();
          }

          if (i == idx)
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