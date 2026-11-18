int file_packet_DATA_PACKET(void *arg1, int arg2) {
    return *(int *)((char *)arg1 - 4);
}