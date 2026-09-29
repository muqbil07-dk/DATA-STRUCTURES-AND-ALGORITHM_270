#include <stdio.h>
int main()
{
    char stack[1000];
    char ch;
    int top = -1;
    int balanced = 1;
    while ((ch = getchar()) != EOF && ch != '\n')
    {
        if (ch == '(' || ch == '[' || ch == '{')
        {
            top++;
            stack[top] = ch;
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (top == -1)
            {
                balanced = 0;
                break;
            }
            if ((ch == ')' && stack[top] != '(') ||
                (ch == ']' && stack[top] != '[') ||
                (ch == '}' && stack[top] != '{'))
            {
                balanced = 0;
                break;
            }
            top--;
        }
    }
    if (top != -1)
        balanced = 0;
    if (balanced == 1)
        printf("Balanced\n");
    else
        printf("Not Balanced\n");

    return 0;
}

