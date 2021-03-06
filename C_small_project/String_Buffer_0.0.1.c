/*---------------------------------|
usr:LiuJiahuan
Description:String_buffer.c
Version:beta-0.0.0
Time:2022-1-8 21:00
----------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//结构体定义
int sz;
struct strbuf {
    int len;     //当前缓冲区（字符串）长度
    int alloc;   //当前缓冲区（字符串）容量
    char *buf;   //缓冲区（字符串）
};


void show_all_attr(struct strbuf *sb){
    printf("string is: %s\nlen is: %d \ncapacity is:%d\n",sb -> buf,sb -> len,sb -> alloc);
}


void strbuf_init(struct strbuf *sb, size_t alloc){
    sb -> buf = (char*)calloc(alloc,sizeof(char));
    sb -> len = 0;
    sb -> alloc = alloc;
}



void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    //不用考虑是否已经初始化，容量够不够，因为这里task要求属于第一部分的简单操作，不涉及扩容
    if(alloc < len) {
        printf("error");
        return;
    }
    sb -> buf = (char*)calloc(alloc,sizeof(char));
    sb -> len = len;
    sb -> alloc = alloc;
    for(int i = 0 ; i < len ; i++){
        *((sb -> buf)+i) = (char)(*(char*)(str+i));
    }
}



void strbuf_release(void *sb){
    free(sb+8);
    free(sb);
}



void strbuf_swap(struct strbuf *a, struct strbuf *b){
    struct strbuf temp;
    temp = *a;
    (*a).len = b -> len;
    (*a).alloc = b -> alloc;
    (*a).buf = b -> buf;

    (*b).len = temp.len;
    (*b).alloc = temp.alloc;
    (*b).buf = temp.buf;
    //strbuf_release(&temp);
}



char *strbuf_detach(struct strbuf *sb, size_t *sz){
    *sz = sb -> len;
    return sb -> buf;
}



int strbuf_cmp(const struct strbuf *first, const struct strbuf *second){
    if(first -> len != second -> len){
        return 0;
    }
    else{
        if(!strcmp(first->buf,second->buf)){
            return 1;
        }
        return 0;
    }
}



void strbuf_reset(struct strbuf *sb){
    for(int i = 0 ; i < sb -> len;i++){
        *((sb -> buf)+i) = '\0';
    }
    sb -> len = 0;
}



void test_strbuf_cmp(){
    struct strbuf a;
    struct strbuf b;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_attach(&b,"xiyou", 5, 8);
    int flag = strbuf_cmp(&a,&b);
    printf("%d",flag);
}


void test_strbuf_reset(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_reset(&a);
    show_all_attr(&a);
}



int main(){

}
