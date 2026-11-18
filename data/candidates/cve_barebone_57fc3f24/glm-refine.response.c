void __cdecl handle_PORT(ctrl_t *ctrl, char *str)
{
  sockaddr_in sin; 
  char addr[16]; 
  int a, b, c, d, e, f; 

  // If a data connection is already active, clean it up before establishing a new one
  if ( ctrl->data_sd > 0 )
  {
    uev_io_stop(&ctrl->data_watcher);
    close(ctrl->data_sd);
    ctrl->data_sd = -1;
  }

  // IDA failed to resolve the arguments for sscanf, but based on the FTP PORT command 
  // format (e.g., "PORT 192,168,1,10,255,128"), it parses 6 comma-separated integers.
  // a,b,c,d represent the IPv4 octets. e,f represent the port (e is MSB, f is LSB).
  __isoc99_sscanf(str, "%d,%d,%d,%d,%d,%d", &a, &b, &c, &d, &e, &f);

  // Reconstruct the standard dotted-decimal IPv4 string
  sprintf(addr, "%d.%d.%d.%d", (unsigned int)a, (unsigned int)b, (unsigned int)c, (unsigned int)d);

  // Validate the IP address
  if ( inet_aton(addr, &sin.sin_addr) )
  {
    // Store the parsed IP and port (port = e * 256 + f)
    strlcpy(ctrl->data_address, addr, 0x10uLL);
    ctrl->data_port = f + (e << 8);
    send_msg(ctrl->sd, "200 PORT command successful.\r\n");
  }
  else
  {
    send_msg(ctrl->sd, "500 Illegal PORT command.\r\n");
  }
}