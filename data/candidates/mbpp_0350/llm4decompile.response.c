int func0(char *s) {
    int arr[26];
    int maxOcc = 0;
    int len = strlen(s);
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < len; i++) {
        arr[s[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        maxOcc = maxOcc > arr[i] ? maxOcc : arr[i];
    }
    return len - maxOcc;
}