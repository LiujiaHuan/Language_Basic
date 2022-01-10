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



void strbuf_grow(struct strbuf *sb,size_t len){//利用了vector增长的思想
    //但是增长多少由len决定，调用的时候一般会传入sb->alloc达到双倍目的
    printf("oversize\n____auto-grow_____\nfrom %d to %d\n",sb -> alloc,sb -> alloc + len);
    char *a;
    a = calloc(sb->alloc + len,sizeof(char));
    for(int i = 0 ; i < sb->len;i++){
        *(a+i) = *((sb -> buf)+i);//赋值
    }
    free(sb -> buf);//free以前开辟的空间
    sb -> buf = a;//更新地址
    sb -> alloc += len;//更新容量
}



void strbuf_add(struct strbuf *sb,const void *data,size_t len){//后面很多函数都基于这个实现
    if(sb -> alloc < sb -> len + len){//原有容量充足
        while(sb -> len + len > sb -> alloc){//增长到能存下原有len以及新增len为止
            strbuf_grow(sb,sb -> alloc);
        }
        for(int i = sb -> len;i < sb -> len + len  ;i++){//拷贝
            *(sb -> buf + i) = *((char *)data + (i - sb -> len));
        }
        sb -> len += len;//更新len
    }
    else{//原有容量不足
        for(int i = sb -> len; i< sb->len + len;i++){
            *(sb -> buf + i) = *((char*)data + (i - sb -> len));
        }
        sb -> len += len;//更新len
    }
}



void strbuf_addch(struct strbuf *sb,int c){
    char* a =&c;
    strbuf_add(sb,a,1);
}



void strbuf_addstr(struct strbuf *sb,const char *s){
    strbuf_add(sb,s,strlen(s));
}



void strbuf_addbuf(struct strbuf *sb,const struct strbuf *sb2 ){
    strbuf_addstr(sb,sb2->buf);
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
void test_strbuf_grow(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_grow(&a,20);
    show_all_attr(&a);
}
void test_strbuf_add(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_add(&a,"sa",2);
    show_all_attr(&a);
}
void test_strbuf_addch(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_addch(&a,'b');
    show_all_attr(&a);
}
void test_strbuf_addstr(){
        struct strbuf a;
        strbuf_attach(&a,"xiyou", 5, 8);
        strbuf_addstr(&a,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        show_all_attr(&a);
};
void test_over_size(){
    printf("strbuf_addch and strbuf_add oversize test\n");
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 5);
    strbuf_addch(&a,'b');
    show_all_attr(&a);
}
void test_strbuf_addbuf(){
    struct strbuf a;
    struct strbuf b;
    strbuf_attach(&a,"xiyou", 5, 7);
    strbuf_attach(&b,"1234567890", 10, 10);
    strbuf_addbuf(&a,&b);
    show_all_attr(&a);
}
int main(){

}
