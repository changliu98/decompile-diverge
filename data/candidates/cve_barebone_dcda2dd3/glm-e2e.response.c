int read_fru_area(struct ipmi_intf *intf, struct fru_info *fru, uint8_t id, uint32_t offset, uint32_t length, uint8_t *data) {
    struct ipmi_rq req;
    uint32_t finish;
    uint32_t off;
    uint32_t size;
    uint16_t max_rsp_size;
    struct ipmi_rs *rsp;

    if (offset > fru->size) {
        lprintf(3, "Fru area offset is larger than fru size");
        return -1;
    }

    finish = offset + length;
    if (finish > fru->size) {
        finish = fru->size;
        lprintf(5, "Read length is too large, clipping to %d", finish - offset);
    }

    memset(&req, 0, sizeof(req));
    req.cmd = 0x11;
    req.msg_data = req.data;
    req.msg_data_len = 4;

    if (fru->max_read_size == 0) {
        max_rsp_size = ipmi_intf_get_max_response_data_size(intf) - 1;
        if (max_rsp_size <= 1) {
            lprintf(3, "Maximum response size is too small");
            return -1;
        }
        if (max_rsp_size - 1 > 0xff) {
            fru->max_read_size = 0xff;
        } else {
            fru->max_read_size = max_rsp_size - 1;
        }
        if (fru->access & 1) {
            fru->max_read_size &= ~1;
        }
    }

    do {
        if (fru->access & 1) {
            off = offset / 2;
        } else {
            off = offset;
        }

        req.data[0] = id;
        req.data[1] = off & 0xff;
        req.data[2] = (off >> 8) & 0xff;

        size = finish - offset;
        if (size > fru->max_read_size) {
            req.data[3] = fru->max_read_size;
        } else {
            req.data[3] = size;
        }

        rsp = intf->sendrecv(intf, &req);
        if (rsp == NULL) {
            lprintf(5, "ipmi_rs_sendrecv failed");
            break;
        }

        if (rsp->ccode != 0) {
            if (fru_cc_rq2big(rsp->ccode)) {
                if (fru->max_read_size > 8) {
                    if (fru->max_read_size > 0x20) {
                        fru->max_read_size -= 8;
                    } else {
                        fru->max_read_size--;
                    }
                    lprintf(6, "Adjusting read size to %d", fru->max_read_size);
                    continue;
                }
            }
            lprintf(5, "Read FRU Area failed: %s", val2str(rsp->ccode, completion_code_vals));
            break;
        }

        if (fru->access & 1) {
            size = rsp->data_len * 2;
        } else {
            size = rsp->data_len;
        }

        memcpy(data, rsp->data, size);
        offset += size;
        data += size;

        if (size == 0 || offset >= finish) {
            return 0;
        }
    } while (offset < finish);

    if (offset < finish) {
        return -1;
    }

    return 0;
}