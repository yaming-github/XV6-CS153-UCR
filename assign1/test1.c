#include "types.h"
#include "user.h"

#define WNOHANG    1

int main(){
int pid;
int child_pid;
int status;
if((pid = fork()) == 0){
//This is child process.
printf(1, "I am child process %d, I will exit in status 123\n", getpid());
exit(123);
}
else{
//This is parent process.
child_pid = wait(&status);
printf(1, "I am parent process, I haved reaped my child process %d, which exited in status %d, using wait(int* status).\n", child_pid, status);
if((pid = fork()) == 0){
//This is child process.
printf(1, "I am child process %d, I will exit in status 456\n", getpid());
exit(456);
}
else{
//This is Parent process.
waitpid(pid, &status, 0);
printf(1, "I am parent process, I haved reaped my child process %d, which exited in status %d, using waitpid(int pid, int *status, int options).\n", pid, status);
if((pid = fork()) == 0){
printf(1, "I am child process %d, I will exit in status 789. I will sleep in next 5 second...\n", getpid());
sleep(5);
exit(789);
}
else do{
if((child_pid = waitpid(pid, &status, WNOHANG)) == 0){
printf(1, "I am parent process. My child is still running.\n");
sleep(1);
}
else{
printf(1, "I am parent process, I haved reaped my child process %d, which exited in status %d, using option WNOHANG.\n", pid, status); 
exit(0);
}
}while(child_pid == 0);
}
}
return 0;
}
