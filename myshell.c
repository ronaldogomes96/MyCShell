#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_NUMBER_OF_TOKENS 10

int readNewInstruction();
void extractTokens(char * fullString, int * tokensLen, char * tokens[]);
void executeCommand(char * tokens[]);

int main() {
	int status = 0;
	while(status == 0) {
		status = readNewInstruction();
	}

	return 0;
}

int readNewInstruction() {
	printf("$ ");
	char buffer[1024] = "";
	gets(buffer);

	unsigned long commandLenght = strlen(buffer);

	if (commandLenght != 0) {
		char * tokens[MAX_NUMBER_OF_TOKENS] = { "" };
		int numberOfTokens = 0;
		extractTokens(buffer, &numberOfTokens, tokens);
		executeCommand(tokens);

		return 0;
	} else {
		return -1;
	}
}

void extractTokens(char * fullString, int * tokensLen, char * tokens[]) {
	int numberOfTokens = 0;
	char * delimiter = " ";

	char * token = strtok(fullString, delimiter);
	while(token != NULL) {
		tokens[numberOfTokens] = token;
		numberOfTokens += 1;

		token = strtok(NULL, delimiter);
	}

	*tokensLen = numberOfTokens;
}

void executeCommand(char * tokens[]) {	
	pid_t pid;
	int status;
	char * path = "/bin/";
	char filePath[100];

	strcpy(filePath, path);
	strcat(filePath, tokens[0]);

	if(!(pid = fork())) {
		execvp(filePath, tokens);
		exit(10); 			
	}

	waitpid(pid,&status,WUNTRACED);
}
