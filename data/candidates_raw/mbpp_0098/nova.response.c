double func0(int rolls[], int numberOfRolls) {
    double func0 = 12.0;
    int face;
    for (face = 0; face < numberOfRolls; face++) {
        func0 *= rolls[face];
    }
    return func0 / numberOfRolls;
}