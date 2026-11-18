void check_supported(struct element *element) {
    int cmp = -1;
    int low = 0;
    int high = supported_elements_count;
    int mid;
    struct tree_node *node;
    struct attribute *attr;
    char buf[0x110];
    char **allowed_attr;

    // Binary search for the element in supported_elements
    while (high > low) {
        mid = (high + low) / 2;
        cmp = strcmp(element->name, supported_elements[mid].name);
        if (cmp == 0) {
            break;
        }
        if (cmp < 0) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    // If element is not supported
    if (cmp != 0) {
        node = tree_search(unknown_element_tree, element->name);
        if (node == NULL) {
            node = misc_malloc(strlen(element->name) + 0x20);
            strcpy((char *)node + 0x19, element->name);
            tree_insertnode(unknown_element_tree, (const char *)node);
        }
        return;
    }

    // If element is supported, check its attributes
    attr = element->attributes;
    while (attr != NULL) {
        if (attr->name[0] == '#') {
            goto next_attr;
        }

        if (strcmp(attr->name, "xml") == 0) {
            if (strcmp(attr->value, "namespace") == 0) {
                goto next_attr;
            }
            sprintf(buf, "Unknown attribute '%s' in element '%s'", attr->name, attr->value, element->name);
        } else {
            allowed_attr = supported_elements[mid].allowed_attributes;
            if (allowed_attr != NULL) {
                if (strcmp(*allowed_attr, "") == 0) {
                    goto next_attr;
                }
                while (*allowed_attr != NULL) {
                    if (strcmp(*allowed_attr, attr->name) == 0) {
                        break;
                    }
                    allowed_attr++;
                }
                if (*allowed_attr != NULL) {
                    goto next_attr;
                }
            }
            sprintf(buf, "Unknown attribute '%s' in element '%s'", attr->name, element->name);
        }

        node = tree_search(unknown_element_tree, buf);
        if (node == NULL) {
            node = misc_malloc(strlen(buf) + 0x20);
            strcpy((char *)node + 0x19, buf);
            tree_insertnode(unknown_element_tree, (const char *)node);
        }

    next_attr:
        attr = attr->next;
    }
}