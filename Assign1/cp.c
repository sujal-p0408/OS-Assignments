#include<stdio.h> 
#include<string.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<fcntl.h> 
#include<unistd.h> 
 
int main(int argc, char* argv[]) { 
if(argc != 3) { 
printf("You can not enter more or less than 3 arguments."); 
return 0; 
} 
char* fn1; 
char* fn2; 
char line[50]; 
int fp1; 
int fp2; 
int n; 
fn1 = argv[1]; 
fn2 = argv[2]; 
fp1 = open(fn1, O_RDONLY); 
fp2 = open(fn2, O_WRONLY); 
while ((n = read(fp1, line, 50)) > 0) { 
write(fp2, line, n); 
} 
close(fp2); 
close(fp1); 
return 0; 
} 
 
  
