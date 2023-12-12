#include <stdint.h>
#include <jack/jack.h>
#include <jack/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    jack_status_t status;

    uint64_t id = fork();
    id += fork();

    char client_name[128] = "";
    snprintf(client_name, 127, "client_%lu", id);

    for (int i = 0; i < 1000; i++) {
        jack_client_t* client = jack_client_open(client_name, JackNullOption, &status);
        jack_client_close(client);

        if (status) {
            printf("Got jack status %d on try i:%d\n", status, i);
            return 0;
        }
    }

    return 0;
}
