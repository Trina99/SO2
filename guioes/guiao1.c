#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> //O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_*
#include <unistd.h>

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

int main(int argc, char* argv[])
{
    ex1();
   return 0; 
}