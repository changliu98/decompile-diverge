int cpu_map__id_to_socket(int id) {
    return id >> 16;
}