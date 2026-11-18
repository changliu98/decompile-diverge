int ExtractRnick(char *Rnick,char *incoming_msg)

{
  bool bVar1;
  int k;
  char *incoming_msg_local;
  char *Rnick_local;
  uint local_c;
  
  k = 0;
  incoming_msg_local = incoming_msg;
  if (*incoming_msg == ':') {
    incoming_msg_local = incoming_msg + 1;
  }
  while( true ) {
    bVar1 = false;
    if (*incoming_msg_local != '!') {
      bVar1 = *incoming_msg_local != '\0';
    }
    if (!bVar1) break;
    Rnick[k] = *incoming_msg_local;
    incoming_msg_local = incoming_msg_local + 1;
    k = k + 1;
  }
  Rnick[k] = '\0';
  local_c = (uint)('/' < *Rnick);
  return local_c;
}