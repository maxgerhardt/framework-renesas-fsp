/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/**
 * @file sockets_wrapper.h
 * @brief FreeRTOS Sockets connect and disconnect function wrapper.
 */

#ifndef SOCKETS_WRAPPER_H
#define SOCKETS_WRAPPER_H

/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

/* Logging related header files are required to be included in the following order:
 * 1. Include the header file "logging_levels.h".
 * 2. Define LIBRARY_LOG_NAME and  LIBRARY_LOG_LEVEL.
 * 3. Include the header file "logging_stack.h".
 */

/* Include header that defines log levels. */
#include "logging_levels.h"

/* Logging configuration for the Sockets. */
#ifndef LIBRARY_LOG_NAME
 #define LIBRARY_LOG_NAME     "Sockets"
#endif
#ifndef LIBRARY_LOG_LEVEL
 #define LIBRARY_LOG_LEVEL    LOG_INFO
#endif

extern void vLoggingPrintf(const char * pcFormatString, ...);

#include "logging_stack.h"

/************ End of logging configuration ****************/

#define SOCKETS_ERROR_NONE        (0)    /*!< No error. */
#define SOCKETS_SOCKET_ERROR      (-1)   /*!< Catch-all sockets error code. */
#define SOCKETS_ENOMEM            (-12)  /*!< Memory allocation failed. */
#define SOCKETS_ENOSOCKETS        (-13)  /*!< Max number of sockets has been used. */
#define SOCKETS_EINVAL            (-22)  /*!< Invalid argument. */
#define SOCKETS_EDNS              (-200) /*!< DNS lookup failed. */

#define SOCKETS_INVALID_SOCKET    ((Socket_t) ~0U)

struct xSOCKET;
typedef struct xSOCKET * Socket_t;     /**< @brief Socket handle data type. */

/**
 * @brief Establish a connection to server.
 *
 * @param[out] pTcpSocket The output parameter to return the created socket descriptor.
 * @param[in] pHostName Server hostname to connect to.
 * @param[in] port Server port to connect to.
 * @param[in] receiveTimeoutMs Timeout (in milliseconds) for transport receive.
 * @param[in] sendTimeoutMs Timeout (in milliseconds) for transport send.
 *
 * @note A timeout of 0 means infinite timeout.
 *
 * @return Non-zero value on error, 0 on success.
 */
BaseType_t Sockets_Connect(Socket_t   * pTcpSocket,
                           const char * pHostName,
                           uint16_t     port,
                           uint32_t     receiveTimeoutMs,
                           uint32_t     sendTimeoutMs);

/**
 * @brief End connection to server.
 *
 * @param[in] xSocket The socket descriptor.
 */
void Sockets_Disconnect(Socket_t xSocket);

/**
 * @brief Transmit data to the remote socket.
 *
 * The socket must have already been created using a call to Sockets_Connect().
 *
 * @param[in] xSocket The handle of the sending socket.
 * @param[in] pvBuffer The buffer containing the data to be sent.
 * @param[in] xDataLength The length of the data to be sent.
 *
 * @return
 * * On success, the number of bytes actually sent is returned.
 * * If an error occurred, a negative value is returned.
 */
int32_t Sockets_Send(Socket_t xSocket, const void * pvBuffer, size_t xDataLength);

/**
 * @brief Receive data from a TCP socket.
 *
 * The socket must have already been created using a call to Sockets_Connect().
 *
 * @param[in] xSocket The handle of the socket from which data is being received.
 * @param[out] pvBuffer The buffer into which the received data will be placed.
 * @param[in] xBufferLength The maximum number of bytes which can be received.
 * pvBuffer must be at least xBufferLength bytes long.
 *
 * @return
 * * If the receive was successful then the number of bytes received (placed in the
 *   buffer pointed to by pvBuffer) is returned.
 * * If a timeout occurred before data could be received then 0 is returned.
 * * If an error occurred, a negative value is returned.
 */
int32_t Sockets_Recv(Socket_t xSocket, void * pvBuffer, size_t xBufferLength);

#endif                                 /* ifndef SOCKETS_WRAPPER_H */
