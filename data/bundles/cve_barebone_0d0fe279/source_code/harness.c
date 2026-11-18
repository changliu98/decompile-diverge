/*
 * cve_0d0fe279 direct-call crash harness for nDPI's concat_hash_string()
 * (CVE-2020-11940 / CWE-125 heap-buffer-overflow READ in the SSH HASSH
 *  algorithm-string concatenator, src/lib/protocols/ssh.c).
 *
 * Root cause (visible in target/original_function.c, unchanged): after the
 * first bounds-checked strncpy of the ssh.kex_algorithms field, `offset` is
 * advanced past that field and then
 *
 *     len = ntohl(*(u_int32_t*)&packet->payload[offset]);        <-- ssh.c:114
 *
 * reads the NEXT 4-byte length WITHOUT any bounds check. The preceding guard
 * (len < payload_packet_len-offset-1) only bounds the FIRST field, so after
 * `offset += len` the 4-byte length read at ssh.c:114 can run up to 2 bytes
 * past packet->payload's end: heap-buffer-overflow READ (CWE-125), matching
 * the baseline dedup_token
 * "concat_hash_string--ndpi_search_ssh_tcp--search_ssh_again" (reached here
 * directly from main() in isolation, no ndpi_search_ssh_tcp scaffolding).
 *
 * Assembles:
 *   1. minimal REAL nDPI types: the BSD scalar typedefs (u_int8_t/u_int16_t/
 *      u_int32_t) via <sys/types.h>, and struct ndpi_packet_struct TRIMMED to
 *      the two fields concat_hash_string dereferences -- payload and
 *      payload_packet_len -- with their REAL names/types copied from
 *      src/include/ndpi_typedefs.h (lines 787, 819).
 *   2. the VERBATIM target function (below, byte-for-byte).
 *   3. main(): reads argv[1] into a HEAP buffer, peels off a leading
 *      client/server HASSH flag byte, copies the remaining bytes into a TIGHT
 *      heap payload chunk (so the trailing unchecked read overflows ASAN's
 *      redzone) and drives concat_hash_string directly, exactly as the real
 *      caller does (hassh_buf = ndpi_calloc(payload_packet_len, 1)).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>   /* BSD scalar typedefs: u_int8_t / u_int16_t / u_int32_t */
#include <arpa/inet.h>   /* ntohl */

/* ---- src/include/ndpi_typedefs.h, trimmed to the fields concat_hash_string
 * actually dereferences (payload @819-scope, payload_packet_len @819); real
 * field names + types, nothing renamed ---- */
struct ndpi_packet_struct {
  const u_int8_t *payload;
  u_int16_t payload_packet_len;
};

/* Keep the (static, single-call-site) target as its OWN frame in the ASAN
 * stack so dc_batch sees "concat_hash_string" at the fault. This prototype
 * changes NO bytes of the verbatim definition below. */
static u_int16_t concat_hash_string(struct ndpi_packet_struct *packet,
                                    char *buf, u_int8_t client_hash) __attribute__((noinline));

/* ==================================================================
 * verbatim target function -- data_cve/cve_0d0fe279/target/original_function.c
 * ================================================================== */
static u_int16_t concat_hash_string(struct ndpi_packet_struct *packet,
				   char *buf, u_int8_t client_hash) {
  u_int16_t offset = 22, buf_out_len = 0;
  if(offset+sizeof(u_int32_t) >= packet->payload_packet_len)
    goto invalid_payload;
  u_int32_t len = ntohl(*(u_int32_t*)&packet->payload[offset]);
  offset += 4;

  /* -1 for ';' */
  if((offset >= packet->payload_packet_len) || (len >= packet->payload_packet_len-offset-1))
    goto invalid_payload;

  /* ssh.kex_algorithms [C/S] */
  strncpy(buf, (const char *)&packet->payload[offset], buf_out_len = len);
  buf[buf_out_len++] = ';';
  offset += len;

  /* ssh.server_host_key_algorithms [None] */
  len = ntohl(*(u_int32_t*)&packet->payload[offset]);
  offset += 4 + len;

  /* ssh.encryption_algorithms_client_to_server [C] */
  len = ntohl(*(u_int32_t*)&packet->payload[offset]);

  if(client_hash) {
    offset += 4;

    if((offset >= packet->payload_packet_len) || (len >= packet->payload_packet_len-offset-1))
      goto invalid_payload;

    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offset], len);
    buf_out_len += len;
    buf[buf_out_len++] = ';';
    offset += len;
  } else
    offset += 4 + len;

  /* ssh.encryption_algorithms_server_to_client [S] */
  len = ntohl(*(u_int32_t*)&packet->payload[offset]);

  if(!client_hash) {
    offset += 4;

    if((offset >= packet->payload_packet_len) || (len >= packet->payload_packet_len-offset-1))
      goto invalid_payload;

    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offset], len);
    buf_out_len += len;
    buf[buf_out_len++] = ';';
    offset += len;
  } else
    offset += 4 + len;

  /* ssh.mac_algorithms_client_to_server [C] */
  len = ntohl(*(u_int32_t*)&packet->payload[offset]);

  if(client_hash) {
    offset += 4;

    if((offset >= packet->payload_packet_len) || (len >= packet->payload_packet_len-offset-1))
      goto invalid_payload;

    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offset], len);
    buf_out_len += len;
    buf[buf_out_len++] = ';';
    offset += len;
  } else
    offset += 4 + len;

  /* ssh.mac_algorithms_server_to_client [S] */
  len = ntohl(*(u_int32_t*)&packet->payload[offset]);

  if(!client_hash) {
    offset += 4;

    if((offset >= packet->payload_packet_len) || (len >= packet->payload_packet_len-offset-1))
      goto invalid_payload;

    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offset], len);
    buf_out_len += len;
    buf[buf_out_len++] = ';';
    offset += len;
  } else
    offset += 4 + len;

  /* ssh.compression_algorithms_client_to_server [C] */
  if(offset+sizeof(u_int32_t) >= packet->payload_packet_len)
    goto invalid_payload;
  len = ntohl(*(u_int32_t*)&packet->payload[offset]);

  if(client_hash) {
    offset += 4;

    if((offset >= packet->payload_packet_len) || (len >= packet->payload_packet_len-offset-1))
      goto invalid_payload;

    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offset], len);
    buf_out_len += len;
    offset += len;
  } else
    offset += 4 + len;

  /* ssh.compression_algorithms_server_to_client [S] */
  len = ntohl(*(u_int32_t*)&packet->payload[offset]);

  if(!client_hash) {
    offset += 4;

    if((offset >= packet->payload_packet_len) || (len >= packet->payload_packet_len-offset-1))
      goto invalid_payload;

    strncpy(&buf[buf_out_len], (const char *)&packet->payload[offset], len);
    buf_out_len += len;
    offset += len;
  } else
    offset += 4 + len;

  /* ssh.languages_client_to_server [None] */

  /* ssh.languages_server_to_client [None] */

#ifdef SSH_DEBUG
  printf("[SSH] %s\n", buf);
#endif

  return(buf_out_len);

invalid_payload:

#ifdef SSH_DEBUG
  printf("[SSH] Invalid packet payload\n");
#endif

  return(0);
}

/* ==================================================================
 * end verbatim target function
 * ================================================================== */

/* Compiler-escape barrier (harness-only): at -O1 the reads/writes whose only
 * observable effect flows through the heap buffers could otherwise be DCE'd,
 * silently erasing the very read that overflows. Force the compiler to assume
 * the pointer may be read by unknown code. */
static void vb_escape(void *p) { __asm__ __volatile__("" : : "g"(p) : "memory"); }

int main(int argc, char **argv) {
  FILE *f;
  long fsz;
  size_t n, plen;
  unsigned char *data;
  u_int8_t *payload;
  char *buf;
  struct ndpi_packet_struct packet;
  volatile u_int16_t sink;

  if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 1; }
  f = fopen(argv[1], "rb");
  if (!f) { perror("fopen"); return 1; }
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
  fsz = ftell(f);
  if (fsz < 0) fsz = 0;
  if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

  /* attacker data on the HEAP so ASAN instruments it */
  data = (unsigned char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
  if (!data) { fclose(f); return 1; }
  n = fsz > 0 ? fread(data, 1, (size_t)fsz, f) : 0;
  fclose(f);

  if (n < 1) { free(data); return 0; }   /* need at least the flag byte */

  /* byte 0 = client/server HASSH flag; the rest is the raw SSH payload */
  u_int8_t client_hash = (u_int8_t)data[0];
  plen = n - 1;
  if (plen > 0xFFFF) plen = 0xFFFF;       /* payload_packet_len is u_int16_t */

  /* tight heap chunk so the unchecked 4-byte read at ssh.c:114 overflows
   * exactly at payload's end (into ASAN's redzone) */
  payload = (u_int8_t *)malloc(plen > 0 ? plen : 1);
  if (!payload) { free(data); return 1; }
  memcpy(payload, data + 1, plen);

  /* faithful to the real caller: hassh_buf = ndpi_calloc(payload_packet_len, 1) */
  buf = (char *)calloc(plen > 0 ? plen : 1, 1);
  if (!buf) { free(payload); free(data); return 1; }

  packet.payload = payload;
  packet.payload_packet_len = (u_int16_t)plen;

  vb_escape(payload);
  vb_escape(buf);
  sink = concat_hash_string(&packet, buf, client_hash);
  vb_escape(buf);
  (void)sink;

  free(buf); free(payload); free(data);
  return 0;
}
