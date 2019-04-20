#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>

void main1()
{
    char buf[100], buff[100];
    int x, y;
    printf("antes do open\n");
    
    int fd = open("entrada.txt", O_RDONLY|O_CREAT, 0644);
    // int fd = open("/etc/passwd", O_RDONLY);
    //O_TRUNC => limpa ficheiro inicialmente
    int fs = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    int fe = open("erros.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    
    //escreve e le no terminal(ecra e teclado)
    printf("inteiro: ");
    scanf("%d", &x);
    printf("1: %d\n", x);

    printf("antes do dup2\n");
    dup2(fd, 0);
    dup2(fs, 1);
    dup2(fe, 2);

    //passa a ler do ficheiro entrada e a escrever no ficheiro saida
    scanf("%d", &y);
    printf("1: %d\n2: %d\n", x, y);
    printf("antes do close\n");
    close(fd);
    close(fs);
    close(fe);
    
    //continua a ler do ficheiro entrada e a escrever no saida
    scanf("%d", &y);
    printf("1: %d\n2: %d\n", x, y);
    printf("depois de tudo\n");
}

void main2()
{
    int fd = open("entrada.txt", O_RDONLY|O_CREAT, 0644);
    int fs = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    int fe = open("erros.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    
    dup2(fd, 0);
    dup2(fs, 1);
    dup2(fe, 2);

    if(fork() == 0)
    {
        int n;
        char buffer[1024];
        while((n = read(0, buffer,1024)) > 0)
            write(1, buffer, n);
        if(n<0)
            write(2, buffer, n); //error
    }

    close(fd);
    close(fs);
    close(fe);
    
}


void main3(){
    int fd = open("entrada.txt", O_RDONLY|O_CREAT, 0644);
    int fs = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    int fe = open("erros.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    
    dup2(fd, 0);
    dup2(fs, 1);
    dup2(fe, 2);

    close(fd);
    close(fs);
    close(fe);

    execlp("wc","wc",NULL);
}

void teste(){
    int fd = open("entrada.txt", O_RDONLY|O_CREAT, 0644);
    int fs = open("saida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    int fe = open("erros.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    
    dup2(fd, 0);
    dup2(fs, 1);
    dup2(fe, 2);

    close(fd);
    close(fs);
    close(fe);

    write(1,"teste teste 123", 15);
    int n;
    char buffer[1024];
    while((n = read(0, buffer,1024))>0)
        write(1,buffer, n);
}

int main(int argc, char* argv[])
{
    // main1();
    // main2();
    // main3();
    teste();
    return 0;
}
