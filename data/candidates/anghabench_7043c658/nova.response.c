short calc_speed(short *arr, int size, short max) {
    short calc_speed = 0;
    int i = 0;
    while (i < size) {
        if (arr[i] > calc_speed) {
            calc_speed = arr[i];
        } else {
            i++;
        }
    }
    if (calc_speed == 0) {
        calc_speed = max;
    }
    return calc_speed;
}