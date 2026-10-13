#include <stdio.h>
#include <string.h>
int main(void)
{
    char line[1005];
    int count[256] = {0};
    int l;
    int i;
    int best_character = 0;
    int best_count = 0;

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 0;
    }
    l = (int)strlen(line);
    for(i=0;i<l;i++) {
        if (line[i] != '\n' && line[i] != '\r') {
            count[(unsigned char)line[i]]++;
        }
    }

    for (i = 0; i < 256; i++) {
        if (count[i] > best_count) {
            best_count = count[i];
            best_character = i;
        }
    }
    printf("%c %d\n", (char)best_character, best_count);
    return 0;
}

