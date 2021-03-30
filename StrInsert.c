#include <stdio.h>
#include <string.h>

static 
int str_insert(char * s , char * t , int i)
{
    int w = strlen(s);
    int c = strlen(t);
    
    printf("strlen(s) = %ld\n", strlen(s));
    printf("strlen(t) = %ld\n", strlen(t));
    
    memcpy(&s[strlen(t) + i], &s[i], strlen(s) - i);
    memcpy(&s[i], t, strlen(t));
    
    s[w + c] = '\0';
    
    printf("strlen(s) = %ld\n", strlen(s));
    printf("strlen(t) = %ld\n", strlen(t));
    
    printf("%s\n",s);
}

int main()
{
    char a[200] = "hello world";
    char b[100] = "the ";
    
    memset(a, 49, 100);
    strcpy(a, "hello world");
    
    str_insert(a, b, 6);

}