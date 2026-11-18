void reverse(char s[])
{
    char *head, *tail;

    for (tail = s; *tail; ++tail)
        ;

    for (head = s; head < --tail; ++head)
        *head = *head ^ *tail,
        *tail = *head ^ *tail,
        *head = *head ^ *tail;
}