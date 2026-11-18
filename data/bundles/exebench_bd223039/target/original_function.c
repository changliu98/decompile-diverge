void clearMarker(char * s, char marker)
{
 char * pos;

 if ((pos = strchr(s, marker)) != NULL) {
  *pos = '\0';
 }
}