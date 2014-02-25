#include <stdio.h>

void cd();
void dir();
void clr();
void environ();
void echo();
void help();
void pause();

int main(void)
{
    char program[256];
    while(1){
        fgets( program, 256, stdin );

        if("cd"==program){
            cd();
        }else if("dir"==program){
            dir();
        }else if("clr"==program){
            clr();
        }else if("environ"==program){
            environ();
        }else if("echo"==program){
            echo();
        }else if("help"==program){
            help();
        }else if("pause"==program){
            puase();
        }else if("quit"==program){
            return 0;
        }
    }
    return 0;
}

