bool func0(long long n) {
    bool is_prime;
    if (n < 2) {
        is_prime = false;
    } else {
        for (long long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                is_prime = false;
                break;
            }
        }
        is_prime = true; // Reached if the loop completes without breaking
    }
    return is_prime;
}