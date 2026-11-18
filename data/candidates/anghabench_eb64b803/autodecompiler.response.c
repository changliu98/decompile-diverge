static int
file_type_to_content_type(int type)
{
  int ret;

  switch(type) {
  case ic_jpeg:
    ret = ct_jpeg;
    break;
  case ic_gif:
    ret = ct_gif;
    break;
  case ic_png:
    ret = ct_png;
    break;
  case ic_pdf:
    ret = ct_pdf;
    break;
  case ic_mp3:
    ret = ct_mp3;
    break;
  case ic_mov:
    ret = ct_mov;
    break;
  case ic_mp4:
    ret = ct_mp4;
    break;
  case ic_partial:
    ret = ct_partial;
    break;
  case ic_webp:
    ret = ct_webp;
    break;
  case ic_unknown:
    ret = ct_unknown;
    break;
  default:
    ret = ct_last | (1 << 30);
  }

  return ret;
}