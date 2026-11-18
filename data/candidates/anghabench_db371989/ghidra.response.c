char * mg_status_message(int status_code)

{
  int status_code_local;
  char *local_10;
  
  if (status_code == 0xce) {
    local_10 = "Partial Content";
  }
  else if (status_code == 0x12d) {
    local_10 = "Moved";
  }
  else if (status_code == 0x12e) {
    local_10 = "Found";
  }
  else if (status_code == 400) {
    local_10 = "Bad Request";
  }
  else if (status_code == 0x191) {
    local_10 = "Unauthorized";
  }
  else if (status_code == 0x193) {
    local_10 = "Forbidden";
  }
  else if (status_code == 0x194) {
    local_10 = "Not Found";
  }
  else if (status_code == 0x1a0) {
    local_10 = "Requested Range Not Satisfiable";
  }
  else if (status_code == 0x1a2) {
    local_10 = "I\'m a teapot";
  }
  else if (status_code == 500) {
    local_10 = "Internal Server Error";
  }
  else if (status_code == 0x1f6) {
    local_10 = "Bad Gateway";
  }
  else if (status_code == 0x1f7) {
    local_10 = "Service Unavailable";
  }
  else {
    local_10 = "OK";
  }
  return local_10;
}