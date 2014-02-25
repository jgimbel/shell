#include <stdio.h>

<<<<<<< HEAD
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
=======
int main(void)
{
    string program;
    progam < cin;

    switch(program){
    case "cd":
        break;
    case "dir":
        break;
    case "clr":
        break;
    case "environ":
        break;
    case "echo":
        break;
    case "help":
        break;
    case "pause":
        break;
    case "quit":
        break;
>>>>>>> cec56bc94b576b8481d6b4b0ebb4aebacf4e591b
    }

    printf("Hello World!\n");
    return 0;
}

