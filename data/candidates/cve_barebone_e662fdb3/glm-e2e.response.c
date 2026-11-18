void do_iccprofile_item(struct de_context *c, struct de_iccprofile *icc, uint64_t pos, uint64_t len) {
    uint64_t type;
    uint64_t data_len;

    if (len < 4) {
        return;
    }

    type = dbuf_getu32be(c->f, pos);
    data_len = len - 4;

    de_dbg(c, "ICC profile item type=0x%x len=%u", (unsigned int)type, (unsigned int)data_len);

    if (type == 1) {
        dbuf_close(icc->outf);
        icc->outf = 0;
    }

    if (type == 0) {
        icc->outf = dbuf_create_output_file(c, "icc_profile", 0, 1);
    }

    if (type == 0 || type == 1) {
        dbuf_copy(c->f, pos + 4, data_len, icc->outf);
    }
}