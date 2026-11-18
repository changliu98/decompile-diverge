void unpack_dxt(struct SOM som, uint8_t input[INPUT_DIM],
                       uint8_t output[OUTPUT_DIM]) {
    uint8_t winner;
    uint8_t i, j;

    while (1) {
        winner = get_winner(som, input);
        for (i = 0; i < OUTPUT_DIM; i++) {
            for (j = 0; j < INPUT_DIM; j++) {
                if (i < INPUT_DIM) {
                    output[i] =
                        (uint8_t)((int)som.neurons[winner].weight[i] / 2 +
                                  (int)input[i] / 2);
                } else {
                    output[i] =
                        (uint8_t)((int)som.neurons[winner].weight[i] / 2 +
                                  (int)input[j] / 2);
                }
            }
        }

        if (input[INPUT_DIM - 1] > input[INPUT_DIM - 2])
            break;
    }
}