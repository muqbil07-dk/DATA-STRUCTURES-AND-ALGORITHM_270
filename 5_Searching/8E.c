#include <stdio.h>
#include <string.h>

#define CMDS 4
#define MAXWORDS 100
#define MAXWORDLEN 105
#define STORYLEN 1005
#define TOKENS 4

int cl[CMDS];
char *lists[CMDS][MAXWORDS];
char words[CMDS][MAXWORDS][MAXWORDLEN];
char *tokens[TOKENS] = {"[N]", "[AV]", "[V]", "[AJ]"};
char *cmds[CMDS] = {"NOUNS", "ADVERBS", "VERBS", "ADJECTIVES"};

void remove_newline(char *s)
{
    int n;

    n = (int)strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

int command_number(char *line)
{
    int i;

    for (i = 0; i < CMDS; i++) {
        if (strcmp(line, cmds[i]) == 0)
            return i;
    }
    return -1;
}

int token_at(char *s)
{
    int i;

    for (i = 0; i < TOKENS; i++) {
        if (strncmp(s, tokens[i], strlen(tokens[i])) == 0)
            return i;
    }
    return -1;
}

int main(void)
{
    char story[STORYLEN];
    char line[MAXWORDLEN];
    int current;
    int command;
    int i;
    int index;
    int used[CMDS];

    for (i = 0; i < CMDS; i++)
        cl[i] = 0;

    if (fgets(story, sizeof(story), stdin) == NULL)
        return 0;
    remove_newline(story);

    current = -1;
    while (fgets(line, sizeof(line), stdin) != NULL) {
        remove_newline(line);
        if (strcmp(line, "END") == 0)
            break;

        command = command_number(line);
        if (command >= 0) {
            current = command;
        } else if (current >= 0 && cl[current] < MAXWORDS) {
            strcpy(words[current][cl[current]], line);
            lists[current][cl[current]] = words[current][cl[current]];
            cl[current]++;
        }
    }

    for (i = 0; i < CMDS; i++)
        used[i] = 0;

    for (i = 0; i < 2; i++) {
        index = 0;
        while (story[index] != '\0') {
            command = token_at(&story[index]);
            if (command >= 0) {
                if (used[command] < cl[command])
                    printf("%s", lists[command][used[command]++]);
                index += (int)strlen(tokens[command]);
            } else {
                putchar(story[index]);
                index++;
            }
        }
        printf("\n");
    }
    return 0;
}

