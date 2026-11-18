int svc_parse_slice(void *bs, struct VUI *vui, struct NALU *nalu) {
    int temp;
    int dependency_id;

    // First two calls to gf_bs_read_ue_log_idx3 seem to read and discard values
    gf_bs_read_ue_log_idx3(bs, "str1", -1, -1, -1);
    temp = gf_bs_read_ue_log_idx3(bs, "str2", -1, -1, -1);
    nalu->field_10 = temp;

    if (nalu->field_10 > 9) {
        return -1;
    }

    dependency_id = gf_bs_read_ue_log_idx3(bs, "str3", -1, -1, -1);
    if (dependency_id > 255) {
        return -1;
    }

    nalu->field_48 = &vui->sps_array[dependency_id];
    nalu->field_48->field_0 = dependency_id;

    if (nalu->field_48->field_14 == 0) {
        return -2;
    }

    nalu->field_40 = (char *)vui + (nalu->field_48->field_4 + 16) * 0x2b8;

    if (*(int *)((char *)nalu->field_40 + 0xc) == 0) {
        return -2;
    }

    nalu->field_4 = gf_bs_read_int(bs, *(int *)((char *)nalu->field_40 + 0xc));
    nalu->field_2 = 0;

    if (*(int *)((char *)nalu->field_40 + 0x28) == 0) {
        nalu->field_2 = gf_bs_read_int(bs, 1);
        if (nalu->field_2 != 0) {
            nalu->field_3 = gf_bs_read_int(bs, 1);
        }
    }

    if (nalu->field_1 == 5 || nalu->field_50 != 0) {
        nalu->field_8 = gf_bs_read_ue_log_idx3(bs, "str4", -1, -1, -1);
    }

    if (*(int *)((char *)nalu->field_40 + 0x10) == 0) {
        nalu->field_c = gf_bs_read_int(bs, *(int *)((char *)nalu->field_40 + 0x18));
        if (nalu->field_48->field_c != 0 && nalu->field_2 == 0) {
            nalu->field_14 = gf_bs_read_se_log_idx2(bs, "str5", -1, -1);
        }
    } else if (*(int *)((char *)nalu->field_40 + 0x10) == 1) {
        if (*(int *)((char *)nalu->field_40 + 0x1c) == 0) {
            nalu->field_18 = gf_bs_read_se_log_idx2(bs, "str6", -1, -1);
            if (nalu->field_48->field_c == 1 && nalu->field_2 == 0) {
                nalu->field_1c = gf_bs_read_se_log_idx2(bs, "str7", -1, -1);
            }
        }
    }

    if (nalu->field_48->field_10 != 0) {
        nalu->field_20 = gf_bs_read_ue_log_idx3(bs, "str8", -1, -1, -1);
    }

    return 0;
}