static struct config *ogs_pfcp_subnet_add(const char *name, const char *value,
                               const char *comment, const char *group) {
    struct config *conf = NULL;
    struct config *tmp = NULL;
    int ret;

    do {
        if (conf == NULL) {
            conf = (struct config *)malloc(sizeof(struct config));
            if (conf == NULL)
                error("out of memory");
        }

        if (name) {
            ret = strncpy_s(&conf->name[0], CONFIG_NAME_LEN, name, 0);
            if (ret!= 0)
                error("strncpy_s() failed");
        }

        if (value) {
            ret = strncpy_s(&conf->value[0], CONFIG_VALUE_LEN, value, 0);
            if (ret!= 0)
                error("strncpy_s() failed");
        }

        if (comment) {
            ret = strncpy_s(&conf->comment[0], CONFIG_COMMENT_LEN, comment, 0);
            if (ret!= 0)
                error("strncpy_s() failed");
        }

        if (group) {
            strncpy_s(&conf->group[0], CONFIG_GROUP_LEN, group, 0);
            add_config_to_group(&config_groups, conf);
        }

        conf->next = tmp;
        tmp = conf;
        conf = NULL;
    } while (1);
}