struct IMAGE *func0(int x, int y) {
    struct IMAGE *image;
    int i;

    if (debug)
        PrintDebug("func0\n");

    image = (struct IMAGE *)calloc(1, sizeof(struct IMAGE));
    if (image == NULL) {
        image = NULL;
        goto func0_exit;
    }

    for (i = 0; i < 39; i++)
        strcpy(image->buffer[i], "                                                                   ");

    image->width = x;
    image->height = y;
    image->color = FALSE;
    image->line = 0;
    image->column = 0;
    image->font.x = 0;
    image->font.y = 0;

    IMAGE_Clear(image);
    IMAGE_SetBackgroundColor(image, 0);
    IMAGE_SetForegroundColor(image, 0);

func0_exit:
    return (image);
}