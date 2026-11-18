/*
 * cve_barebone direct-call harness for CVE-2020-15473 (ndpi)
 * Target: ndpi_search_openvpn  (src/lib/protocols/openvpn.c)
 * Bug: CWE-125 heap-buffer-overflow READ inside memcmp(), where
 *      session_remote = ovpn_payload + P_PACKET_ID_ARRAY_LEN_OFFSET(hmac_size)
 *                       + 1 + alen*4  can point past the packet payload buffer,
 *      so the 8-byte memcmp read runs off the heap allocation.
 *
 * Self-contained: minimal libc + the REAL ndpi type/field names and REAL
 * helper functions this function needs, then ndpi_search_openvpn VERBATIM,
 * plus a main() that drives it directly on a heap-allocated payload.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>   /* u_int8_t / u_int16_t / u_int32_t (real ndpi_unix.h vocabulary) */
#include <arpa/inet.h>   /* ntohl / htons */

/* ---- REAL protocol macros (copied verbatim from src/lib/protocols/openvpn.c) ---- */
#define P_CONTROL_HARD_RESET_CLIENT_V1  (0x01 << 3)
#define P_CONTROL_HARD_RESET_CLIENT_V2  (0x07 << 3)
#define P_CONTROL_HARD_RESET_SERVER_V1  (0x02 << 3)
#define P_CONTROL_HARD_RESET_SERVER_V2  (0x08 << 3)
#define P_OPCODE_MASK 0xF8
#define P_SHA1_HMAC_SIZE 20
#define P_HMAC_128 16                            // (RSA-)MD5, (RSA-)MD4, ..others
#define P_HMAC_160 20                            // (RSA-|DSA-)SHA(1), ..others, SHA1 is openvpn default
#define P_HARD_RESET_PACKET_ID_OFFSET(hmac_size) (9 + hmac_size)
#define P_PACKET_ID_ARRAY_LEN_OFFSET(hmac_size)  (P_HARD_RESET_PACKET_ID_OFFSET(hmac_size) + 8)
#define P_HARD_RESET_CLIENT_MAX_COUNT  5

/* ---- REAL protocol-id constants (copied from src/include/ndpi_protocol_ids.h) ---- */
#define NDPI_PROTOCOL_UNKNOWN 0
#define NDPI_PROTOCOL_OPENVPN 159

/* ---- REAL logging/exclude macros: non-debug default expansion is a no-op ----
 *      (src/include/ndpi_define.h.in: NDPI_LOG_INFO/NDPI_LOG_DBG2 -> {}).
 *      NDPI_EXCLUDE_PROTO calls ndpi_exclude_protocol(); it is OFF the crash
 *      path (only on failure) so a faithful minimal no-op stub is used.        */
#define NDPI_LOG_INFO(mod, args...) { }
#define NDPI_LOG_DBG2(mod, args...) { }
#define NDPI_EXCLUDE_PROTO(mod, flow) { }

/* Opaque header pointer types the packet struct references (only compared to
 * NULL / tested for truthiness by ndpi_search_openvpn). */
struct ndpi_tcphdr;
struct ndpi_udphdr;

/* ---- Minimal isolation of the REAL ndpi structs: real field names/types,
 *      only the members ndpi_search_openvpn touches. ---- */
struct ndpi_packet_struct {
  const struct ndpi_tcphdr *tcp;
  const struct ndpi_udphdr *udp;
  const u_int8_t *payload;
  u_int16_t payload_packet_len;
};

struct ndpi_flow_struct {
  u_int8_t num_processed_pkts;
  u_int8_t ovpn_session_id[8];
  u_int8_t ovpn_counter;
  struct ndpi_packet_struct packet;
};

/* ndpi_struct is only handed to no-op log/exclude macros and the detect stub. */
struct ndpi_detection_module_struct { int _unused; };

/* ndpi_set_detected_protocol: called only on the "found openvpn" success
 * return paths (off the crash path) -> faithful minimal no-op. */
static void ndpi_set_detected_protocol(struct ndpi_detection_module_struct *ndpi_struct,
                                       struct ndpi_flow_struct *flow,
                                       u_int16_t upper_detected_protocol,
                                       u_int16_t lower_detected_protocol) {
  (void)ndpi_struct; (void)flow;
  (void)upper_detected_protocol; (void)lower_detected_protocol;
}

/* ---- REAL helper functions on the crash path (copied verbatim from
 *      src/lib/protocols/openvpn.c) — they compute hmac_size, which drives
 *      the offset of the overflowing read. ---- */
static
#ifndef WIN32
inline
#endif
u_int32_t get_packet_id(const u_int8_t * payload, u_int8_t hms) {
  return(ntohl(*(u_int32_t*)(payload + P_HARD_RESET_PACKET_ID_OFFSET(hms))));
}

static
#ifndef WIN32
inline
#endif
int8_t check_pkid_and_detect_hmac_size(const u_int8_t * payload) {
  // try to guess
  if(get_packet_id(payload, P_HMAC_160) == 1)
    return P_HMAC_160;

  if(get_packet_id(payload, P_HMAC_128) == 1)
    return P_HMAC_128;

  return(-1);
}

/* ==== TARGET FUNCTION — VERBATIM from data_cve/cve_5bb2f2c3/target/original_function.c ==== */
void ndpi_search_openvpn(struct ndpi_detection_module_struct* ndpi_struct,
                         struct ndpi_flow_struct* flow) {
  struct ndpi_packet_struct* packet = &flow->packet;
  const u_int8_t * ovpn_payload = packet->payload;
  const u_int8_t * session_remote;
  u_int8_t opcode;
  u_int8_t alen;
  int8_t hmac_size;
  int8_t failed = 0;

  if(packet->payload_packet_len >= 40) {
    // skip openvpn TCP transport packet size
    if(packet->tcp != NULL)
      ovpn_payload += 2;

    opcode = ovpn_payload[0] & P_OPCODE_MASK;

    if(packet->udp) {
#ifdef DEBUG
      printf("[packet_id: %u][opcode: %u][Packet ID: %d][%u <-> %u][len: %u]\n",
	     flow->num_processed_pkts,
	     opcode, check_pkid_and_detect_hmac_size(ovpn_payload),
	     htons(packet->udp->source), htons(packet->udp->dest), packet->payload_packet_len);	   
#endif
      
      if(
	 (flow->num_processed_pkts == 1)
	 && (
	     ((packet->payload_packet_len == 112)
	      && ((opcode == 168) || (opcode == 192))
	      )
	     || ((packet->payload_packet_len == 80)
		 && ((opcode == 184) || (opcode == 88) || (opcode == 160) || (opcode == 168) || (opcode == 200)))
	     )) {
	NDPI_LOG_INFO(ndpi_struct,"found openvpn\n");
	ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_OPENVPN, NDPI_PROTOCOL_UNKNOWN);
	return;
      }
    }
    
    if(flow->ovpn_counter < P_HARD_RESET_CLIENT_MAX_COUNT && (opcode == P_CONTROL_HARD_RESET_CLIENT_V1 ||
				    opcode == P_CONTROL_HARD_RESET_CLIENT_V2)) {
      if(check_pkid_and_detect_hmac_size(ovpn_payload) > 0) {
        memcpy(flow->ovpn_session_id, ovpn_payload+1, 8);

        NDPI_LOG_DBG2(ndpi_struct,
		 "session key: %02x%02x%02x%02x%02x%02x%02x%02x\n",
		 flow->ovpn_session_id[0], flow->ovpn_session_id[1], flow->ovpn_session_id[2], flow->ovpn_session_id[3],
		 flow->ovpn_session_id[4], flow->ovpn_session_id[5], flow->ovpn_session_id[6], flow->ovpn_session_id[7]);
      }
    } else if(flow->ovpn_counter >= 1 && flow->ovpn_counter <= P_HARD_RESET_CLIENT_MAX_COUNT &&
            (opcode == P_CONTROL_HARD_RESET_SERVER_V1 || opcode == P_CONTROL_HARD_RESET_SERVER_V2)) {

      hmac_size = check_pkid_and_detect_hmac_size(ovpn_payload);

      if(hmac_size > 0) {
        alen = ovpn_payload[P_PACKET_ID_ARRAY_LEN_OFFSET(hmac_size)];
        if (alen > 0) {
	  session_remote = ovpn_payload + P_PACKET_ID_ARRAY_LEN_OFFSET(hmac_size) + 1 + alen * 4;

          if(memcmp(flow->ovpn_session_id, session_remote, 8) == 0) {
	    NDPI_LOG_INFO(ndpi_struct,"found openvpn\n");
	    ndpi_set_detected_protocol(ndpi_struct, flow, NDPI_PROTOCOL_OPENVPN, NDPI_PROTOCOL_UNKNOWN);
	    return;
	  } else {
            NDPI_LOG_DBG2(ndpi_struct,
		   "key mismatch: %02x%02x%02x%02x%02x%02x%02x%02x\n",
		   session_remote[0], session_remote[1], session_remote[2], session_remote[3],
		   session_remote[4], session_remote[5], session_remote[6], session_remote[7]);
            failed = 1;
          }
        } else
          failed = 1;
      } else
        failed = 1;
    } else
      failed = 1;

    flow->ovpn_counter++;
    
    if(failed) {
      NDPI_EXCLUDE_PROTO(ndpi_struct, flow);
    }
  }
}
/* ==== END TARGET FUNCTION ==== */

int main(int argc, char **argv) {
  if(argc < 2) return 0;
  FILE *f = fopen(argv[1], "rb");
  if(!f) return 0;
  fseek(f, 0, SEEK_END);
  long sz = ftell(f);
  fseek(f, 0, SEEK_SET);
  if(sz < 0) { fclose(f); return 0; }
  size_t n = (size_t)sz;

  /* HEAP-allocate the payload EXACTLY n bytes so an out-of-bounds read is in
   * the ASAN redzone right after it. */
  u_int8_t *payload = (u_int8_t*)malloc(n ? n : 1);
  if(!payload) { fclose(f); return 0; }
  if(n) {
    if(fread(payload, 1, n, f) != n) { /* short read: still drive with what we got */ }
  }
  fclose(f);

  struct ndpi_detection_module_struct ndpi_struct;
  memset(&ndpi_struct, 0, sizeof(ndpi_struct));

  struct ndpi_flow_struct *flow =
      (struct ndpi_flow_struct*)calloc(1, sizeof(*flow));
  if(!flow) { free(payload); return 0; }

  flow->packet.payload = payload;
  flow->packet.payload_packet_len = (u_int16_t)n;   /* buffer size == declared len */
  flow->packet.tcp = NULL;                          /* UDP-style: no 2-byte TCP prefix */
  flow->packet.udp = NULL;                          /* skip the first-packet udp branch */
  flow->ovpn_counter = 1;                           /* in [1,5] -> server-reset branch reachable */
  flow->num_processed_pkts = 2;

  ndpi_search_openvpn(&ndpi_struct, flow);

  free(flow);
  free(payload);
  return 0;
}
