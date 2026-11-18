void clearMarker(char *string, char marker) {
  char *p;
  p = strchr(string, marker);
  if (p) {
    *p = '\0';
  }
}