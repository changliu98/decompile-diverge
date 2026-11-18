int kwajd_read_headers(struct io_state *io, struct kwaj_header *hdr, void *unused) {
    unsigned char buf[16];
    int err = 0;

    // Read 14-byte base header
    if (io->read(io, buf, 14) != 14) {
        return 3;
    }

    // Verify magic "KWAJ" (0x4B4A4157)
    if ((buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0]) != 0x4A41574B) {
        return 7;
    }

    // Verify secondary signature (0xd127f088)
    if ((buf[7] << 24 | buf[6] << 16 | buf[5] << 8 | buf[4]) != 0xd127f088) {
        return 7;
    }

    hdr->method = buf[9] << 8 | buf[8];
    hdr->header_size = buf[11] << 8 | buf[10];
    hdr->flags = buf[13] << 8 | buf[12];
    hdr->data_offset = 0;
    hdr->filename = NULL;
    hdr->data = NULL;
    hdr->data_size = 0;

    // Flag 0x1: 4-byte data offset
    if (hdr->flags & 0x1) {
        if (io->read(io, buf, 4) != 4) {
            return 3;
        }
        hdr->data_offset = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
    }

    // Flag 0x2: 2-byte unknown/skip
    if (hdr->flags & 0x2) {
        if (io->read(io, buf, 2) != 2) {
            return 3;
        }
    }

    // Flag 0x4: 2-byte length followed by 1-byte data skip
    if (hdr->flags & 0x4) {
        if (io->read(io, buf, 2) != 2) {
            return 3;
        }
        int length = buf[1] << 8 | buf[0];
        if (io->seek(io, length, 1) != 0) {
            return 5;
        }
    }

    // Flags 0x8 and 0x10: Filename and extension
    if (hdr->flags & 0x18) {
        int64_t pos = io->tell(io);
        char *fn = io->alloc(io, 13);
        if (!fn) {
            return 6;
        }
        hdr->filename = fn;

        // Flag 0x8: 9-byte filename
        if (hdr->flags & 0x8) {
            if (io->read(io, buf, 9) != 9) {
                return 3;
            }
            int i = 0;
            while (i < 9) {
                fn[i] = buf[i];
                if (buf[i] == 0) break;
                i++;
            }
            int adv = (i < 9) ? i + 1 : 9;
            pos += adv;
            if (io->seek(io, pos, 0) != 0) {
                return 5;
            }
        }

        // Flag 0x10: 4-byte extension
        if (hdr->flags & 0x10) {
            *fn++ = '.';
            if (io->read(io, buf, 4) != 4) {
                return 3;
            }
            int i = 0;
            while (i < 4) {
                fn[i] = buf[i];
                if (buf[i] == 0) break;
                i++;
            }
            int adv = (i < 4) ? i + 1 : 4;
            pos += adv;
            if (io->seek(io, pos, 0) != 0) {
                return 5;
            }
        }
        *fn = 0;
    }

    // Flag 0x20: 2-byte length followed by arbitrary data
    if (hdr->flags & 0x20) {
        if (io->read(io, buf, 2) != 2) {
            return 3;
        }
        int length = buf[1] << 8 | buf[0];
        char *d = io->alloc(io, length + 1);
        hdr->data = d;
        if (!d) {
            return 6;
        }
        if (io->read(io, d, length) != length) {
            return 3;
        }
        d[length] = 0;
        hdr->data_size = length;
    }

    return 0;
}