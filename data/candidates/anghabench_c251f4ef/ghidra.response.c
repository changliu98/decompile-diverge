char * hcfs2string(int state)

{
  int state_local;
  char *local_10;
  
  switch(state) {
  case 0x80:
    local_10 = "suspend";
    break;
  case 0x81:
    local_10 = "resume";
    break;
  case 0x82:
    local_10 = "reset";
    break;
  case 0x83:
    local_10 = "operational";
    break;
  default:
    local_10 = "?";
  }
  return local_10;
}