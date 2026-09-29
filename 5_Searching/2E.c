#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXP 100
#define BUFLEN 105
#define GEMCOUNT 12
char *gems[] = {
    "NONE", "Garnet", "Amethyst", "Aquamarine", "Diamond",
    "Emerald", "Pearl", "Ruby", "Peridot", "Sapphire",
    "Tourmaline", "Topaz", "Lapis", 0
};
char ponies[MAXP][BUFLEN];
void remove_newline(char *s)
{
    int n;
    n = (int)strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}
int same_word(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}
int gem_rank(const char *name)
{
    char word[BUFLEN];
    int i;
    int j;
    int rank;
    i = 0;
    rank = 0;
    while (name[i] != '\0') {
        while (name[i] == ' ')
            i++;
        if (name[i] == '\0')
            break;
        j = 0;
        while (name[i] != '\0' && name[i] != ' ' && j < BUFLEN - 1) {
            word[j] = name[i];
            i++;
            j++;
        }
        word[j] = '\0';

        for (j = 1; j <= GEMCOUNT; j++) {
            if (same_word(word, gems[j]) && j > rank)
                rank = j;
        }
        while (name[i] == ' ')
            i++;
    }
    return rank;
}

int alpha_compare(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0') {
        int ca;
        int cb;

        ca = tolower((unsigned char)*a);
        cb = tolower((unsigned char)*b);
        if (ca != cb)
            return ca - cb;
        a++;
        b++;
    }
    if (*a == '\0' && *b == '\0')
        return 0;
    if (*a == '\0')
        return -1;
    return 1;
}

int comes_before(const char *a, const char *b)
{
    int ra;
    int rb;
    int comparison;

    ra = gem_rank(a);
    rb = gem_rank(b);
    if (ra != rb)
        return ra > rb;

    comparison = alpha_compare(a, b);
    if (comparison != 0)
        return comparison < 0;
    return strcmp(a, b) < 0;
}

int main(void)
{
    char line[BUFLEN];
    char temp[BUFLEN];
    int count;
    int i;
    int j;

    count = 0;
    while (fgets(line, sizeof(line), stdin) != NULL) {
        remove_newline(line);
        if (strcmp(line, "END") == 0)
            break;
        if (count < MAXP) {
            strcpy(ponies[count], line);
            count++;
        }
    }

    for (i = 1; i < count; i++) {
        strcpy(temp, ponies[i]);
        j = i - 1;
        while (j >= 0 && comes_before(temp, ponies[j])) {
            strcpy(ponies[j + 1], ponies[j]);
            j--;
        }
        strcpy(ponies[j + 1], temp);
    }

    for (i = 0; i < count; i++)
        printf("%s\n", ponies[i]);
    return 0;
}

