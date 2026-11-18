int SSL_select_next_proto
              (uchar **out,uchar *outlen,uchar *server,uint server_len,uchar *client,uint client_len
              )

{
  int iVar1;
  int status;
  uchar *result;
  uint j;
  uint i;
  uint client_len_local;
  uchar *client_local;
  uint server_len_local;
  uchar *server_local;
  uchar *outlen_local;
  uchar **out_local;
  
  i = 0;
  do {
    if (server_len <= i) {
      status = 2;
      result = client;
LAB_001012da:
      *out = result + 1;
      *outlen = *result;
      return status;
    }
    for (j = 0; j < client_len; j = client[j] + j + 1) {
      if (server[i] == client[j]) {
        iVar1 = memcmp(server + (i + 1),client + (j + 1),(ulong)server[i]);
        if (iVar1 == 0) {
          result = server + i;
          status = 1;
          goto LAB_001012da;
        }
      }
    }
    i = server[i] + i + 1;
  } while( true );
}