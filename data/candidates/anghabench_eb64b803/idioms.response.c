int file_type_to_content_type(int file_type)
{
  int ct;
  switch (file_type) {
  case 128:
    ct = ct_webp;
    break;
  case 129:
    ct = ct_unknown;
    break;
  case 130:
    ct = ct_png;
    break;
  case 131:
    ct = ct_pdf;
    break;
  case 132:
    ct = ct_partial;
    break;
  case 133:
    ct = ct_mp4;
    break;
  case 134:
    ct = ct_mp3;
    break;
  case 135:
    ct = ct_mov;
    break;
  case 136:
    ct = ct_jpeg;
    break;
  case 137:
    ct = ct_gif;
    break;
  default:
    ct = ct_last | (1 << 29);
  }
  return ct;
}