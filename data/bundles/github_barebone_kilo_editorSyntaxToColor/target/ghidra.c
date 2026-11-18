int editorSyntaxToColor(int hl)

{
  int hl_local;
  int local_c;
  
  switch(hl) {
  case 2:
  case 3:
    local_c = 0x24;
    break;
  case 4:
    local_c = 0x21;
    break;
  case 5:
    local_c = 0x20;
    break;
  case 6:
    local_c = 0x23;
    break;
  case 7:
    local_c = 0x1f;
    break;
  case 8:
    local_c = 0x22;
    break;
  default:
    local_c = 0x25;
  }
  return local_c;
}