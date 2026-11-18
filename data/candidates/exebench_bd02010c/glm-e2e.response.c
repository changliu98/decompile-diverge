void get_vector_modulo(int *vec1, int *vec2) {
    for (int i = 0; i < 3; i++) {
        vec1[i] %= vec2[i];
        if (vec1[i] < 0) {
            vec1[i] += vec2[i];
        }
    }
}