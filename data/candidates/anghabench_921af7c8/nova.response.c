int handle_to_chunks(unsigned long long adr) {
    return (adr >> (64 - 11943)) & 0xffff;
}