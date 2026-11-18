int canConstruct(char* ransomNote, char* magazine) {
    int len1 = strlen(ransomNote);
    int len2 = strlen(magazine);

    int i;
    int j;

    char flag;

    for(i = 0; i < len1; i++){
        flag = 0;
        for(j = 0; j < len2; j++){
            if(ransomNote[i] == magazine[j]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            return 0;
        }
    }

    for(i = 0; i < len2; i++){
        flag = 0;
        for(j = 0; j < len1; j++){
            if(magazine[i] == ransomNote[j]){
                flag = 1;
                break;
            }
        }
        if(!flag){
            return 0;
        }
    }

    return 1;
}