void raw_relu_bulk_apply_function(int length, float *array) {
    for (int i = 0; i < length; i++) {
        double val = (double)array[i];
        if (val > 0.0) {
            val = (double)array[i];
        } else {
            val = 0.0;
        }
        array[i] = (float)val;
    }
}