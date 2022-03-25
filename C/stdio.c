//--------------------------------------define-------------------------------------------------------//
#define BUFSIZ 512    //数组长度（buf）宏

#define EOF (-1)



//--------------------------------------function------------------------------------------------------//

void setbuf(FILE *stream, char *buffer)
  
  @param1:  stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了一个打开的流
  @param2:  这是分配给用户的缓冲，它的长度至少为 BUFSIZ 字节，BUFSIZ 是一个宏常量，表示数组的长度。
  @funtion: 定义流 stream 应如何缓冲。该函数应在与流 stream 相关的文件被打开时，且还未发生任何输入或输出操作之前被调用一次。
  @e.g:/*
                        char buf[BUFSIZ];
                        setbuf(stdout, buf);
                        puts("hi");
                        fflush(stdout);
                        return(0);          程序在即将输出的时候，发送输出到 STDOUT，否则它将缓冲输出*/
                        
