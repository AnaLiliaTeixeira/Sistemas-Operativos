#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process.h"


int launch_restaurant(int restaurant_id, struct communication_buffers* buffers, struct main_data* data) {
    
    pid_t pid;

    pid = fork();

    if (pid == -1){
        perror("Fodasse");
        exit(1);
    }

    if (pid == 0) {
        execute_restaurant(restaurant_id, buffers, data);
    }
    else {
        wait(NULL);
        exit(pid);
    }
}

int launch_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {

    pid_t pid;

    pid = fork();

    if (pid == -1){
        perror("Fodasse");
        exit(1);
    }

    if (pid == 0) {
        execute_driver(driver_id, buffers, data);
    }
    else {
        wait(NULL);
        exit(pid);
    }
}

int launch_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {

    pid_t pid;

    pid = fork();

    if (pid == -1){
        perror("Fodasse");
        exit(1);
    }

    if (pid == 0) {
        execute_client(client_id, buffers, data);
    }
    else {
        wait(NULL);
        exit(pid);
    }
}

int wait_process (int process_id) {

    int result;
    waitpid(process_id, WIFEXITED(result), WNOHANG);
    return WEXITSTATUS (result);
}


/*
int launch_restaurant(int restaurant_id, struct communication_buffers* buffers, struct main_data* data) {

    launch(execute_restaurant(restaurant_id, buffers, data), "Error on launch_restaurant");
}

int launch_driver(int driver_id, struct communication_buffers* buffers, struct main_data* data) {

    launch(execute_driver(driver_id, buffers, data), "Error on launch_driver");
}

int launch_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {

    launch(execute_client(client_id, buffers, data), "Error on launch_client");
}

int launch(int method(int id, struct communication_buffers* buffers, struct main_data* data), char messageError []) {
    
    int pid;

    pid = fork();

    if (pid == -1){
        perror(messageError);
        exit(1);
    }

    if (pid == 0) {
        method;
    }
    else {
        wait(NULL);
        exit(pid);
    }
}*/
