#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char M[33], Q[33];
char Qn = '0';
char A[33];
int n;
bool is_complete = false;

char *tobin(int n)
{
    char *binary = (char *)malloc(33 * sizeof(char));
    int i = 0;
    if (n < 0)
    {
        n = abs(n);
        n = ~n + 1;
    }
    while (n > 0)
    {
        binary[i++] = (n % 2) + '0';
        n /= 2;
    }
    binary[i] = '\0';
    strrev(binary);
    return binary;
}

void equalize(char *str, int count)
{
    char temp[33];
    int i;

    for (i = 0; i < count; i++)
    {
        temp[i] = '0';
    }
    temp[i] = '\0';

    strcat(temp, str);
    strcpy(str, temp);
}

void initA(int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        A[i] = '0';
    }
    A[i] = '\0';
}

int todec(char *str)
{
    int i, dec = 0;
    for (i = 0; i < strlen(str); i++)
    {
        dec = dec * 2 + (str[i] - '0');
    }
    return dec;
}

void binary_subtraction()
{
    int borrow = 0;
    for (int i = strlen(A) - 1; i >= 0; i--)
    {
        int a = A[i] - '0';
        int m = M[i] - '0';
        int diff = a - m - borrow;
        if (diff < 0)
        {
            diff += 2;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        A[i] = diff + '0';
    }
}
void binary_addition()
{
    int carry = 0;
    for (int i = strlen(A) - 1; i >= 0; i--)
    {
        int a = A[i] - '0';
        int m = M[i] - '0';
        int sum = a + m + carry;
        if (sum > 1)
        {
            sum -= 2;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        A[i] = sum + '0';
    }
}

void shifter()
{
    char tempA, tempQ;
    tempA = A[strlen(A) - 1];
    tempQ = Q[strlen(Q) - 1];
    // printf("tempA: %c\ntempQ: %c\n", tempA, tempQ);
    
    for (int j = strlen(A) - 1; j > 0; j--)
    {
        A[j] = A[j - 1];
    }
    for (int j = strlen(Q) - 1; j > 0; j--)
    {
        Q[j] = Q[j - 1];
    }
    // printf("A: %s\nQ: %s\n ", A, Q);
    Q[0] = tempA;

    Qn = tempQ;
}
void ensure_four_bits()
{
    if (strlen(A) < 4)
    {
        equalize(A, 4 - strlen(A));
    }
    if (strlen(M) < 4)
    {
        equalize(M, 4 - strlen(M));
    }
    if (strlen(Q) < 4)
    {
        equalize(Q, 4 - strlen(Q));
    }
}

int twos_complement(int n)
{
    int x = ~n + 1;
    return x;
}

void errorcheck(int multiplicand, int multiplier)
{
    if (multiplicand > 16 || multiplier > 16)
    {
        equalize(A, 1);
        equalize(M, 1);
        equalize(Q, 1);
    }
    else if (multiplicand > 15 || multiplier > 15)
    {
        equalize(A, 2);
        equalize(M, 2);
        equalize(Q, 2);
    }
    else if (multiplicand > 7 || multiplier > 7)
    {
        equalize(A, 1);
        equalize(M, 1);
        equalize(Q, 1);
    }
}

int main()
{
    int multiplier, multiplicand, i;

    printf("Enter the multiplier: ");
    scanf("%d", &multiplier);
    printf("Enter the multiplicand: ");
    scanf("%d", &multiplicand);

    strcpy(M, tobin(multiplicand));
    strcpy(Q, tobin(multiplier));

    if (strlen(M) > strlen(Q))
    {

        equalize(Q, strlen(M) - strlen(Q));
    }
    else if (strlen(M) < strlen(Q))
    {

        equalize(M, strlen(Q) - strlen(M));
    }
    ensure_four_bits();

    errorcheck(multiplicand, multiplier);
    n = strlen(M);
    initA(n);
    printf("%s\n%s\n%s\nn:%d\n", M, Q, A, n);

    for (i = 0; i < n; i++)

    {

        if (Q[strlen(Q) - 1] == Qn)
        {

            shifter();

            printf("A: %s\nQ: %s\n Qn:%c\n", A, Q, Qn);
        }
        else if (Q[strlen(Q) - 1] == '1' && Qn == '0')
        {
            binary_subtraction();
            printf("A:%s\n\n", A);
            shifter();
            printf("A: %s\nQ: %s\n Qn:%c\n\n", A, Q, Qn);
        }
        else
        {
            binary_addition();
            printf("A:%s\n\n", A);
            shifter();
            printf("A: %s\nQ: %s\n Qn:%c\n\n", A, Q, Qn);
        }
    }
    if (multiplicand > 15 || multiplier > 15)
    {
        shifter();
        printf("A: %s\nQ: %s\n Qn:%c\n\n", A, Q, Qn);
    }

    strcat(A, Q);

    printf("Product is %d\n", todec(A));
}