#include<stdbool.h>
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
char input_string[1000]; char Args_list[100][1000];
	char cwd[1024]; char history[1000][1000];
	int his_pos=0; int i; 
void start_shell(){
	printf("\n_________________Wilkommenn to V-SHELL__________________________________\n");

	char* user= getenv("USER");
	
	printf("\n@%s\n\n",user);
}

bool takeInput(){
	//char* input;
	printf(">>>"); //Prompt
	scanf("%[^\n]%*c",input_string);
	if(strlen(input_string)!=0){
		//printf("Hello\n");
		strcpy(history[his_pos],input_string);
		his_pos++;
		return 1;
	}
	else{
		return 0;
	}
}

void parseWords() 
{
     i=0; 
  
    char* tok; 
  
    tok = strtok(input_string," "); 
  
    while (tok != 0) { 
        //printf("%s\n", tok); 
        strcpy(Args_list[i],tok);
        // Use of strtok 
        // go through other tokens 
        tok = strtok(0," ");
        i++; 
    } 
    strcpy(Args_list[i],"NULL"); 
}


void execArgs() 
{ 
	// for(int x=i; x<100; x++){
	// 		Args_list[x][0]='\0';
	// 	}
	// 	printf("Paresdd[2] %s\n",Args_list[1]);

		//char *argv[13] = {Args_list[0],Args_list[1],Args_list[2],Args_list[3],Args_list[4],Args_list[5],Args_list[6],Args_list[7],Args_list[8],Args_list[9],Args_list[10],Args_list[11],NULL};
		//argv[0]=Args_list[0];
		
    // Forking a child 
    char *argv[4];
    if(strcmp(Args_list[2],"NULL")==0){
    	argv[0]=Args_list[0];
    	argv[1]=Args_list[1];
    	argv[2]=NULL;
    	argv[3]=NULL;
    }
    else{
    	argv[0]=Args_list[0];
    	argv[1]=Args_list[1];
    	argv[2]=Args_list[2];
    	argv[3]=NULL;
    }

    if(strcmp(Args_list[1],"NULL")==0 || strcmp(Args_list[1],"-")==0){
    	argv[1]=NULL;
    }

		//printf("%s\n",argv[0]);
    int pid = fork();  
  	//printf("PID %d\n",pid);
 	if(pid==0){
 		//char * loc = "/bin/";
 		//strcat(loc,argv[0]);
 		//strcpy(argv[0],loc);
 		execvp(argv[0],argv);
 		//printf("Heeek");
 	}
 	else{
 		wait(0);
 	}

} 

void main(){
	start_shell();

	//int a=takeInput();
	//printf("%d\n",a);

	while(1){
		getcwd(cwd,sizeof(cwd));
		printf("You are working @ %s",cwd);
		takeInput();
		parseWords();

		if(strcmp(Args_list[0],"exit")==0){		// exit
			printf("Hasta Luego , Have a Good Day! \n");
			exit(0);
			return;
				//flag++;
		}
		else if(strcmp(Args_list[0],"history")==0){		// history
			for(int x=0; x<his_pos; x++)
				printf("%s\n",history[x]);
				//flag++;
		}
		else if(strcmp(Args_list[0],"pwd")==0){		// pwd
			getcwd(cwd,sizeof(cwd));
			printf("The current working directory is : %s",cwd);
			printf("\n");
			//flag++;
		}
		else if(strcmp(Args_list[0],"cd")==0){		// cd
			chdir(Args_list[1]);
			getcwd(cwd,sizeof(cwd));
			printf("You have changed your current directory to %s",cwd);
			printf("\n");
		}
		else if(strcmp(Args_list[0],"echo")==0){		// echo
			if(strcmp(Args_list[1],"-n")==0){
				for(int x=2; x<i; x++){
					if(strcmp(Args_list[x],"\"")==0)
						continue;
					for(int y=0; y<strlen(Args_list[x]); y++){
						if(Args_list[x][y]==34)
							continue;
						printf("%c",Args_list[x][y]);
					}
				
				}
			//printf("\n");
			}
			else{
				for(int x=1; x<i; x++){
					if(strcmp(Args_list[x],"\"")==0)
						continue;
	
					for(int y=0; y<strlen(Args_list[x]); y++){
						if(Args_list[x][y]==34)
							continue;
						printf("%c",Args_list[x][y]);
					}
				
				}
				printf("\n");
			}
		}
		else if(strcmp(Args_list[0],"ls")==0){
			char a[100];
			a[0]='-';
			int p=1;
			for(int i=1;i<15;i++){
				if(strcmp(Args_list[i],"NULL")==0){
					break;
				}
				for(int j=0;j<strlen(Args_list[i]);j++){
					if(Args_list[i][j]!='-'){
						a[p]=Args_list[i][j];
						p++;
					}
				}
			}
			printf("%s\n",a);
			strcpy(Args_list[1],a);
			//printf("%s\n",Args_list[2]);
			execArgs();
			memset(a, 0, sizeof a);
		}
		 else if(strcmp(Args_list[0],"cat")==0){

		 execArgs();	

		 }
		else{
			//printf("Enter in else\n");
			execArgs();
		}

		memset(Args_list, 0, sizeof Args_list);
	}
}