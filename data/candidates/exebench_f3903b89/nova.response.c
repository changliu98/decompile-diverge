static void get_payload_info(const u8 *data, u32 *rh, u32 *rl) {
    u32 tmp;

    tmp = (data[OFFSET_16 / 8] + 1) * 512;
    *rh = tmp + data[OFFSET_17 / 8];
    *rl = data[OFFSET_18 / 8];
}