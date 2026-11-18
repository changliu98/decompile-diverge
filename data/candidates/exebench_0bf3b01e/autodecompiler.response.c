void DoAdjust(int *headX, int *headY, int headStartX, int headStartY, int width, int height) {
    *headX -= 1;
    *headY -= 1;

    *headX += headStartX;
    if (*headX < 0) {
        *headX = width + (0 - *headX);
        *headY -= *headX / width;
        *headX = width - (*headX % width);
    }
    *headY += *headX / width;
    *headX %= width;

    *headY += headStartY;

    *headX += 1;
    *headY += 1;
}