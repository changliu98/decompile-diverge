_Bool type_marker_to_cmp_type(uint8_t type_marker,uint8_t *cmp_type)

{
  uint8_t *cmp_type_local;
  uint8_t type_marker_local;
  _Bool local_9;
  
  if (type_marker < 0x80) {
    *cmp_type = '\0';
    local_9 = true;
  }
  else if (type_marker < 0x90) {
    *cmp_type = '\x01';
    local_9 = true;
  }
  else if (type_marker < 0xa0) {
    *cmp_type = '\x02';
    local_9 = true;
  }
  else if (type_marker < 0xc0) {
    *cmp_type = '\x03';
    local_9 = true;
  }
  else if (type_marker < 0xe0) {
    switch(type_marker) {
    case 0xc0:
      *cmp_type = '\x04';
      local_9 = true;
      break;
    default:
      local_9 = false;
      break;
    case 0xc2:
      *cmp_type = '\x05';
      local_9 = true;
      break;
    case 0xc3:
      *cmp_type = '\x05';
      local_9 = true;
      break;
    case 0xc4:
      *cmp_type = '\x06';
      local_9 = true;
      break;
    case 0xc5:
      *cmp_type = '\a';
      local_9 = true;
      break;
    case 0xc6:
      *cmp_type = '\b';
      local_9 = true;
      break;
    case 199:
      *cmp_type = '\t';
      local_9 = true;
      break;
    case 200:
      *cmp_type = '\n';
      local_9 = true;
      break;
    case 0xc9:
      *cmp_type = '\v';
      local_9 = true;
      break;
    case 0xca:
      *cmp_type = '\f';
      local_9 = true;
      break;
    case 0xcb:
      *cmp_type = '\r';
      local_9 = true;
      break;
    case 0xcc:
      *cmp_type = '\x0e';
      local_9 = true;
      break;
    case 0xcd:
      *cmp_type = '\x0f';
      local_9 = true;
      break;
    case 0xce:
      *cmp_type = '\x10';
      local_9 = true;
      break;
    case 0xcf:
      *cmp_type = '\x11';
      local_9 = true;
      break;
    case 0xd0:
      *cmp_type = '\x12';
      local_9 = true;
      break;
    case 0xd1:
      *cmp_type = '\x13';
      local_9 = true;
      break;
    case 0xd2:
      *cmp_type = '\x14';
      local_9 = true;
      break;
    case 0xd3:
      *cmp_type = '\x15';
      local_9 = true;
      break;
    case 0xd4:
      *cmp_type = '\x16';
      local_9 = true;
      break;
    case 0xd5:
      *cmp_type = '\x17';
      local_9 = true;
      break;
    case 0xd6:
      *cmp_type = '\x18';
      local_9 = true;
      break;
    case 0xd7:
      *cmp_type = '\x19';
      local_9 = true;
      break;
    case 0xd8:
      *cmp_type = '\x1a';
      local_9 = true;
      break;
    case 0xd9:
      *cmp_type = '\x1b';
      local_9 = true;
      break;
    case 0xda:
      *cmp_type = '\x1c';
      local_9 = true;
      break;
    case 0xdb:
      *cmp_type = '\x1d';
      local_9 = true;
      break;
    case 0xdc:
      *cmp_type = '\x1e';
      local_9 = true;
      break;
    case 0xdd:
      *cmp_type = '\x1f';
      local_9 = true;
      break;
    case 0xde:
      *cmp_type = ' ';
      local_9 = true;
      break;
    case 0xdf:
      *cmp_type = '!';
      local_9 = true;
    }
  }
  else {
    *cmp_type = '\"';
    local_9 = true;
  }
  return local_9;
}