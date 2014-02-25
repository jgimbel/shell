#include <stdio.h>
#include <unistd.h>
#include <string.h>

void cd();
void dir();
void clr();
void environ();
void echo(char *string);
void help();
void ps();

int main(void)
{
    while(1){
        char program[256];
        gets(program);

        char *line = strtok(program, " ");
        if(strcmp(line,"cd")==0){
            cd();
        }else if(strcmp(line,"dir")==0){
            dir();
        }else if(strcmp(line,"clr")==0){
            clr();
        }else if(strcmp(line,"environ")==0){
            environ();
        }else if(strcmp(line,"echo")==0){
            echo(program);
        }else if(strcmp(line,"help")==0){
            help();
        }else if(strcmp(line,"pause")==0){
            ps();
        }else if(strcmp(line,"quit")==0){
            return 0;
        }
    }
    return 0;
}

void dir(){
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
       fprintf(stdout,cwd);
   }else{
       fprintf(stderr,"getcwd() error \n");
   }
}
void cd(){}
void clr(){}
void echo(char *string){
    printf(stdout, string);
}
void ps(){
char pause[4];
        printf(stdout,"Press Enter to continue");
        fgets( pause, 256, stdin );
}
void help(){
    printf(stdout,"Manual\n");
    printf(stdout,"cd: Changes the current directory\n");
    printf(stdout,"clr: Clears the Screen\n");
    printf(stdout,"dir: Lists the contents of directory\n");
    printf(stdout,"environ: Lists all the environment strings\n");
    printf(stdout,"echo: Displaying what is input on screen\n");
    printf(stdout,"help: Displayes this user manual\n");
    printf(stdout,"ps: Pauses operation of shell until 'Enter' is pressed.\n");
    printf(stdout,"quit: Quits the shell");

    fgets( help, 256, stdin );
}



