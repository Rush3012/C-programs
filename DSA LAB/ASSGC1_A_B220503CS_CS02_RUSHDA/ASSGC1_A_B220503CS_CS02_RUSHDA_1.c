#include <stdio.h>

int isop(char ch) {
    return (ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '(');
}

int top = -1;
char st[100000];

int checkParentheses(char expression[], int length) {
    top = -1;

    for (int i = 0; i < length; i++) {
        if (isop(expression[i]) == 1) {
            st[++top] = expression[i];
        }

        if (expression[i] == ')') {
            if (st[top] == '(') {
                return 1;
            }

            while (st[top] != '(') {
                top--;
            }
            top--;
        }
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    char a[1000000];

    scanf(" ");

    for (int i = 0; i < n; i++) {
        scanf("%c", &a[i]);
    }

    int result = checkParentheses(a, n);

    if (result) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}
