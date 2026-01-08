#include <stdio.h>
#include<stdlib.h>

//スタックを実現する構造体
typedef struct{
    /* data */
    int max;    //スタックの容量
    int ptr;    //スタックのポインタ
    int *stk;   //スタック本体(先頭要素のポインタ)
}Stack;

//スタックの準備初期化
int StackAlloc(Stack *s, int max){
    s -> ptr = 0;
    if((s -> stk = calloc(max, sizeof(int))) == NULL){
        s -> max = 0;
        return -1;
    }
    s -> max = max;
    return 0;
}

//スタックの後始末
void StackFree(Stack *s){
    if(s ->stk != NULL){
        free(s -> stk);
        s -> max = s -> ptr = 0;
    }
}

//スタックにデータをプッシュ
int StackPush(Stack *s, int x){
    if(s -> ptr >= s->max)
        return -1;
    s->stk[s->ptr++] = x;
    
    return 0;
}

//スタックからデータをポップ
int StackPop(Stack *s, int *x){
    if(s->ptr <= 0)
        return -1;
    *x = s->stk[--s->ptr];
    return 0;
}

//スタックからデータをピーク
int StackPeek(const Stack *s, int *x){
    if(s->ptr <= 0)
        return -1;
    *x = s->stk[s->ptr - 1];
    return 0;
}

//スタックの容量
int StackSize(const Stack *s){
    return s->max;
}
//スタックに積まれているデータ数
int StackNo(const Stack *s){
    return s->ptr;
}
//スタックは空か
int StackEmpty(const Stack *s){
    return s->ptr <= 0;
}
//スタックは満杯か
int StackFull(const Stack *s){
    return s->ptr >= s->max;
}
//スタックを空にする
void StackClear(Stack *s){
    s->ptr = 0;
}

void StackView(Stack *s){
    if(s->ptr == 0){
        printf("nostack");
        return;
    }

    for(int i = 0; i < s -> ptr;i++){
        printf("%d ", s->stk[i]);
    }
    printf("\n");
}
