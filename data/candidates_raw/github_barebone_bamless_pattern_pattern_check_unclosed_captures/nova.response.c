void func0(struct config *config) {
    int i = 1;
    while (i < config->population_size) {
        if (config->individuals[i].fitness == -1) {
            int j = 0;
            char *gene = config->individuals[0].gene;
            char *current_gene = gene;
            char *next_gene = gene;
            while (1) {
                next_gene = strchr(gene, '%');
                if (next_gene < gene + strlen(gene)) {
                    if (*gene == '%') {
                        gene = next_gene + 2;
                    } else if (*gene == '(') {
                        j++;
                        if (j == i) {
                            break;
                        }
                        gene++;
                    } else {
                        gene++;
                    }
                } else {
                    break;
                }
            }
            strncpy(config->individuals[i].gene, gene - (gene - current_gene),
                    sizeof(config->individuals[i].gene));
        } else {
            i++;
        }
    }
}