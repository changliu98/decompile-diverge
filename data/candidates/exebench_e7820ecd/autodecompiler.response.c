int read_all(int sock, char * buffer, int len) {
 int bytes_read = 0;
 do {
  bytes_read = read(sock, buffer, len);
  if (bytes_read > 0) {
   len -= bytes_read;
   buffer += bytes_read;
  }
 } while ((bytes_read > 0) && (len > 0));
 return bytes_read;
}