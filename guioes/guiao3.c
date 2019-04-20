#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void main1()
{
    char* prog = "/usr/bin/ls";
    // execl(prog, "ls", "-l", NULL);
    execlp("ls", "ls", "-l", NULL);
    
    // char* argv[] = {"ls", "-l", NULL};
    // execv(prog,argv);
    // execvp("ls", argv);

    perror(prog);
    printf("ERRO!\n");
    
    exit(1);
}

void main2()
{
    if(fork() == 0)
    {
        char* prog = "/usr/bin/ls";
        execl(prog, "ls", "-l", NULL);

        perror(prog);
        printf("ERRO!\n");
    
        _exit(1);
    }
}

void main3(int argc, const char** argv)
{
    //execvp("echo", argv);
    //começa em 1 para nao imprimir o ./a.out
    for (int i = 1; i < argc; i++)
        printf("%s ", argv[i]);

    printf("\n");
}


void main5(int argc, const char** argv)
{
    for(int i = 1; i < argc; i++)
        if(fork() == 0)
        {
            printf("%d. filho %d\n", i, getpid());
            execlp(argv[i], argv[i], NULL);
            _exit(0);
        }
        else wait(NULL);
}


void main6(int argc, char* argv[])
{
    if(argc > 1)
        execvp(argv[1], argv+1);
    else perror("ERRO! sem argumentos ");
}

int main(int argc, char* argv[])
{
    // char prog[] = "ls -l -a";
    main1();
    // main2();
    // main3(argc, argv);
    // main5(argc, argv);
    // system("ls -l");
    // main6(argc, argv);
    return 0;
}






// -------- // ---------------------------------------------------

/*
int system1(char* cmd)
{
    char* prog = "/usr/bin";
    char* args[]={"ls", "-l", "-a", NULL};
    if(fork()==0)
    {
        execvp(prog, cmd, args);
        perror(cmd);

        _exit(1);
    }
    else
        wait(NULL);
}
*/

/*
int my_system(char* cmd){
    // usar strtok para obter args a partir de cmd
    char* args[]={"ls", "-l", "-a", NULL};
    if(fork()==0){
        execvp(prog, args);

        //nada do que aparece aqui sera executado!!!!
        //(a nao ser que haja um erro!)
        perror(prog); //printf("ERROR!\n");
        _exit(1);
    }else{
        wait(NULL);
    }
}

//experimentem os comandos exit e cd
int main(){
    while(1){
        write(1, "$ ",2);
        le_linha(0, cmd);
        my_system(cmd);
    }
}

int main(int argc, char* argv[])
{
    char prog[] = "ls -l -a";
    printf("ANTES \n");
    my_system(prog);
    printf("DEPOIS \n");
}
*/


