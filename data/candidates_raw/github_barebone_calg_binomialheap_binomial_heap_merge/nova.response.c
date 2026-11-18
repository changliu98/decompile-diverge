int func0(struct btreeNode *myNode, struct btreeNode *newNode) {
    struct btreeNode *tmp;
    int i, j, flag;
    do {
        flag = 0;
        for (i = 0; i <= myNode->count; i++) {
            if (i == myNode->count ||
                (myNode->link[i]!= NULL && myNode->link[i]->count >= t)) {
                for (j = 0; j < newNode->count; j++) {
                    if (i == myNode->count ||
                        (myNode->link[i]->item[j]!= newNode->item[j])) {
                        tmp = (struct btreeNode *)malloc(
                            sizeof(struct btreeNode));
                        if (tmp == NULL) {
                            free(tmp);
                            tmp = NULL;
                            flag = 1;
                            break;
                        }
                        tmp->item[j] = newNode->item[j];
                        tmp->count = newNode->count;
                        break;
                    }
                }
                if (flag == 1)
                    break;
                tmp->link[j] = myNode->link[i];
                myNode->link[i] = tmp;
                flag = 1;
            }
        }
        if (flag == 1)
            break;
        free(myNode->link);
        myNode->link = tmp;
        myNode->count = newNode->count;
    } while (flag == 1);
    return 1;
}