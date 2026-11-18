void func0(struct IMAGE *image, const uint8_t *data, uint32_t length) {
    uint32_t i = 0;
    while (i < length) {
        image->memory[image->ac] = data[i];
        image->ac++;
        if (image->ac == 64) {
            IMAGE_TO_SCREEN(image);
            image->pc += 512;
        }
        image->ac = 0;
        i++;
    }
}