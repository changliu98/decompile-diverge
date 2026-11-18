int func0(const char *arg) {
    int max_val = 0;
    char buffer[0x110]; // 272 bytes
    int buf_idx = 0;
    int i = 0;

    while (arg[i] != '\0') {
        if (arg[i] >= '0' && arg[i] <= '9') {
            buffer[buf_idx++] = arg[i];
        } else {
            if (buf_idx != 0) {
                buffer[buf_idx] = '\0';
                int current_val = atoi(buffer);
                if (current_val > max_val) {
                    max_val = current_val;
                }
                buf_idx = 0;
            }
        }
        i++;
    }

    // Handle the last number if the string ends with digits
    if (buf_idx != 0) {
        buffer[buf_idx] = '\0';
        int current_val = atoi(buffer);
        if (current_val > max_val) {
            max_val = current_val;
        }
    }

    return max_val;
}