#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


//ex1.
void main1()
{
    printf("Pai: %d - Filho: %d\n", getppid(), getpid());
    //este pai é o terminal

    // if(fork() == 0)
        // printf("Pai: %d - Filho: %d\n", getppid(), getpid());
    // else 
        // printf("Pai: %d - Filho: %d\n", getppid(), getpid());
    //nao e a soluçao, era so para experimentar
}


//ex2.
void main2()
{
    int pid = fork();
    if (pid == 0) //filho
        printf("sou o filho, o meu pai é %d e eu sou %d\n", getppid(), getpid());
    else {
        int pid2 = wait(NULL); 
        printf("sou o pai, o meu filho é %d == %d e eu sou %d\n", pid, pid2, getpid());
    }
}

//ex3.
void main3()
{
    for(int i = 0; i < 10; i++)
    {
        if(fork() == 0)
        {
            printf("filho: %d  pai: %d\n", getpid(), getppid());
            _exit(i+1);
        }
        else
        {
            int pid;
            int status;
            pid = wait(&status);
            if(WIFEXITED(status))
            {
                status = WEXITSTATUS(status);
                printf("pai: %d  %d. filho: %d\n", getpid(), status, pid);
            }
        }
    }
}

void main4()
{
    for(int i = 0; i < 10; i++)
    {
        if(fork() == 0)
        {
            printf("filho: %d  pai: %d\n", getpid(), getppid());
            _exit(i+1);
        }
    }

    for(int i = 0; i<10; i++)
    {
        int pid;
        int status;
        pid = wait(&status);
        if(WIFEXITED(status))
        {
            status = WEXITSTATUS(status);
            printf("pai: %d  %d. filho: %d\n", getpid(), status, pid);
        }
    }
}

void main5(int n)
{
    if(n > 0)
        if(fork() == 0)
        {
            {
                printf("filho: %d  pai: %d\n", getpid(), getppid());
                main5(n-1);
                _exit(n);
            }
        }
        else
        {
            int pid, status;
            pid = wait(&status);
            if(WIFEXITED(status))
            {
                status = WEXITSTATUS(status);
                printf("pai: %d  %d. filho: %d\n", getpid(), status, pid);
            }
        }
}

void main6()
{
    //inicializa matriz;
    int linhas = 10;
    int colunas = 10000;
    int matriz[linhas][colunas];
    for(int i = 0; i < linhas; i++)
        for(int j = 0; j < colunas; j++)
            matriz[i][j] = 0;
    
    //posicoes onde vamos por um certo numero
    int x = 27;
    matriz[2][45] = matriz[5][20] = matriz[3][30] = matriz[5][50] = x;

    //procura
    int v[linhas];
    for (int i = 0; i < linhas; i++)
        if ((v[i] = fork()) == 0) 
        {
            for (int j = 0; j < colunas; j++) 
                if (matriz[i][j] == x) 
                    _exit(j);
            _exit(0);
        }
   
   int pid, status;
    while ((pid = wait(&status)) != -1) 
    {
        int i;
        for (i = 0; i < linhas && pid != v[i]; i++);
            if (status = WEXITSTATUS(status))
            {
                // status = WEXITSTATUS(status);
                // printf("Valor %d está na linha %d\n", x, i);
                printf("Filho %d encontrou %d na linha %d coluna %d\n", pid, x, i, status);

                // printf("linha %d\n", i);
            
            }
            //else
              //  printf("Filho %d nao encontrou nada na linha %d\n", pid, i);
    }
    //cada filho está encarregue de ver se o valor x está numa linha. assim que encontra o valor nao percorre o resto. porque ele só quer saber se existe ou não o valor, nao importa em que coluna esta ou se existe mais do que um valor;
}


void teste()
{
    for(int i = 0; i < 10; i++)
    {
        if(fork() == 0)
        {
            // printf("filho: %d  pai: %d\n", getpid(), getppid());
            _exit(i+1);
        }
    }

    for(int i = 0; i<10; i++)
    {
        int pid;
        int status;
        pid = wait(&status);
        printf("status1: %d ",&status);
        if(WIFEXITED(status))
        {
            status = WEXITSTATUS(status);
            // printf("pai: %d  %d. filho: %d\n", getpid(), status, pid);
            printf("status2: %d\n", status);
        }
    }
}

int main()
{
    // main1();  
    // main2();
    // main3();
    // main4();
    // main5(10);
    // main6();
    // teste();

}


