#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
// Function to implement the KMP algorithm
void KMP(const char* text, const char* pattern, int m, int n)
{
    // base case 1: pattern is NULL or empty
    if (*pattern == '\0' || n == 0) {
        printf("The pattern occurs with shift 0");
    }
 
    // base case 2: text is NULL, or text's length is less than that of pattern's
    if (*text == '\0' || n > m) {
        printf("Pattern not found");
    }
 
    // next[i] stores the index of the next best partial match
    int next[n + 1];
 
    for (int i = 0; i < n + 1; i++) {
        next[i] = 0;
    }
 
    for (int i = 1; i < n; i++)
    {
        int j = next[i + 1];
 
        while (j > 0 && pattern[j] != pattern[i]) {
            j = next[j];
        }
 
        if (j > 0 || pattern[j] == pattern[i]) {
            next[i + 1] = j + 1;
        }
    }
 
    for (int i = 0, j = 0; i < m; i++)
    {
        if (*(text + i) == *(pattern + j))
        {
            if (++j == n) {
                printf("The pattern occurs with shift %d\n", i - j + 1);
            }
        }
        else if (j > 0)
        {
            j = next[j];
            i--;    // since `i` will be incremented in the next iteration
        }
    }
}
 
// Program to implement the KMP algorithm in C
int main(void)
{
    char* text = "ABCABAABCABAC";
    char* pattern = "CAB";
 
    int n = strlen(text);
    int m = strlen(pattern);
 
    KMP(text, pattern, n, m);
 
    return 0;
}