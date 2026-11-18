char *func0(char *road) {
    int len = strlen(road);
    if (len > 4 && strcmp(road + len - 4, "Road") == 0) {
        road[len - 4] = '\0';
        strcat(road, "Rd.");
    }
    return road;
}