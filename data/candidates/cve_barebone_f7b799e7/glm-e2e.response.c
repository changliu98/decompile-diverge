void color_cmyk_to_rgb(struct color_t *color) {
    int height = color->data->height;
    int width = color->data->width;
    
    if ((unsigned int)color->count < 4) {
        return;
    }

    int pixels = width * height;
    
    float c_div = 1.0f / (float)((1 << color->data->c_bits) - 1);
    float m_div = 1.0f / (float)((1 << color->data->m_bits) - 1);
    float y_div = 1.0f / (float)((1 << color->data->y_bits) - 1);
    float k_div = 1.0f / (float)((1 << color->data->k_bits) - 1);

    for (int i = 0; i < pixels; i++) {
        float c = (float)color->data->c[i] * c_div;
        float m = (float)color->data->m[i] * m_div;
        float y = (float)color->data->y[i] * y_div;
        float k = (float)color->data->k[i] * k_div;

        c = 1.0f - c;
        m = 1.0f - m;
        y = 1.0f - y;
        k = 1.0f - k;

        color->data->c[i] = (int)(255.0f * c * k);
        color->data->m[i] = (int)(255.0f * m * k);
        color->data->y[i] = (int)(255.0f * y * k);
    }

    free(color->data->k);
    color->data->k = NULL;
    
    color->data->c_bits = 8;
    color->data->m_bits = 8;
    color->data->y_bits = 8;
    
    color->count--;
    color->field_8 = 1;

    for (int i = 3; i < color->count; i++) {
        memcpy((char*)color->data + i * 64, (char*)color->data + (i + 1) * 64, 64);
    }
}