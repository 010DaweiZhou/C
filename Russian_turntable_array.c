#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main()
{
    unsigned int num = 0;
    unsigned int total = 0;
    unsigned int shot = 0;
    unsigned int location = 0;
    
    unsigned int node = 0;
    
    printf("please input number of player...\n");
    scanf("%d",&num);
    printf("%d players join , start game ...\n",num);
    total = num;
    
    srand(time(NULL));
    
    int plays[num];
    
    while(num != 1)
    {
        shot = rand() % 6 + 1;
        
        printf("start at %d , shot %d times...\n", location + 1, shot) ;
        
        while(--shot)
        {
            do{
                location ++;
                location %= total;
            }while(plays[location] == -1);
        }
        
        plays[location] = -1;
        
        printf("player %d out...\n",location + 1);
        
        do{
            location = (location + 1) % total;
        }while( plays[location] == -1);
        
        num --;
    }
    
    return 0;
}