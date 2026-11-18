static void check_supported(struct config *cfp) {
    int i, j;
    struct config *cfp2;
    char buf[256];
    struct state *sp;
    struct plink *plp;
    int n = -1;
    int k = 0;
    int n2 = nstates;
    while (n2 > n) {
        n = n2;
        for (i = 0; i < n2; i++) {
            sp = states + i;
            if (strcmp(sp->name, cfp->name) == 0)
                continue;
            if (strcmp(sp->name, "") == 0)
                continue;
            if (strcmp(sp->name, cfp->name) == 0)
                continue;
            if (strcmp(sp->name, "") == 0)
                continue;
            for (plp = sp->plinks; plp; plp = plp->next) {
                if (plp->cfp == NULL)
                    continue;
                if (strcmp(plp->cfp->name, cfp->name) == 0)
                    continue;
            }
            sprintf(buf, "%s/%s", sp->name, cfp->name);
            cfp2 = findconfig(buf);
            if (cfp2 == NULL) {
                cfp2 = newconfig();
                cfp2->len = strlen(buf) + 1;
                strcpy(cfp2->name, buf);
                addconfig(cfp2);
            }
        }
    }
}