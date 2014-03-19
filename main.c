#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <assert.h>

char path[256];
_IO_FILE *out;
void run(char *line);
void cd(char *path);
void dir();
void clr();
void env();
void echo(char *string);
void help();
void ps();
void ls();
void noChange();
void readFile(char *f);
void io(char *arg1,char *arg2,char *out,char *in);
void init();
int main(int argc, char *argv[]){

    init();
    switch(argc){
        case 1:
            noChange();
            break;
        case 2:
            readFile(argv[1]);
            break;
        default:
            fprintf(stdout, "Incorrect amount of parametters");
            break;
    }

    return 0;
}
char** str_split(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

//take command line input from a file
void readFile(char *f){
    char *args[50];
    char string[1000];
    FILE *file = fopen(f,"r");
    while(fgets(string,1000, file)!=NULL){
        char *ptr;
        if( (ptr = strchr(string, '\n')) != NULL)
            *ptr = '\0';
	    run(string);

    }
    fclose(file);
}

char* changeStreams(char *program){
    char inFile[1000];
    char** words = str_split(program,' ');
    int toReturn=0;
    int x=0;
    while(words[x]!=NULL){
        if(strcmp(words[x],">")==0){
            fclose(stdout);
            stdout=fopen(words[x+1],"w+");
        }
        if(strcmp(words[x],">>")==0){
            fclose(stdout);
            stdout=fopen(words[x+1],"a");
        }
        // if(strcmp(words[x],"<")==0){
        //     strcat(inFile,words[0]);
        //     FILE *file = fopen(words[x+1],"r");
        //     char string[1000];
        //     while(fgets(string,1000, file)!=NULL){
        //         char *ptr;
        //         if( (ptr = strchr(string, '\n')) != NULL)
        //             *ptr = '\0';
        //         strcat(inFile," ");
        // 	    strcat(inFile,string);
        //     }
        //      toReturn=1;
        // }
        x++;
    }
    if(toReturn){
        return inFile;
    }else{
        return NULL;
    }

}

void resetStream(){
    if(stdout!=out){
        fclose(stdout);
        stdout=out;
    }
}

void noChange(){
    dir();
    while(1){

        char program[256];
        gets(program);
        char *input = changeStreams(program);
        char *line;
        if(input){
            line = strtok(input, " ");
        }else {
            line = strtok(program, " ");
        }


        run(line);
        resetStream();
        dir();
    }
}

void run(char *line){
    if(strcmp(line,"cd")==0){
        cd(line);
    }else if(strcmp(line,"dir")==0){
        ls();
    }else if(strcmp(line,"clr")==0){
        clr();
    }else if(strcmp(line,"env")==0){
        env();
    }else if(strcmp(line,"echo")==0){
        echo(line);
    }else if(strcmp(line,"help")==0){
        help();
    }else if(strcmp(line,"pause")==0){
        ps();
    }else if(strcmp(line,"quit")==0){
        exit(1);
    }else{

        char *args[20];
        int x = 0;
        int y = 20;
        while (line != NULL) {
           if (x == y) {
                y = y * 2;
                x=y;
                *args = (char *)realloc(*args, y);
           }
           args[x] = line;
           x++;
           line = strtok(NULL, " ");
        }
        args[x] = (char *)0;
        pid_t pID = fork();
        char * myPath = malloc(snprintf(NULL, 0, "%s %s", "parent=", getenv("shell")) + 1);
        //char *env[] = { "PATH=/usr/bin:/bin:/opt/bin", (char *) 0 };
        char *envp[] = { myPath, (char *) 0};
        if(pID == 0) {
            //execv(envargs[0], envargs);
            int execReturn = execve(args[0], args, envp);
            if (execReturn == -1){
                printf("execv has failed.");
                exit(0);
            }
        }else if(pID < 0){
            printf("\nFailed to fork.");
        }else{}
    }
}

void init(){
    out=stdout;
    char *pathname;
    char *name= "shell";
    if (getcwd(path, sizeof(path)) != NULL) {
        pathname = malloc(strlen(name)+strlen(path)+1);
        sprintf(pathname, "%s=%s", name, path);
        putenv(pathname);
    }
}
//Displays current directory contents
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
            fprintf(stdout,"%s\n", dir->d_name);
        }
        closedir(d);
    }
}

// changes directory to the current working directory
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
    getcwd(path, sizeof(path));
}

//clears screen
void clr(){
    printf("\033[2J\033[1;1H");
}
//displays what has just been typed out
void echo(char *string){
    string = strtok(NULL, " ");
    while(string != NULL){
        fprintf(stdout,"%s ", string);
        string = strtok(NULL, " ");
    }
    fprintf(stdout, "\n");
}

//Pause function
void ps(){
    char pause[256];
    fprintf(stdout,"Press Enter to continue\n");
    gets(pause);
}

//Shell manual
void help(){
    fprintf(stdout,"**********************Manual*******************\n");
    fprintf(stdout,"cd: Changes the current directory\n");
    fprintf(stdout,"clr: Clears the Screen\n");
    fprintf(stdout,"dir: Lists the contents of directory\n");
    fprintf(stdout,"env: Lists all the environment strings\n");
    fprintf(stdout,"echo: Displaying what is input on screen\n");
    fprintf(stdout,"help: Displayes this user manual\n");
    fprintf(stdout,"ps: Pauses operation of shell until 'Enter' is pressed\n");
    fprintf(stdout,"quit: Quits the shell\n");
}

void env(){

    extern char **environ;
    int x = 0;
    while (environ[x]){
        fprintf(stdout, "%s\n", environ[x++]);
    }
}
