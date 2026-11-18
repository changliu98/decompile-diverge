static unsigned file_type_to_content_type(file_type_t type) {
  unsigned content_type;
  switch (type) {
    case FILE_TYPE_UNKNOWN:
      content_type = CONTENT_TYPE_UNKNOWN;
      break;
    case FILE_TYPE_TEXT:
      content_type = CONTENT_TYPE_TEXT;
      break;
    case FILE_TYPE_IMAGE:
      content_type = CONTENT_TYPE_IMAGE;
      break;
    case FILE_TYPE_AUDIO:
      content_type = CONTENT_TYPE_AUDIO;
      break;
    case FILE_TYPE_VIDEO:
      content_type = CONTENT_TYPE_VIDEO;
      break;
    case FILE_TYPE_DOCUMENT:
      content_type = CONTENT_TYPE_DOCUMENT;
      break;
    case FILE_TYPE_EXECUTABLE:
      content_type = CONTENT_TYPE_EXECUTABLE;
      break;
    case FILE_TYPE_FONT:
      content_type = CONTENT_TYPE_FONT;
      break;
    case FILE_TYPE_ARCHIVE:
      content_type = CONTENT_TYPE_ARCHIVE;
      break;
    case FILE_TYPE_SYMLINK:
      content_type = CONTENT_TYPE_SYMLINK;
      break;
    default:
      content_type = (0x40000000 | CONTENT_TYPE_OTHER);
      break;
  }
  return content_type;
}