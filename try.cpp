#include<bits/stdc++.h>
#include<sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_ARGS 100
using namespace std;

enum TYPE {PIPE, IN, OUT, NORMAL};

TYPE parse(string& cmd_line, string argv[], string cmd_left[], string cmd_right[]){
	string tmp = cmd_line;
	TYPE type = NORMAL;
	int cnt=0, sep=-1, argc=0;
	
	while(tmp.find(" ") != string::npos ){
		int found = tmp.find(" ");
		argv[cnt] = tmp.substr(0, found);
		
		if(argv[cnt]=="|"){
			type = PIPE;
			sep = cnt;
		} 
		else if(argv[cnt]==">"){
			type = OUT;
			sep = cnt;
		}
		else if(argv[cnt]=="<"){
			type = IN; 
			sep = cnt;
		} 
		
		cnt++;
		tmp = tmp.substr(found+1);
		argc++;
	}
	
	argv[cnt] = tmp;
	argc++;
	
	int remains=0;
	
	for(int i=0;i<sep;i++){
		cmd_left[i]=argv[i];
	}
	cmd_left[sep] = "\0";
	for(int i=sep+1;i<argc;i++){
		cmd_right[remains++]=argv[i];
	}
	cmd_right[remains] = "\0";
	
	cout<<type;
	
	return type;
}

void execute(int argc, string pre_argv[]){
	pid_t pid;
	const char* amp;
	amp = "&";
	bool found_amp = false;
	
	char *argv[MAX_ARGS];
	for(int i=0;i<argc;i++){
		argv[i] = strdup(pre_argv[i].c_str());
	}
	
	if(argv[argc-1]==amp) found_amp = true;
	
	pid = fork();
	
	if(pid<0)
		perror("Error");
	else if(pid == 0){
		if(found_amp){
			argv[argc-1] = "\0";
			argc--;
		}
		execvp(argv[0],argv);
		perror("execvp error");
	}
	else if(!found_amp)
		waitpid(pid,NULL,0);
}

int main(){
	string cmd_line, argv[MAX_ARGS], cmd_left[MAX_ARGS], cmd_right[MAX_ARGS];
	while(true){
		cout<<">";
		getline(cin,cmd_line);
		TYPE type = parse(cmd_line, argv, cmd_left,cmd_right);
		
		switch (type){
			case PIPE:
			
				break;
			case IN: case OUT:
			
				break;
			default:
		}
		
		
	}
	
    return 0;
}

