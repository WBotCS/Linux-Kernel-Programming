#include "userapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>

// Function to calculate the length of a string
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Function to copy a string
void my_strcpy(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
// Function to convert an integer to a string
void itoa(int num, char *str) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Negative numbers are handled only with base 10, unsigned otherwise.
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % 10;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / 10;
    }

    // If number is negative, append '-'
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Null-terminate string

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void register_process(unsigned int pid) {
    int fd = open("/proc/kmlab/status", O_WRONLY);
    if (fd == -1) {
        perror("Error opening /proc/kmlab/status");
        exit(1);
    }
    char buf[16];
    itoa(pid, buf);
    write(fd, buf, my_strlen(buf));
    close(fd);
}

void write_to_stdout(const char *str) {
    write(STDOUT_FILENO, str, my_strlen(str));
}

void execute_command(const char *cmd) {
    pid_t pid = fork();
    if (pid == -1) {
        // Fork failed
        write_to_stdout("Fork failed\n");
        return;
    }

    if (pid == 0) {
        // Child process
        char *arguments[] = {"/bin/sh", "-c", NULL, NULL};

        // Allocate memory for the command
        arguments[2] = (char *)malloc(my_strlen(cmd) + 1);
        if (arguments[2] == NULL) {
            _exit(1); // Memory allocation failed
        }
        my_strcpy(arguments[2], cmd);

        execv("/bin/sh", arguments);
        // Exec should not return, if it does, it's an error
        _exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for child process to finish
    }
}


int main(int argc, char* argv[]) {
    const int expire = 10;
    time_t start_time = time(NULL);

    register_process(getpid());

    // Loop for a specified duration
    while ((int)(time(NULL) - start_time) <= expire) {
        // Allocate and deallocate memory
        int *data = malloc(10000);
        free(data);
    }

    // Open and read from "kmlab_test.sh"
    int fd;
    ssize_t bytes_read;
    char buffer[1024]; // Adjust buffer size as needed

    fd = open("kmlab_test.sh", O_RDONLY);
    if (fd == -1) {
        write_to_stdout("Error opening kmlab_test.sh\n");
        _exit(1);
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    close(fd);

    // Print PIDs and times using a system call
    write_to_stdout("Registered PIDs and times:\n");
    execute_command("cat /proc/kmlab/status");

    return 0;
}

//old func that uses clib

// Register process
//void register_process(unsigned int pid) {
//
//  int fd = open("/proc/kmlab/status", O_WRONLY);
//  if(fd == -1) {
//      perror("Error opening /proc/kmlab/status");
//      exit(1);
//  }
//  char buf[16];
//  sprintf(buf, "%d", pid);
//  write(fd, buf, strlen(buf));
//  close(fd);
//}
//
//void write_to_stdout(const char *str) {
//    write(STDOUT_FILENO, str, strlen(str));
//}
//void execute_command(const char *cmd) {
//    pid_t pid = fork();
//    if (pid == -1) {
//        // Fork failed
//        write_to_stdout("Fork failed\n");
//        return;
//    }
//
//    if (pid == 0) {
//        // Child process
//        char *const arguments[] = {"/bin/sh", "-c", cmd, NULL};
//        execv("/bin/sh", arguments);
//        // Exec should not return, if it does, it's an error
//        _exit(1);
//    } else {
//        // Parent process
//        wait(NULL); // Wait for child process to finish
//    }
//}
//int main(int argc, char* argv[]) {
//    int fd;
//    ssize_t bytes_read;
//    char buffer[1024]; // Adjust buffer size as needed
//
//    register_process(getpid());
//
//    // Read from "kmlab_test.sh" without using the standard C library
//    fd = open("kmlab_test.sh", O_RDONLY);
//    if (fd == -1) {
//        write_to_stdout("Error opening kmlab_test.sh\n");
//        _exit(1);
//    }
//
//    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
//        write(STDOUT_FILENO, buffer, bytes_read);
//    }
//
//    close(fd);
//
//    // Print PIDs and times without using standard C library
//    write_to_stdout("Registered PIDs and times:\n");
//    execute_command("cat /proc/kmlab/status");
//
//    return 0;
//}

