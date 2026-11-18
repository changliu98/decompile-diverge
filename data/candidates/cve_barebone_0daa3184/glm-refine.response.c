enamemem *__cdecl lookup_bytestring(netdissect_options *ndo, const u_char *bs, const unsigned int nlen)
{
  int k, j, i;
  enamemem *tp;

  // 1. Extract up to three 16-bit words from the byte string.
  // The extraction is big-endian (network byte order).
  if (nlen >= 6) {
    i = (bs[0] << 8) | bs[1];
    j = (bs[2] << 8) | bs[3];
    k = (bs[4] << 8) | bs[5];
  } else if (nlen >= 4) {
    i = 0;
    j = (bs[0] << 8) | bs[1];
    k = (bs[2] << 8) | bs[3];
  } else {
    i = 0;
    j = 0;
    k = 0;
  }

  // 2. Calculate the hash table index.
  // The hash table `bytestringtable` is an array of 4096 (0x1000) enamemem structs.
  // The size of each enamemem struct is 32 bytes (0x20).
  // The index is derived from (j XOR i) masked to 12 bits.
  unsigned int hash_idx = ((unsigned __int16)j ^ (unsigned __int16)i) & 0xFFF;
  tp = (enamemem *)((char *)&bytestringtable + (32 * hash_idx));

  // 3. Traverse the linked list to find a matching entry.
  while (tp->e_nxt) {
    if (tp->e_addr0 == i && 
        tp->e_addr1 == j && 
        tp->e_addr2 == k && 
        !memcmp(bs, tp->e_nsap, nlen)) {
      return tp; // Entry found
    }
    tp = tp->e_nxt;
  }

  // 4. If not found, populate the current empty tail node.
  tp->e_addr0 = i;
  tp->e_addr1 = j;
  tp->e_addr2 = k;
  
  tp->e_nsap = (u_char *)calloc(1uLL, nlen + 1);
  if (!tp->e_nsap)
    ndo->ndo_error(ndo, "lookup_bytestring: calloc");
    
  memcpy(tp->e_nsap, bs, nlen);
  
  // 5. Allocate a new empty tail node for the linked list.
  tp->e_nxt = (enamemem *)calloc(1uLL, 0x20uLL); // 0x20 == sizeof(enamemem)
  if (!tp->e_nxt)
    ndo->ndo_error(ndo, "lookup_bytestring: calloc");

  return tp;
}