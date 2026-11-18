define SSL_TLSEXT_ERR_NOACK 2

int __cdecl SSL_select_next_proto(
        unsigned char **out,
        unsigned char *outlen,
        const unsigned char *server,
        unsigned int server_len,
        const unsigned char *client,
        unsigned int client_len)
{
  const unsigned char *result;
  int status;

  // Iterate over the server's list of protocols.
  // Each protocol is prefixed by a length byte, hence the `server[i] + 1` step.
  for (unsigned int i = 0; i < server_len; i += server[i] + 1)
  {
    // Iterate over the client's list of protocols.
    for (unsigned int j = 0; j < client_len; j += client[j] + 1)
    {
      // Compare lengths first, then compare the actual protocol bytes
      if (server[i] == client[j] && !memcmp(&server[i + 1], &client[j + 1], server[i]))
      {
        result = &server[i];
        status = SSL_OPEN_NPN;
        goto found;
      }
    }
  }

  // Fallback: No overlap between server and client protocols.
  // Default to the first protocol in the client's list.
  result = client;
  status = SSL_TLSEXT_ERR_NOACK;

found:
  // Output the selected protocol (skipping the length prefix byte)
  *out = (unsigned char *)(result + 1);
  *outlen = *result;
  return status;
}