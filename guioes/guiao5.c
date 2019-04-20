#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

// 1.
void ex1_paiToFilho()
{
    int n;
    int fd[2];
    pipe(fd);
    // fd[0] = saida, fd[1]=entrada
    char buffer[1024];

    if(fork()==0) 
    {
        while((n = read(fd[0],buffer,1024)) > 0)
            write(1, buffer, n);
        close(fd[0]);
    } else {
        // close(fd[0]);
        sleep(5);
        write(fd[1], "estou a escrever",16);
        close(fd[1]);
    }
}

void ex1_filhoToPai()
{
    int n;
    int fd[2];
    pipe(fd);
    // fd[0] = saida, fd[1]=entrada
    char buffer[1024];

    if(fork()==0) 
    {
        // close(fd[0]);
        write(fd[1], "estou a escrever",16);
        close(fd[1]);
    } else {
        close(fd[1]);
        //filho fecha uma entrada, mas nao fecha todas
        while((n = read(fd[0],buffer,1024)) > 0)
            write(1, buffer, n);
        close(fd[0]);
    }
}

void ex3(){
    int fd[2];
    pipe(fd);

    if(fork() == 0)
    {
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        execlp("wc","wc",NULL);
        perror("ERRO!!!");
        _exit(-1);
    }else{
        int n;
        int buffer[1024];
        close(fd[0]);
        while((n = read(0,buffer,1024)) > 0)
            write(fd[1], buffer, n);
        close(fd[1]);
    }
}

// ls /etc | wc -l
// nao da para fazer tudo num so comando. o | indica que temos de redirecionar a informaçao. primeiro executamos ls, e com o resultado que obtivermos executamos wc
void ex4(){
    int fd[2];
    pipe(fd);
    if(fork()==0)
    {
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        execlp("wc","wc","-l",NULL);
        perror("Erro wc!");
        _exit(-1);

    }else{
        close(fd[0]);
        dup2(fd[1],1);
        close(fd[1]);

        execlp("ls","ls","/etc",NULL);
        perror("Erro ls!");
    }
}


// grep -v ^#  /etc/passwd --> encontra todas as linhas que NÃO começam por #
// cut -f7 -d: /etc/passwd --> encontra a 7º palavra de cada linha (entre :)
// uniq        /etc/passwd --> elimina linhas iguais consecutivas
// wc -l       /etc/passwd --> conta as linhas

// grep -v ^# /etc/passwd | cut -f7 -d: | uniq | wc -l
// Conta o número de vezes que o 7º parâmetro não é repetido (em linhas consecutivas não iniciadas por '#')


void ex5(){
    char* prog[4][5] =
    {{"grep","-v","^#","/etc/passwd",NULL},
     {"cut","-f7","-d:",NULL},
     {"uniq",NULL},
     {"wc","-l",NULL}};
     int i;
     int fd[2];
    for(i=0; i<3; i++)
    {
        pipe(fd);
        if(fork()==0)
        {
            close(fd[0]);
            dup2(fd[1],1);
            close(fd[1]);
            execvp(prog[i][0], prog[i]);
            perror("Erro!");
            _exit(-1);
        }else{
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        }
    }
    execvp(prog[i][0], prog[i]);
    perror("Erro!");
    exit(-1);
}


void teste()
{
    
    int n;
    int fd[2];
    pipe(fd);
    // fd[0] = saida, fd[1]=entrada
    char buffer[1024];

    if(fork()==0) 
    {
        write(fd[1],"filho teste7", 12);
        while((n = read(fd[0],buffer,1024)) > 0)
            write(1, buffer, n);
        // close(fd[0]);
    } else {
        // close(fd[0]);
        // sleep(5);
        write(fd[1], "estou a escrever8\n",20);
        // close(fd[1]);
    }
    //COMO É POSSIVEL, TODOS OS CLOSES ESTAO COMENTADOS E MESMO ASSIM O PROGRAMA PARA, AWESOME,
}




int main()
{
    // ex1_paiToFilho();
    // ex1_filhoToPai();
    // ex3();
    // ex4();
    // ex5();
    teste();
}
