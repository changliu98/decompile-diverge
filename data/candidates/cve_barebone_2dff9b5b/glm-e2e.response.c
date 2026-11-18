int decode_rt_routing_info(const void *arg1, const unsigned char *arg2, char *arg3, int arg4) {
    int var_4 = -2;
    unsigned char var_2c[8];
    char *var_38;
    const void *var_40 = (const void *)(long)arg4;
    char *var_48 = arg3;
    const void *var_50 = arg1;
    unsigned int var_30;
    unsigned long len;

    len = *(unsigned long *)((char *)arg1 + 8);
    if (len - 1 > len || (unsigned long)arg2 > len - 1) {
        goto end;
    }

    var_30 = *arg2;
    if (var_30 == 0) {
        snprintf(arg3, arg4, "");
        var_4 = 1;
        goto end;
    }

    if (var_30 < 32) {
        var_4 = -1;
        goto end;
    }

    var_30 -= 32;
    if (var_30 >= 64) {
        var_4 = -1;
        goto end;
    }

    memset(var_2c, 0, 8);
    unsigned int nbytes = (var_30 + 7) >> 3;
    if (nbytes != 0) {
        if (len - nbytes > len || (unsigned long)(arg2 + 1) > len - nbytes) {
            goto end;
        }
        memcpy(var_2c, arg2 + 1, nbytes);
        if (var_30 & 7) {
            unsigned int shift = var_30 & 7;
            unsigned char mask = (signed short)0xff00 >> shift;
            var_2c[nbytes - 1] &= mask;
        }
    }

    var_38 = as_printf(arg1, "astostr", 20);
    char *rd_str = bgp_vpn_rd_print(arg1, var_2c);
    snprintf(arg3, arg4, "%s %s", var_38, rd_str);
    var_4 = nbytes + 5;

end:
    return var_4;
}