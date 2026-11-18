/* cve_barebone direct-call harness for CVE-2024-5535 (openssl SSL_select_next_proto)
 * Self-contained: only libc includes, real #defines copied from
 * include/openssl/ssl.h.in, and SSL_select_next_proto pasted byte-for-byte
 * from target/original_function.c. Links with just -lm.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* real constants, copied verbatim from include/openssl/ssl.h.in */
# define OPENSSL_NPN_UNSUPPORTED 0
# define OPENSSL_NPN_NEGOTIATED  1
# define OPENSSL_NPN_NO_OVERLAP  2

/* ---- BEGIN verbatim copy of target/original_function.c ---- */
int SSL_select_next_proto(unsigned char **out, unsigned char *outlen,
                          const unsigned char *server,
                          unsigned int server_len,
                          const unsigned char *client, unsigned int client_len)
{
    unsigned int i, j;
    const unsigned char *result;
    int status = OPENSSL_NPN_UNSUPPORTED;

    /*
     * For each protocol in server preference order, see if we support it.
     */
    for (i = 0; i < server_len;) {
        for (j = 0; j < client_len;) {
            if (server[i] == client[j] &&
                memcmp(&server[i + 1], &client[j + 1], server[i]) == 0) {
                /* We found a match */
                result = &server[i];
                status = OPENSSL_NPN_NEGOTIATED;
                goto found;
            }
            j += client[j];
            j++;
        }
        i += server[i];
        i++;
    }

    /* There's no overlap between our protocols and the server's list. */
    result = client;
    status = OPENSSL_NPN_NO_OVERLAP;

 found:
    *out = (unsigned char *)result + 1;
    *outlen = result[0];
    return status;
}
/* ---- END verbatim copy of target/original_function.c ---- */

/*
 * Driver: read argv[1] as a file into a HEAP buffer, use it to build the
 * (server, server_len, client, client_len) arguments and call
 * SSL_select_next_proto directly.
 *
 * File layout (all lengths are attacker-controlled bytes from the file):
 *   byte 0        : client_len (0-255)
 *   byte 1        : server_len (0-255)
 *   next server_len bytes : server list bytes (copied into its own malloc)
 *   next client_len bytes : client list bytes (copied into its own malloc)
 *
 * server/client are each allocated with EXACTLY their declared length
 * (malloc(0) for a declared length of 0), so any out-of-bounds access the
 * function itself makes is caught by ASAN as a heap-buffer-overflow -- this
 * is CVE-2024-5535: when client_len == 0, the inner loop body never runs for
 * any i, so the function falls through to the "no overlap" path and reads
 * result[0] == client[0], a 1-byte heap-buffer-overflow READ when client
 * was allocated with size 0.
 */
int main(int argc, char **argv)
{
    if (argc < 2)
        return 0;

    FILE *f = fopen(argv[1], "rb");
    if (!f)
        return 0;

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long fsz = ftell(f);
    if (fsz < 2) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    unsigned char *filebuf = (unsigned char *)malloc((size_t)fsz);
    if (!filebuf) { fclose(f); return 0; }
    if (fread(filebuf, 1, (size_t)fsz, f) != (size_t)fsz) {
        fclose(f);
        free(filebuf);
        return 0;
    }
    fclose(f);

    unsigned int client_len = (unsigned int)filebuf[0];
    unsigned int server_len = (unsigned int)filebuf[1];

    long need = 2L + (long)server_len + (long)client_len;
    if (fsz < need) {
        free(filebuf);
        return 0;
    }

    /* heap-allocate server/client with EXACT declared sizes (ASAN-guarded) */
    unsigned char *server = (unsigned char *)malloc(server_len);
    unsigned char *client = (unsigned char *)malloc(client_len);
    if (server_len > 0 && server == NULL) { free(filebuf); free(server); free(client); return 0; }
    if (client_len > 0 && client == NULL) { free(filebuf); free(server); free(client); return 0; }

    if (server_len > 0)
        memcpy(server, filebuf + 2, server_len);
    if (client_len > 0)
        memcpy(client, filebuf + 2 + server_len, client_len);

    free(filebuf);

    unsigned char *out = NULL;
    unsigned char outlen = 0;

    int status = SSL_select_next_proto(&out, &outlen, server, server_len,
                                        client, client_len);

    printf("status=%d outlen=%u\n", status, (unsigned int)outlen);

    free(server);
    free(client);
    return 0;
}
