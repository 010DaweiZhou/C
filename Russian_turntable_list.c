#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32_t;

struct player{
    struct player *next;
    uint32_t player_number;
};

    
struct list{
    struct player *head;
    uint32_t count;
};

struct player * get_list_tail(struct list *list)
{
    struct player * p = NULL;
    
    if(list == NULL)
        return NULL;
      
    p = list->head;
    
    while(p->next != list->head)
    {
        p = p->next;
    }
    
    return p;
}

int main(int argc ,char ** argv)
{
    uint32_t player_count = 0;
    uint32_t shot = 0;
    struct list* list = NULL;
    struct player * player = NULL;
    struct player * temp = NULL;
    
    printf("Input how many players...\n");
    scanf("%u",&player_count);
    printf("%u players join,start game...\n",player_count);
    
    if(player_count == 0)
    {
        exit(1);
    }
    
    list = (struct list*)malloc(sizeof(struct list));
    memset(list , 0 ,sizeof(struct list));
    
    while(player_count)
    {
        player = (struct player*)malloc(sizeof(struct player));
        memset(player , 0 ,sizeof(struct player));
        
        player->player_number = player_count;
        
        if(list->count == 0)
        {
            list->head = player;
            list->head->next = list->head;
        }
        else
        {
            player->next = list->head->next;
            list->head->next = player;
        }
        
        list->count++;   
        player_count--;
    }
    
    printf("%u numbers are ready...\n",list->count);
    
    srand(time(NULL));
    
    while(list->count != 1)
    {
        player = list->head;
        
        shot = rand() % 6 + 1;
        
        printf("start at %u , boom after %u  ", player->player_number, shot);

        if(shot == 1)
        {
            temp = get_list_tail(list);
        }
        else
        {
            while(shot != 1)
            {
                temp = player;
                player = player->next;
                shot--;
            }
        }
        
        printf("player %u dead ... \n",player->player_number);
        
        temp->next = player->next;
        
        free(player);
        player = NULL;
        
        list->head = temp->next;
        list->count--;
    }
    
    printf("player %u win ...\n",list->head->player_number);
    
    free(list->head);
    free(list);
    
    exit(0);
}