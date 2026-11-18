int __cdecl SSL_select_next_proto(
        unsigned __int8 **out,
        unsigned __int8 *outlen,
        const unsigned __int8 *server,
        unsigned int server_len,
        const unsigned __int8 *client,
        unsigned int client_len)
{
  int status; // [rsp+Ch] [rbp-44h]
  const unsigned __int8 *result; // [rsp+10h] [rbp-40h]
  unsigned int j; // [rsp+1Ch] [rbp-34h]
  unsigned int i; // [rsp+20h] [rbp-30h]

  for ( i = 0; i < server_len; i += server[i] + 1 )
  {
    for ( j = 0; j < client_len; j += client[j] + 1 )
    {
      if ( server[i] == client[j] && !memcmp(&server[i + 1], &client[j + 1], server[i]) )
      {
        result = &server[i];
        status = 1;
        goto found;
      }
    }
  }
  result = client;
  status = 2;
found:
  *out = (unsigned __int8 *)(result + 1);
  *outlen = *result;
  return status;
}