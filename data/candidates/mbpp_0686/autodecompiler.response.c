char * func0(int * list, int size) {
    struct occurance_t {
        int number;
        int count;
    } stats[100];

    int count = 0;
    int i = 0;

    while(1) {
        if(i >= size) break;

        bool found = false;
        int j = 0;
        for(; j < count; j++) {
            if(stats[j].number == list[i]) {
                stats[j].count++;
                found = true;
                break;
            }
        }

        if(!found) {
            stats[count].number = list[i];
            stats[count].count = 1;
            count++;
        }

        i++;
    }

    char * result = malloc(sizeof(char) * 1000);
    strcpy(result, "\0");
    strcat(result, "{");

    char buffer[100];
    for(int i = 0; i < count; i++) {
        sprintf(buffer, "%d: %d", stats[i].number, stats[i].count);
        strcat(result, buffer);
        if(i < count-1) strcat(result, ", ");
    }

    strcat(result, "}");
    return result;
}