void to_bytes(int val, char *bytes) {
    bytes[0] = (char)(val);
    bytes[1] = (char)(val >> 8);
    bytes[2] = (char)(val >> 16);
    bytes[3] = (char)(val >> 24);
}