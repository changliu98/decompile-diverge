int __cdecl gnrc_rpl_srh_process(ipv6_hdr_t *ipv6, gnrc_rpl_srh_t *rh, void **err_ptr)
{
    // addr_vec points to the addresses embedded right after the routing header
    uint8_t *addr_vec = (uint8_t *)(rh + 1);
    
    // Decrement Segments Left for the current hop
    uint8_t new_seg_left = rh->seg_left - 1;

    // Assert that we actually had segments left to process
    if (!rh->seg_left)
    {
        __assert_fail(
            "rh->seg_left > 0",
            "/work/harness.c",
            0xA5u,
            "int gnrc_rpl_srh_process(ipv6_hdr_t *, gnrc_rpl_srh_t *, void **)");
    }

    // Extract padding and compression fields
    uint8_t pad = (rh->pad_resv & 0xF0) >> 4;
    uint8_t compr_elided = rh->compr & 0xF;
    uint8_t compri_addr_len = 16 - ((rh->compr & 0xF0) >> 4);

    // Calculate the number of addresses in the routing header
    uint8_t num_addr = (8 * rh->len - pad - (16 - compr_elided)) / compri_addr_len + 1;

    // Check if seg_left is within the valid range of addresses
    if (rh->seg_left > num_addr)
    {
        *err_ptr = &rh->seg_left;
        return 0;
    }

    // Determine the current position in the address vector (1-indexed)
    uint8_t current_pos = num_addr - new_seg_left;

    // Determine how many prefix bytes are elided for the current address
    uint8_t elided_bytes;
    if (rh->seg_left == 1)
    {
        elided_bytes = compr_elided;
    }
    else
    {
        elided_bytes = (rh->compr & 0xF0) >> 4;
    }

    // Construct the full next-hop address (`addr`) by combining the current 
    // destination prefix with the suffix stored in the routing header
    ipv6_addr_t addr;
    memcpy(&addr, &ipv6->dst, elided_bytes);
    memcpy(&addr.u8[elided_bytes], 
           addr_vec + compri_addr_len * (current_pos - 1), 
           16 - elided_bytes);

    // Multicast address validation checks
    if (ipv6_addr_is_multicast(&ipv6->dst) || ipv6_addr_is_multicast(&addr))
    {
        return 0;
    }

    // Check if the destination address contains multiple instances of our own address
    void *err_val = contains_multiple_of_my_addr(&ipv6->dst, rh, num_addr, compri_addr_len);
    *err_ptr = err_val;
    if (err_val)
    {
        return 0;
    }

    // Update the routing header and swap the addresses
    rh->seg_left = new_seg_left;
    
    // Save the current destination suffix into the routing header
    memcpy(addr_vec + compri_addr_len * (current_pos - 1), 
           &ipv6->dst.u8[elided_bytes], 
           16 - elided_bytes);
           
    // Set the new destination
    ipv6->dst = addr;

    return 2;
}