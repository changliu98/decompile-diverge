void basename_discriminant(const char* filename, long* h, long* len) {
 const char* stt = strrchr(filename, '/');
 if (!stt)
  stt = filename;
 else
  stt++;

 *len = 0;

 *h = 0;
 while (*stt) {
  *h *= 33;
  *h += *stt++;
  ++*len;
 }
}