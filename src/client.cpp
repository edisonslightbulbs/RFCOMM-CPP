#include "client.h"
#include "definitions.hpp"

void client::callServer(int channel, char *deviceAddress) {
    // allocate a socket
    struct sockaddr_rc address = { 0 };
    int allocatedSocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    address.rc_family = AF_BLUETOOTH;
    address.rc_channel = channel;
    str2ba(deviceAddress, &address.rc_bdaddr);

    // connect to remote device
    int callStatus;
    long writeStatus;
    callStatus
        = connect(allocatedSocket, (struct sockaddr*)&address, sizeof(address));

    if (callStatus == 0) {
        BEGIN_DELAY_ENVIRONMENT
        writeStatus = write(allocatedSocket, "hello!", 6);
        printf("-- sent: \"hello!\" \n");
        END_DELAY_ENVIRONMENT
    } else {
        perror("-- failed to connect to remote device");
    }
    close(allocatedSocket);
}
