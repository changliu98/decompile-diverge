int file_type_to_content_type(int file_type)

{
  int file_type_local;
  uint local_c;
  
  switch(file_type) {
  case 0x80:
    local_c = ct_webp;
    break;
  case 0x81:
    local_c = ct_unknown;
    break;
  case 0x82:
    local_c = ct_png;
    break;
  case 0x83:
    local_c = ct_pdf;
    break;
  case 0x84:
    local_c = ct_partial;
    break;
  case 0x85:
    local_c = ct_mp4;
    break;
  case 0x86:
    local_c = ct_mp3;
    break;
  case 0x87:
    local_c = ct_mov;
    break;
  case 0x88:
    local_c = ct_jpeg;
    break;
  case 0x89:
    local_c = ct_gif;
    break;
  default:
    local_c = ct_last | 0x40000000;
  }
  return local_c;
}