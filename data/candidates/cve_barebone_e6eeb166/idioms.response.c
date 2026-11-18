int SSL_select_next_proto(unsigned char **next_hop, unsigned char *next_hop_len, unsigned char *server, unsigned int server_len, unsigned char *client, unsigned int client_len)
{
    int i; int j;
    unsigned char *next;
    int status;
    for (i = 0; i < server_len; i += server[i] + 1) {
        for (j = 0; j < client_len; j += client[j] + 1) {
            if (server[i] == client[j] &&
                sios_ll_llcp_is_llcp_end(&server[i + 1],
                                         &client[j + 1],
                                         server[i]) == 0) {
                next = &server[i];
                status = 1;
                goto found;
            }
        }
    }
    next = client;
    status = 2;
found:
    *next_hop = next + 1;
    *next_hop_len = *next;
    return (status);
}