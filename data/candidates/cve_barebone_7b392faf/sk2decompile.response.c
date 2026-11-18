static int xid_map_enter(struct dns_packet *P, const struct dns_query *Q,
                         const unsigned char *answer) {
  const struct dns_aaaa_record *AAAA = NULL;
  const struct dns_a_record *A = NULL;
  struct xid_map_entry *entry;
  if (P->end - 4 < answer || P->end - 4 < Q->qname) return 0;
  switch (answer[0] >> 4) {
    case 4:
      AAAA = (const struct dns_aaaa_record *)answer;
      break;
    case 6:
      A = (const struct dns_a_record *)answer;
      break;
    default:
      return 1;
  }
  entry = &xid_map[xid_map_next];
  xid_map_next++;
  if (xid_map_next >= 64) xid_map_next = 0;
  entry->xid = Q->id;
  if (AAAA) {
    entry->family = 4;
    entry->addr = AAAA->address;
    entry->addr_len = AAAA->length;
  } else if (A) {
    entry->family = 6;
    entry->addr = A->address_v6;
    entry->addr_len = A->length_v6;
  }
  entry->qname_hash = EXTRACT_32BITS((const char *)(Q->qname + 4));
  entry->qname_hash_qtype = EXTRACT_32BITS((const char *)(Q->qname));
  return 1;
}