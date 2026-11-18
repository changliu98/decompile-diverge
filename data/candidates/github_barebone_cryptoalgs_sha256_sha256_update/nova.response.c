void sha256_update(struct IMAGE *image, const uint8_t *data, const size_t data_length) {
    unsigned int i = 0;
    while (i < data_length) {
        image->memory[image->ac] = data[i];
        image->ac++;
        if (image->ac == 64) {
            IMAGE_exec(image);
            image->ap = image->dp + 512;
            image->ac = 0;
        }
        i++;
    }
}