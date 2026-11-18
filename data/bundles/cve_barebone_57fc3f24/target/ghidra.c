void handle_PORT(ctrl_t *ctrl,char *str)

{
  int iVar1;
  sockaddr_in sin;
  char addr [16];
  int f;
  int e;
  int d;
  int c;
  int b;
  int a;
  char *str_local;
  ctrl_t *ctrl_local;
  
  str_local = str;
  ctrl_local = ctrl;
  if (0 < ctrl->data_sd) {
    uev_io_stop(&ctrl->data_watcher);
    close(ctrl_local->data_sd);
    ctrl_local->data_sd = -1;
  }
  __isoc99_sscanf(str_local,"%d,%d,%d,%d,%d,%d",&a,&b,&c,&d,&e,&f);
  sprintf(addr,"%d.%d.%d.%d",(ulong)(uint)a,(ulong)(uint)b,(ulong)(uint)c,(ulong)(uint)d);
  iVar1 = inet_aton(addr,(in_addr *)&sin.sin_addr);
  if (iVar1 == 0) {
    send_msg(ctrl_local->sd,"500 Illegal PORT command.\r\n");
  }
  else {
    strlcpy(ctrl_local->data_address,addr,0x10);
    ctrl_local->data_port = e * 0x100 + f;
    send_msg(ctrl_local->sd,"200 PORT command successful.\r\n");
  }
  return;
}