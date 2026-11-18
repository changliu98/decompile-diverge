static void OPLL_Reset(struct context *c, int version) {
    memset(c, 0, sizeof(*c));
    c->version = version;
    if (version == 1) {
        c->cipher_name[321] ='';
        c->cipher_name[370] = 0x80;
    }
    unsigned int i = version;
    if (i <= 6)
        c->cipher_list = &cipher_list_v1[i];
    else if (i <= 18)
        c->cipher_list = &cipher_list_v2[i - 6];
    else
        c->cipher_list = &cipher_list_v3[i - 19];

    for (i = 0; i < 18; i++) {
        c->cipher_list_v2[i].cipher_name[3] = 0x03;
        c->cipher_list_v2[i].cipher_name[63] = 0x7f;
        c->cipher_list_v2[i].cipher_name[100] = 0x7f;
    }
    c->cipher_list_v2[18].cipher_name[3] = 0x06;
}