/*
 * cve_b024754e direct-call crash harness for nDPI's ndpi_search_oracle()
 * (CVE-2020-15476 / CWE-125 heap-buffer-overflow READ in the Oracle-DB
 *  protocol dissector, src/lib/protocols/oracle.c).
 *
 * Root cause (visible directly in target/original_function.c, UNCHANGED):
 *   when the TCP src/dst port is 1521 the dissector reads
 *       packet->payload[0], packet->payload[1], packet->payload[2]
 *   WITHOUT first checking packet->payload_packet_len >= 3.  When the
 *   captured payload is shorter than the accessed index the read walks
 *   past the end of the packet payload buffer -> heap-buffer-overflow
 *   READ (baseline dedup_token
 *   "ndpi_search_oracle--check_ndpi_tcp_flow_func--ndpi_check_flow_func";
 *   here ndpi_search_oracle is called directly from main() so the two
 *   upstream frames are replaced by main, but the faulting READ is the
 *   same payload[] access inside ndpi_search_oracle).  The fix commit
 *   b69177be adds the missing payload_packet_len bounds check.
 *
 * This file assembles:
 *   1. Minimal-but-faithful standalone re-declarations of the REAL nDPI
 *      types the function needs, with their real names/fields copied from
 *      source_code/src/include/ndpi_typedefs.h:
 *        - struct ndpi_tcphdr        (fields source, dest -- lines 303-319)
 *        - struct ndpi_packet_struct (fields tcp, payload,
 *                                     payload_packet_len -- lines 779-831)
 *        - struct ndpi_flow_struct   (member "struct ndpi_packet_struct
 *                                     packet;" -- line 1350)
 *        - struct ndpi_detection_module_struct is opaque here: the target
 *          only ever passes it as a pointer (to the log macros and to
 *          ndpi_int_oracle_add_connection), never dereferences it.
 *      The u_int8_t/u_int16_t scalar typedefs are the real BSD names the
 *      project uses, supplied by <sys/types.h> exactly as nDPI gets them.
 *   2. Faithful no-op stubs for the incidental callees/macros the target
 *      references but that are NOT on the CWE-125 read path:
 *        - NDPI_LOG_DBG / NDPI_LOG_DBG2 / NDPI_LOG_INFO / NDPI_EXCLUDE_PROTO
 *          are debug-logging / bookkeeping macros (compiled out in release
 *          nDPI builds) -> no-ops.
 *        - ndpi_int_oracle_add_connection() only records the detected
 *          protocol (real body just calls ndpi_set_detected_protocol);
 *          it runs AFTER the faulting payload read and has no bearing on
 *          the overflow -> minimal faithful stub that records the detection
 *          in an observable global (a real side effect, mirroring the real
 *          body, so -O1 does not delete the gating payload reads).
 *   3. VERBATIM real nDPI source: target/original_function.c byte-for-byte
 *      (the target function itself, UNCHANGED -- no logic/name/signature
 *      edits).
 *   4. main(): reads argv[1] into a HEAP buffer (so ASAN instruments it),
 *      uses the first byte to select which TCP port is 1521 (dport / sport
 *      / neither), copies the REST of the file into a SEPARATE heap buffer
 *      of EXACTLY that length and points packet->payload at it with
 *      payload_packet_len == that length (mirrors the real capture model
 *      where the payload buffer's length IS payload_packet_len), then
 *      calls ndpi_search_oracle() directly, once.  A short payload +
 *      port 1521 drives the unchecked payload[] read past the buffer end.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>   /* u_int8_t, u_int16_t, u_int32_t (the real nDPI scalar names) */
#include <arpa/inet.h>   /* ntohs, htons */

/* ---- REAL nDPI types (names/fields from src/include/ndpi_typedefs.h) ---- */

/* opaque: ndpi_search_oracle only ever holds this as a pointer */
struct ndpi_detection_module_struct;

struct ndpi_tcphdr {
  u_int16_t source;
  u_int16_t dest;
};

struct ndpi_packet_struct {
  const struct ndpi_tcphdr *tcp;
  const u_int8_t *payload;
  u_int16_t payload_packet_len;
};

struct ndpi_flow_struct {
  struct ndpi_packet_struct packet;
};

/* ---- faithful no-op stubs for incidental callees/macros ---- */
#define NDPI_LOG_DBG(mod, ...)         do { (void)(mod); } while (0)
#define NDPI_LOG_DBG2(mod, ...)        do { (void)(mod); } while (0)
#define NDPI_LOG_INFO(mod, ...)        do { (void)(mod); } while (0)
#define NDPI_EXCLUDE_PROTO(mod, flow)  do { (void)(mod); (void)(flow); } while (0)

/* incidental: real body only marks the protocol detected
 * (ndpi_set_detected_protocol); it runs AFTER the faulting payload read and
 * has no bearing on the CWE-125 overflow.  Faithful minimal stub: record the
 * detection in an observable (volatile) global -- exactly as the real body
 * records the detected protocol on the flow.  The observable write is also
 * load-bearing: without a side effect the compiler proves both "found oracle"
 * branches dead at -O1 and eliminates the gating payload[] reads (the bug),
 * so the stub must, like the real code, actually DO something. */
static volatile unsigned long g_oracle_detected;
static void ndpi_int_oracle_add_connection(struct ndpi_detection_module_struct *ndpi_struct,
                                           struct ndpi_flow_struct *flow) {
  (void)ndpi_struct;
  (void)flow;
  g_oracle_detected++;
}

/* ==== TARGET FUNCTION: verbatim from target/original_function.c ==== */
void ndpi_search_oracle(struct ndpi_detection_module_struct *ndpi_struct, struct ndpi_flow_struct *flow)
{
  struct ndpi_packet_struct *packet = &flow->packet;
  u_int16_t dport = 0, sport = 0;

  NDPI_LOG_DBG(ndpi_struct, "search ORACLE\n");

  if(packet->tcp != NULL) {
    sport = ntohs(packet->tcp->source), dport = ntohs(packet->tcp->dest);
    NDPI_LOG_DBG2(ndpi_struct, "calculating ORACLE over tcp\n");
    /* Oracle Database 9g,10g,11g */
    if ((dport == 1521 || sport == 1521)
	&&  (((packet->payload[0] == 0x07) && (packet->payload[1] == 0xff) && (packet->payload[2] == 0x00))
	     || ((packet->payload_packet_len >= 232) && ((packet->payload[0] == 0x00) || (packet->payload[0] == 0x01)) 
	     && (packet->payload[1] != 0x00)
	     && (packet->payload[2] == 0x00)
		 && (packet->payload[3] == 0x00)))) {
      NDPI_LOG_INFO(ndpi_struct, "found oracle\n");
      ndpi_int_oracle_add_connection(ndpi_struct, flow);
    } else if (packet->payload_packet_len == 213 && packet->payload[0] == 0x00 &&
               packet->payload[1] == 0xd5 && packet->payload[2] == 0x00 &&
               packet->payload[3] == 0x00 ) {
      NDPI_LOG_INFO(ndpi_struct, "found oracle\n");
      ndpi_int_oracle_add_connection(ndpi_struct, flow);
    }
  } else {
    NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
  }
}
/* ==== END verbatim target ==== */

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <input>\n", argv[0]);
    return 2;
  }
  FILE *f = fopen(argv[1], "rb");
  if (!f) { perror("fopen"); return 2; }
  fseek(f, 0, SEEK_END);
  long sz = ftell(f);
  fseek(f, 0, SEEK_SET);
  if (sz < 0) { fclose(f); return 2; }

  u_int8_t *data = (u_int8_t *)malloc((size_t)sz ? (size_t)sz : 1);
  size_t n = fread(data, 1, (size_t)sz, f);
  fclose(f);
  if (n < 1) { free(data); return 0; }   /* need at least the mode byte */

  u_int8_t mode = data[0];
  size_t payload_len = n - 1;

  /* payload = a SEPARATE heap buffer of EXACTLY payload_len bytes, so any
   * read at/past index payload_len is an ASAN-visible heap-buffer-overflow.
   * This mirrors the real capture model: the payload buffer's length IS
   * packet->payload_packet_len.  (The differential corpus drives the overflow
   * with 1- and 2-byte payloads: payload[0]=0x07 -> payload[1] over-read, or
   * payload[0..1]=0x07,0xff -> payload[2] over-read, both past a real heap
   * allocation.) */
  u_int8_t *payload = (u_int8_t *)malloc(payload_len);
  if (payload_len) memcpy(payload, data + 1, payload_len);

  struct ndpi_tcphdr *tcp = (struct ndpi_tcphdr *)malloc(sizeof(*tcp));
  switch (mode & 3) {
    case 1:  /* dport == 1521 */
      tcp->dest = htons(1521); tcp->source = htons(40000);
      break;
    case 2:  /* sport == 1521 */
      tcp->source = htons(1521); tcp->dest = htons(80);
      break;
    default: /* neither port 1521 -> payload never read */
      tcp->source = htons(40000); tcp->dest = htons(80);
      break;
  }

  struct ndpi_flow_struct *flow = (struct ndpi_flow_struct *)malloc(sizeof(*flow));
  memset(flow, 0, sizeof(*flow));
  flow->packet.tcp = tcp;
  flow->packet.payload = payload;
  flow->packet.payload_packet_len = (u_int16_t)(payload_len > 0xffff ? 0xffff : payload_len);

  ndpi_search_oracle((struct ndpi_detection_module_struct *)NULL, flow);

  free(flow);
  free(tcp);
  free(payload);
  free(data);
  return 0;
}
