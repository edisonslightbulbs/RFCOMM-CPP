#ifndef SERVER_H
#define SERVER_H

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
#endif // SERVER_H
