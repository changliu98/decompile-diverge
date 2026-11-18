#include <string.h>

static int set_filename(char *to_name, char *from_name) {
  while (*from_name != '\0') {
    if (*from_name == '/') {
      *to_name = '\0';
      return 2;
    }
    *to_name = *from_name;
    to_name++;
    from_name++;
  }
  *to_name = '\0';
  return 1;
}
