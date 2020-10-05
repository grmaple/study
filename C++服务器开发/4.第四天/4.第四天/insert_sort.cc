
#define swap(a, b) { \
    __typeof(a) __a = a; \
    a = b, b = __a; \
}

void insert_sort(int *arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            --j;
        }
    }
    return ;
}

void unguarded_insert_sort(int *arr, int l, int r) {
    int ind = l;
    for (int i = l + 1; i <= r; i++) {
        if (arr[ind] > arr[i]) ind = i;
    }
    while (ind > l) {
        swap(arr[ind], arr[ind - 1]);
        --ind;
    }
    for (int i = l + 2; i <= r; i++) {
        int j = i;
        while (arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            --j;
        }
    }
    return ;
}
