void __cdecl ndpi_search_oracle(ndpi_detection_module_struct *ndpi_struct, ndpi_flow_struct *flow)
{
  const u_int8_t *p;
  u_int16_t sport, dport;
  u_int16_t payload_len;

  // 1. Ensure the packet is using TCP
  if (!flow->packet.tcp)
    return;

  // 2. Extract port information
  sport = ntohs(flow->packet.tcp->source);
  dport = ntohs(flow->packet.tcp->dest);
  
  // 3. Check if either source or destination port is the default Oracle DB port (1521)
  if (sport != 1521 && dport != 1521)
    return;

  // 4. Setup payload variables for easier readability
  p = (const u_int8_t *)flow->packet.payload;
  payload_len = flow->packet.payload_packet_len;

  // 5. Oracle DB protocol signature matching
  //
  // The original decompiled logic relies on C's operator precedence where `&&` binds 
  // tighter than `||`. The conditions are grouped exactly as the compiler evaluated them:
  //
  // Group A: (Port check) AND (Condition 1 OR Condition 2)
  // Group B: Condition 3
  // Final Match = Group A OR Group B
  //
  if (
    // --- Group A: Standard Oracle Traffic ---
    (
      // Condition 1: Typical Oracle TNS packet prefix (07 FF 00)
      (p[0] == 7 && p[1] == 0xFF && p[2] == 0) ||

      // Condition 2: Large packet (>= 232 bytes) with standard header flags
      (payload_len >= 0xE8 && (p[0] == 0 || p[0] == 1) && p[1] != 0 && p[2] == 0 && p[3] == 0)
    )
    ||
    // --- Group B: Specific 213-byte packet variation ---
    (
      payload_len == 213 && p[0] == 0 && p[1] == 213 && p[2] == 0 && p[3] == 0
    )
  )
  {
    ndpi_int_oracle_add_connection(ndpi_struct, flow);
  }
}