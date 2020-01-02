#ifndef VECTOR_H
#define VECTOR_H

struct vector{
   int length     ;
   int inuse      ;
   void ** head   ;
};

    
#define VEC_RESIZE(vec,data)                                      \
do{                                                               \
    if(vec == NULL)                                               \
    {                                                             \
        vec = malloc(sizeof(struct vector));                      \
        memset(vec,0,sizeof(struct vector));                      \
        vec->head = malloc(sizeof(data));                         \
        memset(vec->head, 0 ,sizeof(data));                       \
        vec->length = 1;                                          \
    }                                                             \
    else                                                          \
    {                                                             \
        if(vec->length == vec->inuse)                             \
        {                                                         \
            vec->head = realloc(vec->head , vec->length * 2 * 8); \
            vec->length *= 2;                                     \
        }                                                         \
    }                                                             \
}while(0)


#define VEC_FREE(vec)                                        \
do{                                                          \
    if(vec != NULL)                                          \
    {                                                        \
        if(vec->head != NULL)                                \
        {                                                    \
            free(vec->head);                                 \
            free(vec);                                       \
        }                                                    \
        else                                                 \
        {                                                    \
            free(vec);                                       \
        }                                                    \
    }                                                        \
}while(0)
    

#define VEC_ADD(vec,data)                                    \
do{                                                          \
    VEC_RESIZE(vec,data);                                    \
    vec->head[vec->inuse++] = (void *)data;                  \
}while(0)
    

#define VEC_GET(vec,index)  vec->head[index]

#endif