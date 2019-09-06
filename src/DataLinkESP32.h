//author: chenliang @ Youtu Lab, Tencent
#ifndef YT_DATALINKESP32_H
#define YT_DATALINKESP32_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <pthread.h>
#include "driver/uart.h"

#include "DataLink.h"
#include "IDataLinkObserver.h"
#include <vector>
#include <queue>
#include <memory>
#include <string>

#include "YtMsg.pb.h"

using namespace std;


class YtSerialPortESP32 : public YtSerialPortBase
{
protected:
    uart_port_t mUart;
    QueueHandle_t mUartQueue;
public:
    YtSerialPortESP32(const char *dev);
    virtual ~YtSerialPortESP32();
    virtual bool isOpen();
    virtual int open();
    virtual int close();
    virtual int read(void *buffer, size_t len);
    virtual int write(void *buffer, size_t len);
};

class YtDataLinkESP32 : public YtDataLink
{
public:
    virtual ~YtDataLinkESP32();
    YtDataLinkESP32(const char *dev);
protected:
};

#endif
