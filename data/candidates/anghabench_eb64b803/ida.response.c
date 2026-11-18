int __cdecl file_type_to_content_type(int file_type)
{
  int v2; // [rsp+Ch] [rbp-4h]

  switch ( file_type )
  {
    case 128:
      v2 = ct_webp;
      break;
    case 129:
      v2 = ct_unknown;
      break;
    case 130:
      v2 = ct_png;
      break;
    case 131:
      v2 = ct_pdf;
      break;
    case 132:
      v2 = ct_partial;
      break;
    case 133:
      v2 = ct_mp4;
      break;
    case 134:
      v2 = ct_mp3;
      break;
    case 135:
      v2 = ct_mov;
      break;
    case 136:
      v2 = ct_jpeg;
      break;
    case 137:
      v2 = ct_gif;
      break;
    default:
      v2 = ct_last | 0x40000000;
      break;
  }
  return v2;
}