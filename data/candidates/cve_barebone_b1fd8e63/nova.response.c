void gitn_box_del(struct sNode **top_ref) {
    unsigned short int i;
    struct sNode *temp = *top_ref;

    
    if (temp == NULL)
        return;

    
    for (i = 0; i < temp->count; i++) {
        if (temp->arr[i]!= NULL)
            free(temp->arr[i]);
    }

    
    if (temp->next!= NULL)
        gitn_box_del(&temp->next);

    
    free(temp);
}