int updateBounds(int score, int *lowerBound, int *upperBound, int maximizingPlayer) {
    int returnValue;

    if (maximizingPlayer && score > *lowerBound) {

        *lowerBound = score;
    } else if (!maximizingPlayer && score < *upperBound) {

        *upperBound = score;
    }

    if (*upperBound <= *lowerBound) {
        returnValue = 1;
    } else {
        returnValue = 0;
    }

    return returnValue;
}