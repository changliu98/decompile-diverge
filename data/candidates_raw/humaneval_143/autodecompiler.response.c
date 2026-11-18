int main() {
    char line[100 + 1];
    char result[100 + 1];

    scanf__bench("%[^\n]s", line);

    filterPrimes(line, result);

    printf__bench("%s\n", result);

    return 0;
}