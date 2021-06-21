#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdint-gcc.h>

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
#endif // CHANNEL_H
