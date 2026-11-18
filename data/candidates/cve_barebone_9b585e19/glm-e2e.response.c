20

int archive_read_format_rar_read_data(struct archive_read *a, int64_t *buff, int64_t *size, int64_t *offset) {
    struct rar *rar = (struct rar *)((struct archive_read_data *)a->data)->rar;
    int ret;

    if (rar->offset == -1) {
        rar->offset = 0;
    }

    if (rar->bytes_unconsumed > 0) {
        __archive_read_consume(a, rar->bytes_unconsumed);
        rar->bytes_unconsumed = 0;
    }

    *buff = 0;

    if (rar->compression_method == 0) {
        if (rar->bytes_uncopied >= rar->bytes_uncompressed) {
            *size = 0;
            *offset = rar->offset;
            if (*offset < rar->bytes_uncompressed) {
                *offset = rar->bytes_uncompressed;
            }
            return 1;
        }
    } else {
        *size = 0;
        *offset = rar->offset;
        if (*offset < rar->bytes_uncompressed) {
            *offset = rar->bytes_uncompressed;
        }
        return 1;
    }

    switch (rar->compression_method) {
        case 0x30:
            ret = read_data_stored(a, buff, size, offset);
            break;
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
            ret = read_data_compressed(a, buff, size, offset);
            if (ret != 0 && ret != ARCHIVE_EOF) {
                ppmd_decompress(rar); // Called via function pointer in __archive_ppmd7_functions
            }
            break;
        default:
            archive_set_error(a, -1, "Unsupported compression method");
            ret = ARCHIVE_FAILED;
            break;
    }

    return ret;
}