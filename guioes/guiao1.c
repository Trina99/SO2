#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_*
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// 0 = stdin  /  STDIN_FILENO
// 1 = stdout /  STDOUT_FILENO
// 2 = stderr /  STDERR_FILENO

// Devolve descritor de ficheiro ou erro
// int open(const char*path, int oflag [, mode]);

// Devolve número de bytes lidos ou erro
// ssize_t read(int fildes, void * buf, size_t nbyte);

// Devolve número de bytes escritos ou erro
// ssize_t write(int fildes, const void*buf, size_t nbyte);

// Apaga o descritor da tabela do processo
// Devolve:
// 0 , operação executada com sucesso
// -1, caso contrário
// int close(int fildes);

void ex1(){
    int fd = open("a.txt", O_CREAT| O_WRONLY, 0600);
    
    for(int i = 0; i < 2000000; i++)//174762
        write(fd, "panda",5); 

    close(fd);
}

void ex2_mycat1(){
    int n;
    char c;
    while((n = read(0, &c, 1)) > 0)
        write(1, &c, n);
}

void ex3_mycat2(int N){
    int n;
    char c[N];
    while((n = read(0, c, N)) > 0)
        write(1, c, n);
}

ssize_t ex5_readln(int fildes, char *buf, size_t nbyte){
    int n, i = 0;
    char c;
    while((n = read(fildes, &c, 1)) > 0 && i < nbyte && c != '\n')
        buf[i++] = c;
    buf[i++] = '\n';
    return i;
}

void ex6_nl(){
    /*
    int n, line = 1;
    char c[1024];

    while((n = read(0, c, 1024))>0)
    {
        write(1. , &line, 1);
        write(1, c, n);
        if(c[n-1] == '\n')
            line++;
    }
    */
    int n , line = 1;
    char buf[1024], str[12];
    while((n = ex5_readln(0, buf, 1024)) > 0) 
    {
        if(n > 1)
        {
            sprintf(str, "%d  ", line);
            write(1, str, strlen(str));
            write(1, buf, n);
            line++;
        }
    }
}

int main(int argc, char* argv[])
{
    // ex1();
    // ex2_mycat1();
    // ex3_mycat2(8);

    /*
    int fd = open("a.txt", O_RDONLY);
    char buff[24];
    int n = ex5_readln(fd,buff,16);
    printf("n = %d\nbuff = %s\n", n, buff);
    */

    ex6_nl();


   return 0; 
}
