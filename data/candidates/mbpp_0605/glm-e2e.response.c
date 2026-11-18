bool func0(int n) {
    bool is_prime = false;
    if (n >= 2) {
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                is_prime = false;
                break;
            }
        }
        // If the loop completes without breaking, it's a prime
        if (i > n / 2) {
            is_prime = true;
        }
    }
    return is_prime;
}