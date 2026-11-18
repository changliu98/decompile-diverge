uint32_t sc_crc32(uint32_t crc, const void *buf, size_t len)
{
# 187 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/cryptotronix/openvpn-nl/refs/heads/master/src/openvpn/openvpn-2.4.x/src/openvpn/tun.c"
    return crc32_sw_le(crc, buf, len);

}