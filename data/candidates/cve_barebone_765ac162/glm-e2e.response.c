Forward declaration

void print_trans(struct smb_struct *smb, unsigned char *buf, unsigned char *buf2, unsigned char *buf3, unsigned char *buf_end) {
    unsigned char *buf1 = buf + 1;
    unsigned short param_length, data_length;
    unsigned char *param, *data;
    const char *f1, *f2, *f3, *f4;
    unsigned short setup_count;
    unsigned char *buf_end_adjusted;

    if (request) {
        if (smb->count - 2 > smb->count || buf1 + 0x18 > smb->count - 2) {
            goto error;
        }
        param_length = (buf1[0x13] << 8) | buf1[0x12];
        param = buf2 + (buf1[0x15] << 8 | buf1[0x14]);
        data_length = (buf1[0x17] << 8) | buf1[0x16];
        data = buf2 + (buf1[0x19] << 8 | buf1[0x18]);
        
        f1 = "Transaction request\n";
        f2 = "TransName";
        f3 = "Param";
        f4 = "Data";
    } else {
        if (smb->count - 2 > smb->count || buf1 + 0xe > smb->count - 2) {
            goto error;
        }
        param_length = (buf1[0x7] << 8) | buf1[0x6];
        param = buf2 + (buf1[0x9] << 8 | buf1[0x8]);
        data_length = (buf1[0xd] << 8) | buf1[0xc];
        data = buf2 + (buf1[0xf] << 8 | buf1[0xe]);
        
        f1 = "Transaction response\n";
        f2 = "TransName";
        f3 = "Param";
        f4 = "Data";
    }

    buf_end_adjusted = (buf + 1 + (buf[0] << 1) > buf_end) ? buf_end : (buf + 1 + (buf[0] << 1));
    smb_fdata(smb, buf + 1, f1, buf_end_adjusted, unicodestr);

    if (smb->count - 2 > smb->count || buf2 > smb->count - 2) {
        goto error;
    }

    setup_count = (buf2[1] << 8) | buf2[0];
    smb->fn("TransName=%s\n", buf2 + 2);

    if (setup_count > 0) {
        buf_end_adjusted = (param + param_length > buf_end) ? buf_end : (param + param_length);
        smb_fdata(smb, buf2 + 2, f2, buf_end_adjusted, unicodestr);
    }

    if (strcmp(buf2 + 2, "\\PIPE\\LANMAN") == 0) {
        print_browse(smb, param, param_length, data, data_length);
        return;
    } else if (strcmp(buf2 + 2, "\\PIPE\\WKSSVC") == 0) {
        print_ipc(smb, param, param_length, data, data_length);
        return;
    }

    if (param_length > 0) {
        buf_end_adjusted = (param + param_length > buf_end) ? buf_end : (param + param_length);
        smb_fdata(smb, param, f3, buf_end_adjusted, unicodestr);
    }

    if (data_length > 0) {
        buf_end_adjusted = (data + data_length > buf_end) ? buf_end : (data + data_length);
        smb_fdata(smb, data, f4, buf_end_adjusted, unicodestr);
    }

    return;

error:
    smb->fn("Panic? %s %s\n", tstr, tstr);
    return;
}