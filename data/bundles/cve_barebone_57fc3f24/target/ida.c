void __cdecl handle_PORT(ctrl_t *ctrl, char *str)
{
  sockaddr_in sin; // [rsp+10h] [rbp-50h] BYREF
  char addr[16]; // [rsp+20h] [rbp-40h] BYREF
  int f; // [rsp+38h] [rbp-28h]
  int e; // [rsp+3Ch] [rbp-24h]
  int d; // [rsp+40h] [rbp-20h]
  int c; // [rsp+44h] [rbp-1Ch]
  int b; // [rsp+48h] [rbp-18h]
  int a; // [rsp+4Ch] [rbp-14h]
  char *stra; // [rsp+50h] [rbp-10h]
  ctrl_t *ctrla; // [rsp+58h] [rbp-8h]

  ctrla = ctrl;
  stra = str;
  if ( ctrl->data_sd > 0 )
  {
    uev_io_stop(&ctrla->data_watcher);
    close(ctrla->data_sd);
    ctrla->data_sd = -1;
  }
  __isoc99_sscanf();
  sprintf(addr, "%d.%d.%d.%d", (unsigned int)a, (unsigned int)b, (unsigned int)c, (unsigned int)d);
  if ( inet_aton(addr, &sin.sin_addr) )
  {
    strlcpy(ctrla->data_address, addr, 0x10uLL);
    ctrla->data_port = f + (e << 8);
    send_msg(ctrla->sd, "200 PORT command successful.\r\n");
  }
  else
  {
    send_msg(ctrla->sd, "500 Illegal PORT command.\r\n");
  }
}