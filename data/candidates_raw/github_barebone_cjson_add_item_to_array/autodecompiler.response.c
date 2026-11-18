int suffix_object(object_t *head, object_t *obj)
{
    object_t *child = NULL;
    int ret;

    if (!obj || !head || head == obj) {
        ret = 0;
        goto out;
    }

    child = head->next;
    if (!child) {
        head->next = obj;
        obj->prev = obj;
        obj->next = NULL;
    } else {
        if (child->prev) {
            suffix_object(child->prev, obj);
            head->next->prev = obj;
        }
    }

    ret = 1;
out:
    return ret;
}