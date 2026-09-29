#include <stdio.h>
#include <string.h>
int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return 1;
    return 0;
}
int main()
{
    char expression[1000];
    char stack[1000][1000];
    char left[1000];
    char right[1000];
    char result[1000];
    int top = -1;
    int i;
    scanf("%s", expression);
    for (i = 0; expression[i] != '\0'; i++)
    {
        if (isOperator(expression[i]) == 0)
        {
            top++;
            stack[top][0] = expression[i];
            stack[top][1] = '\0';
        }
        else
        {
            strcpy(right, stack[top]);
            top--;
            strcpy(left, stack[top]);
            top--;
            result[0] = expression[i];
            result[1] = '\0';
            strcat(result, left);
            strcat(result, right);
            top++;
            strcpy(stack[top], result);
        }
    }
    printf("%s\n", stack[top]);
    return 0;
}
