void __cdecl special_keys(char_u *args)
{
  int v1; // eax
  int v2; // [rsp+8h] [rbp-168h]
  int i; // [rsp+Ch] [rbp-164h]
  char cmdbuf[256]; // [rsp+10h] [rbp-160h] BYREF
  char keybuf[64]; // [rsp+110h] [rbp-60h] BYREF
  char *sep; // [rsp+150h] [rbp-20h]
  char *tok; // [rsp+158h] [rbp-18h]
  char *save_str; // [rsp+160h] [rbp-10h]
  char_u *argsa; // [rsp+168h] [rbp-8h]

  argsa = args;
  save_str = nb_unquote(args, 0LL);
  for ( tok = strtok(save_str, " "); tok; tok = strtok(0LL, " ") )
  {
    i = 0;
    sep = strchr(tok, 45);
    if ( sep )
    {
      *sep = 0;
      while ( *tok )
      {
        v2 = *tok;
        if ( v2 == 65 || v2 == 67 || v2 == 77 || v2 == 83 )
        {
          keybuf[i] = *tok;
          v1 = i + 1;
          i += 2;
          keybuf[v1] = 45;
        }
        ++tok;
      }
      ++tok;
    }
    if ( i + strlen(tok) < 0x40 )
    {
      strcpy(&keybuf[i], tok);
      vim_snprintf(cmdbuf, 0x100uLL, "<silent><%s> :nbkey %s<CR>", keybuf, keybuf);
      do_map(0, (char_u *)cmdbuf, 1, 0);
    }
  }
  vim_free(save_str);
}