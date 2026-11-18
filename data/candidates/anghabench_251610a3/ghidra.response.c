char * get_level_str(int level)

{
  int level_local;
  char *local_10;
  
  switch(level) {
  case 0x80:
    local_10 = "warning";
    break;
  case 0x81:
    local_10 = "verbose";
    break;
  case 0x82:
    local_10 = "quiet";
    break;
  case 0x83:
    local_10 = "panic";
    break;
  case 0x84:
    local_10 = "info";
    break;
  case 0x85:
    local_10 = "fatal";
    break;
  case 0x86:
    local_10 = "error";
    break;
  case 0x87:
    local_10 = "debug";
    break;
  default:
    local_10 = "";
  }
  return local_10;
}