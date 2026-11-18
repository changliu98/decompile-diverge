void func0(struct node *root) {
    if (root == NULL) {
        return;
    }
    struct node *current = root;
    current->visited = false;
    current->distance = 0;
    current->parent = NULL;
    if (current->neighbors!= NULL) {
        free(current->neighbors);
    }
    current->neighbors = NULL;
    current->color = WHITE;
    current->pred = -1;
    current->time = 0;
}