int file_type_to_content_type (int file_type) {
  switch (file_type) {
    case TL_STORAGE_FILE_UNKNOWN: return ct_unknown;
    case TL_STORAGE_FILE_JPEG: return ct_jpeg;
    case TL_STORAGE_FILE_GIF: return ct_gif;
    case TL_STORAGE_FILE_PNG: return ct_png;
    case TL_STORAGE_FILE_PDF: return ct_pdf;
    case TL_STORAGE_FILE_MP3: return ct_mp3;
    case TL_STORAGE_FILE_MOV: return ct_mov;
    case TL_STORAGE_FILE_MP4: return ct_mp4;
    case TL_STORAGE_FILE_PARTIAL: return ct_partial;
    case TL_STORAGE_FILE_WEBP: return ct_webp;
  }
  return ct_last | 0x40000000;
}