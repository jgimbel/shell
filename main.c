#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void cd(char *path);
void dir();
void clr();
void environ(); //TODO
void echo(char *string);
void help();
void ps();
void ls();

int main(void)
{
    dir();
    while(1){
        char program[256];
        gets(program);
        char *line = strtok(program, " ");
        if(strcmp(line,"cd")==0){
            cd(program);
        }else if(strcmp(line,"dir")==0){
            ls();
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
        dir();
    }
    return 0;
}

void dir(){
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
       fprintf(stdout,"%s$",cwd);
   }else{
       fprintf(stderr,"getcwd() error \n");
   }
}
void ls(){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}

void cd(char *path){
    path = strtok(NULL, " ");
    if(path[0] == '/'){
        fprintf(stdout,"changing from root");
        chdir(path);
    } else {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL){
            char p[strlen(path)+1];
            strcat(p,path);
            strcat(cwd,p);
            chdir(path);
        }
    }
}

void clr(){
    printf("\033[2J\033[1;1H");
}

void echo(char *string){
    string = strtok(NULL, " ");
    while(string != NULL){
        fprintf(stdout,"%s ", string);
        string = strtok(NULL, " ");
    }
    fprintf(stdout, "\n");
}
void ps(){
char pause[4];
        fprintf(stdout,"Press Enter to continue\n");
        fgets( pause, 256, stdin );
}
void help(){
    fprintf(stdout,"Manual\n");
    fprintf(stdout,"cd: Changes the current directory\n");
    fprintf(stdout,"clr: Clears the Screen\n");
    fprintf(stdout,"dir: Lists the contents of directory\n");
    fprintf(stdout,"environ: Lists all the environment strings\n");
    fprintf(stdout,"echo: Displaying what is input on screen\n");
    fprintf(stdout,"help: Displayes this user manual\n");
    fprintf(stdout,"ps: Pauses operation of shell until 'Enter' is pressed.\n");
    fprintf(stdout,"quit: Quits the shell");

    fgets( help, 256, stdin );
}



