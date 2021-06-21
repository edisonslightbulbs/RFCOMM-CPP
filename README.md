#### Usage of this tiny bluez CPP helper library 👏🍻🍻

*   the channel interface
```cpp
namespace channel {

/**
 * channel.h
 *   Establishes RFCOMM (TX) channel associated with
 *   a given UUID and MAC address.
 *
 *   @ref
 *     https://people.csail.mit.edu/albert/bluez-intro/x604.html
 *
 *   accessed
 *     18 June 2021
 */
int queryID(uint8_t* uuid, char *deviceAddress);
}

```
*   the client interface
```cpp
namespace client {

/**
 * callServer
 *   Calls a remote server over a RFCOMM (TX) channel.
 *
 *   @ref
 *     https://people.csail.mit.edu/albert/bluez-intro/x502.html
 *
 *   accessed
 *     05:22 18 June 2021
 */
void callServer(int channel, char *deviceAddress);
}

```
*  the server inteface  

```cpp
namespace server {

/**
 * setup
 *   Uses host machine as a local server: opens an RFCOMM (RX) channel
 *   for a specified number of connections.
 *
 *   @ref
 *     https://people.csail.mit.edu/albert/bluez-intro/x502.html
 *
 *   accessed
 *     05:22 18 June 2021
 */
void setup(int channelID, int connectionCount);
}

```

here's an example of how to use the interfaces

```cpp

// RFCOMM connection between Linux system and Android device.
//
#include <thread>

#include "channel.h"
#include "client.h"
#include "server.h"

// configure setup
//
#define SETUP_CLIENT 1 // use host machine as a client
#define SETUP_SERVER 0 // use host machine as a server

void setupClient(uint8_t *uuid, char *deviceAddress)
{
#if SETUP_CLIENT == 1
    int clientChannel = channel::queryID(uuid, deviceAddress);
    client::callServer(clientChannel, deviceAddress);
#endif
}

void setupServer(int channelID, int connectionCount)
{
#if SETUP_SERVER == 1
    server::setup(channelID, connectionCount);
#endif
}


int main()
{
    /** client config */
    // UUID: d8308c4e-9469-4051-8adc-7a2663e415e2
    //  n.b. make sure UUID on the android device is the same as this one.
    uint8_t CHANNEL_UUID[16] = { 0xd8, 0x30, 0x8c, 0x4e, 0x94, 0x69,
        0x40, 0x51, 0x8a, 0xdc, 0x7a, 0x26, 0x63, 0xe4, 0x15, 0xe2 };
    char deviceAddress[18] = "C0:8C:71:61:34:8C"; // <-- android address

    /** server config */
    const int CHANNEL_ID = 20;             // use channel 20 ...
    const int NUMBER_OF_CONNECTIONS = 1;   // ... for a single connection

    std::thread clientWorker(setupClient, CHANNEL_UUID, deviceAddress);
    std::thread serverWorker(setupServer, CHANNEL_ID, NUMBER_OF_CONNECTIONS);

    clientWorker.join();
    serverWorker.join();
    return 0;
}

```
