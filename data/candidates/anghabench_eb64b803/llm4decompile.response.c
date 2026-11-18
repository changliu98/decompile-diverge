content_type_t file_type_to_content_type(file_type_t file_type) {
  content_type_t ct;
  switch (file_type) {
    case ft_partial:
      ct = ct_partial;
      break;
    case ft_jpeg:
      ct = ct_jpeg;
      break;
    case ft_png:
      ct = ct_png;
      break;
    case ft_gif:
      ct = ct_gif;
      break;
    case ft_webp:
      ct = ct_webp;
      break;
    case ft_mp3:
      ct = ct_mp3;
      break;
    case ft_mp4:
      ct = ct_mp4;
      break;
    case ft_mov:
      ct = ct_mov;
      break;
    case ft_pdf:
      ct = ct_pdf;
      break;
    case ft_unknown:
      ct = ct_unknown;
      break;
    default:
      ct = (content_type_t)(ct_last | 0x40000000);
  }
  return ct;
}