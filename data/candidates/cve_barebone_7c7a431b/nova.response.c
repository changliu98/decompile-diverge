void RemoveICCProfileFromResourceBlock(FILE *fp) {
    unsigned long len = get_file_size(fp);
    if (len < sizeof(struct elfhdr))
        return;

    unsigned char *buf = (unsigned char *)malloc(len);
    unsigned char *p = buf;
    while (1) {
        if (p >= buf + len)
            return;
        if (!(p[0] == 0x7f && p[1] == 0x45 && p[2] == 0x4c && p[3] == 0x46)) {
            p++;
            continue;
        }
        unsigned int e_entry, e_phoff, e_phentsize, e_phnum;
        p = read_elf_field(2, p, &e_entry);
        p = read_elf_field(2, p, &e_phoff);
        p = read_elf_field(4, p, &e_phentsize);
        p = read_elf_field(2, p, &e_phnum);
        if (e_entry!= 0x0000)
            continue;
        print_elf_info(buf, len, len - (p - buf), e_phentsize, e_phnum);
        print_ph_info(fp, len - (p - buf), e_phentsize, e_phnum);
        break;
    }
}