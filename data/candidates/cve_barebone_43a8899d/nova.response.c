struct nodo *get_object_item(struct nodo *lista, char *nome, int ordem) {
    struct nodo *p;
    p = lista;
    if (lista == NULL || nome == NULL) {
        p = NULL;
    } else {
        while (p!= NULL) {
            if (ordem) {
                if (strcmp(nome, p->nome)!= 0) {
                    p = p->prox;
                } else {
                    break;
                }
            } else {
                if (strcmp(nome, p->nome)!= 0) {
                    p = p->ant;
                } else {
                    break;
                }
            }
        }
    }
    return p;
}