int rfftp_forward(rfftp_plan* plan, double* output, double scale) {
    if (plan->n == 1) {
        return 0;
    }

    long n = plan->n;
    long current_n = n;
    long factors_count = plan->factors_count;
    double* workspace = malloc(n * 8);
    
    if (workspace == NULL) {
        return -1;
    }

    double* in = output;
    double* out = workspace;

    for (long i = 0; i < factors_count; i++) {
        long factor_index = factors_count - i - 1;
        long factor = plan->factors[factor_index].value;
        long previous_n = n / current_n;
        current_n = current_n / factor;
        double* tw1 = plan->factors[factor_index].tw1;
        double* tw2 = plan->factors[factor_index].tw2;

        if (factor == 4) {
            radf4(previous_n, current_n, in, out, tw1);
        } else if (factor == 2) {
            radf2(previous_n, current_n, in, out, tw1);
        } else if (factor == 3) {
            radf3(previous_n, current_n, in, out, tw1);
        } else if (factor == 5) {
            radf5(previous_n, current_n, in, out, tw1);
        } else {
            radfg(previous_n, factor, current_n, in, out, tw1, tw2);
        }

        // Swap in and out pointers
        double* temp = in;
        in = out;
        out = temp;
    }

    copy_and_norm(output, in, n, scale);
    free(workspace);
    workspace = NULL;
    
    return 0;
}