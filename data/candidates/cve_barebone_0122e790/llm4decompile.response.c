char *parse_content_length(char *buffer, char *end, int *length)
{
 int number = 0;
 int size = 0;

 while (((buffer < end) && ((((*buffer) == ' ') || ((*buffer) == '\t')) || (((*buffer) == '\r') && ((*(buffer + 1)) == '\n')) || (((*buffer) == '\n') && (((*(buffer + 1)) == ' ') || ((*(buffer + 1)) == '\t')))))) buffer++;

 while (((buffer < end) && (((*buffer) >= '0') && ((*buffer) <= '9')))) {
  number = number * 10 + (*buffer) - '0';
  if (number < 0) return NULL;
  size++;
  buffer++;
 }

 if ((buffer == end) || (size == 0)) return NULL;

 while (((buffer < end) && ((((*buffer) == ' ') || ((*buffer) == '\t')) || (((*buffer) == '\n') && (((*(buffer + 1)) == ' ') || ((*(buffer + 1)) == '\t')))))) buffer++;

 if ((buffer == end) || (((*buffer) != '\n') && (((*buffer) != '\r') || ((*(buffer + 1)) != '\n')))) return NULL;

 if ((*buffer) == '\n') {
  buffer++;
 } else {
  buffer += 2;
 }

 *length = number;

 return buffer;
}