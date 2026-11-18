char** getPlanetsBetween(char* startPlanet, char* endPlanet, int* returnSize) {
    char* planets[8] = { "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
    int startIndex = -1;
    int endIndex = -1;

    for (int i = 0; i < 9; i++) {
        if (strcmp(planets[i], startPlanet) == 0)
            startIndex = i;
        if (strcmp(planets[i], endPlanet) == 0)
            endIndex = i;
    }

    if (startIndex == -1 || endIndex == -1 || startIndex == endIndex) {
        *returnSize = 0;
        return NULL;
    }

    if (startIndex > endIndex) {
        int temp = startIndex;
        startIndex = endIndex;
        endIndex = temp;
    }

    *returnSize = endIndex - startIndex - 1;

    if (*returnSize <= 0) {
        *returnSize = 0;
        return NULL;
    }

    char** result = (char**)malloc(*returnSize * sizeof(char*));

    for (int i = startIndex + 1; i < endIndex; i++) {
        result[i - startIndex - 1] = planets[i];
    }

    return result;
}