double func0(int rolls[], int numberOfRolls) {
    int i, sum = 0;
    for (i = 0; i < numberOfRolls; i++) {
        sum += rolls[i];
    }
    return sum / (double)numberOfRolls;
}