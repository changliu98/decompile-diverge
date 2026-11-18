void func0(struct IMAGE *image, const uint8_t *data, size_t length) {
    size_t i = 0;
    while (i < length) {
        image->memory[image->ac] = data[i];
        image->ac++;
        if (image->ac == MEMORY) {
            dump(image, image->memory, MEMORY);
            image->memory = image->memory + MEMORY;
            image->ac = 0;
        }
        i++;
    }
}