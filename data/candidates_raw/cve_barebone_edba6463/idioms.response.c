void JPEGActualComment(unsigned char *data, int length)
{
  int i; int c; int nch = 0;
  char comment[16001];
  if (length > 16000)
    length = 16000;
  for (i = 2; i < length; i++) {
    c = data[i];
    if (c == '\r' && data[i+1] == '\n')
      continue;
    if (c < ' ' && c != '\n' && c != '\t')
      comment[nch++] = '?';
    else
      comment[nch++] = c;
  }
  comment[nch] = '\0';
  if (ShowTags)
    JPEGActualCommentEx("COM marker comment: %s\n", comment);
  SetExifTag(ImageInfo, comment);
}