char * reorganizeString(char * S){
    int len = strlen(S);
    if (len == 0) {
        char *tmp = (char *)malloc(sizeof(char));
        if (tmp != NULL) {
            tmp[0] = '\0';
        }
        return tmp;
    }

    int cnt[256];
    memset(cnt, 0, sizeof(cnt));

    int i = 0;
    while (1) {
        if (i >= len) {
            break;
        }
        cnt[S[i]]++;
        i++;
    }

    HeapNode heap[256];
    int heap_size = 0;

    int j = 0;
    while (1) {
        if (j >= 257) {
            break;
        }
        if (cnt[j] > 0) {
            HeapNode node;
            node.freq = cnt[j];
            node.ch = (char)j;
            heap[heap_size++] = node;
        }
        j++;
    }

    for (int k = heap_size / 2 - 1; k >= 0; k--) {
        heapify_down(heap, heap_size, k);
    }

    if (heap_size > 0 && heap[0].freq * 2 > len + 1) {
        char *tmp = (char *)malloc(sizeof(char));
        if (tmp != NULL) {
            tmp[0] = '\0';
        }
        return tmp;
    }

    char *res = (char *)malloc((len + 1) * sizeof(char));
    int pos = 0;
    while (1) {
        if (heap_size < 3) {
            HeapNode node = heap_pop(heap, &heap_size);
            res[pos++] = node.ch;
            if (heap_size > 0) {
                HeapNode second = heap_pop(heap, &heap_size);
                res[pos++] = second.ch;
                if (node.freq - 1 > 0) {
                    node.freq--;
                    heap_push(heap, &heap_size, node);
                }
                if (second.freq - 1 > 0) {
                    second.freq--;
                    heap_push(heap, &heap_size, second);
                }
            }
            break;
        } else {
            HeapNode node = heap_pop(heap, &heap_size);
            HeapNode second = heap_pop(heap, &heap_size);

            res[pos++] = node.ch;
            res[pos++] = second.ch;

            node.freq--;
            second.freq--;

            if (node.freq > 0) {
                heap_push(heap, &heap_size, node);
            }
            if (second.freq > 0) {
                heap_push(heap, &heap_size, second);
            }
        }
    }
    res[pos] = '\0';

    return res;
}