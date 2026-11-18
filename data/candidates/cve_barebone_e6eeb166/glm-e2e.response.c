int SSL_select_next_proto(unsigned char **out, unsigned char *outlen,
                          const unsigned char *server, unsigned int server_len,
                          const unsigned char *client, unsigned int client_len)
{
    int status = 0;
    unsigned int i = 0;
    const unsigned char *result = NULL;

    while (i < server_len) {
        unsigned int j = 0;
        while (j < client_len) {
            if (server[i] == client[j]) {
                if (memcmp(server + i + 1, client + j + 1, server[i]) == 0) {
                    result = server + i;
                    status = 1;
                    goto done;
                }
            }
            j += client[j] + 1;
        }
        i += server[i] + 1;
    }

    result = client;
    status = 2;

done:
    *out = result + 1;
    *outlen = *result;
    return status;
}