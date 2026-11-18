char * get_priority_string(int prio)

{
  int prio_local;
  char *local_10;
  
  switch(prio) {
  case 0x80:
    local_10 = "Unavailable";
    break;
  case 0x81:
    local_10 = "Preferred";
    break;
  case 0x82:
    local_10 = "Neutral";
    break;
  case 0x83:
    local_10 = "Low";
    break;
  default:
    local_10 = "Invalid";
  }
  return local_10;
}