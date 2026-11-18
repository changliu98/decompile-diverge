int SSL_select_next_proto(unsigned char **out, unsigned char *outlen,
                          const unsigned char *server,
                          unsigned int server_len,
                          const unsigned char *client,
                          unsigned int client_len)
{
    unsigned int i, j;
    int found;

    for (i = 0; i < server_len; i += server[i] + 1) {
        for (j = 0; j < client_len; j += client[j] + 1) {
            if (server[i] == client[j]) {
                found = memcmp(server + i + 1, client + j + 1, server[i]);
                if (found == 0) {
                    *out = (unsigned char *)server + i;
                    *outlen = server[i];
                    return 1;
                }
            }
        }
    }

    *out = (unsigned char *)client;
    *outlen = client[0];
    return 2;
}