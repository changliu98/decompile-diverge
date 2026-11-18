int stbi__compute_transparency(struct stbi__png *z, unsigned char *tc, int out_n) {
    struct stbi__context *s = z->s;
    int pixel_count = s->img_x * s->img_y;
    unsigned char *p = z->out;

    // Assert that out_n is either 2 or 4
    // (The assembly calls an assert-like function if this condition is not met)
    if (!(out_n == 2 || out_n == 4)) {
        // stbi__assert("...", "...", 0x1332, "...");
    }

    if (out_n == 2) {
        for (int i = 0; i < pixel_count; ++i) {
            // If the grayscale value matches the transparent color, alpha is 0; otherwise, 255
            p[1] = (p[0] == tc[0]) ? 0 : 255;
            p += 2;
        }
    } else { // out_n == 4
        for (int i = 0; i < pixel_count; ++i) {
            // If the RGB values match the transparent color, set alpha to 0
            if (p[0] == tc[0] && p[1] == tc[1] && p[2] == tc[2]) {
                p[3] = 0;
            }
            p += 4;
        }
    }

    return 1;
}