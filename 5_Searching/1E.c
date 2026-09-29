#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LEN 20
int main(void)
{
    char var[3][LEN];
    char inp[3][LEN];
    double m;
    double d;
    double x;
    double value;
    char missing;
    int i;
    m = 0.0;
    d = 0.0;
    x = 0.0;
    missing = '?';
    for (i = 0; i < 3; i++) {
        scanf("%19s %19s", var[i], inp[i]);
        if (strcmp(inp[i], "?") == 0) {
            missing = var[i][0];
        } else if (var[i][0] == 'M') {
            m = atof(inp[i]);
        } else if (var[i][0] == 'D') {
            d = atof(inp[i]);
        } else if (var[i][0] == 'X') {
            x = atof(inp[i]);
        }
    }
    if (missing == 'M')
        value = -d * x;
    else if (missing == 'D')
        value = -m / x;
    else
        value = -m / d;
    printf("%c %.2f\n", tolower((unsigned char)missing), value);
    return 0;
}

