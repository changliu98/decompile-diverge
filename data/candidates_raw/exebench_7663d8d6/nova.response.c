void func0(struct SOM som, double value, int flag) {
    if (flag & 1)
        som.learning_rate += value;
    else
        som.learning_rate -= value;

    if (flag & 2)
        som.sigma += value;
    else
        som.sigma -= value;

    if (flag & 4)
        som.n_iterations += value;
    else
        som.n_iterations -= value;
}