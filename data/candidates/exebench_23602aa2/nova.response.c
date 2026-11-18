void lib3ds_quat_scalar(float arr[], float mult) {
    int i = 0;
    while (i < 5) {
        arr[i] *= mult;
        i++;
    }
}