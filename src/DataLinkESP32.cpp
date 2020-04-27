//author: chenliang @ Youtu Lab, Tencent

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory>

#include <pb_encode.h>
#include <pb_decode.h>
#include "YtMsg.pb.h"

#include "DataLink.h"
#include "DataLinkESP32.h"
#include "IDataLinkObserver.h"



YtDataLinkESP32::YtDataLinkESP32(const char *dev) : YtDataLink(new YtSerialPortESP32(dev))
{
}
YtDataLinkESP32::~YtDataLinkESP32()
{
}

// void *YtDataLinkESP32::run()
// {
// #ifdef __rtems__
//     rtems_object_set_name(pthread_self(), "YtDataLinkPull"); //for moviDebug
// #endif
// #ifndef INC_FREERTOS_H
//     pthread_setname_np(pthread_self(), "YtDataLinkPull"); //for rtems ps
// #endif
//
//     while (!shouldExit)
//     {
//         YtMsg *msg = recvRunOnce();
//         if (msg)
//         {
//             std::shared_ptr<YtMsg> message(msg, [](YtMsg *p) { /*printf("[YtDataLink] release %p\n", p);*/ pb_release(YtMsg_fields, p); delete p; });
//             Notify(instanceId, message);
//
//             if (message->which_values == YtMsg_rpc_tag)
//             {
//                 LOG_D("[YtDataLink] - YtMsg (%d)\n", message->values.rpc.func);
//                 if (message->values.rpc.which_params == YtRpc_cameraExposureParams_tag)
//                 {
//                     LOG_D("[YtDataLink] | CameraExposureParams type is %d!\n", (int)message->values.rpc.params.cameraExposureParams.type);
//                 }
//             }
//         }
//     }
//     return NULL;
// }
//






YtSerialPortESP32::YtSerialPortESP32(const char *dev) : YtSerialPortBase(dev), mUart((uart_port_t)(dev[0]-'0'))
{
}
YtSerialPortESP32::~YtSerialPortESP32()
{
}

bool YtSerialPortESP32::isOpen()
{
    //TODO: USB断开后处理
    return mPortFd >= 0;
}
int YtSerialPortESP32::open()
{
    mPortFd = (int)mUart;

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(mUart, &uart_config));
    // Set UART pins(TX: IO17 (UART2 default), RX: IO16 (UART2 default), RTS: IO18, CTS: IO19)
    int modifyTx = GPIO_NUM_17;
    int modifyRx = GPIO_NUM_16;
    if (mDev[0] == '2' && mDev[1] == '~')
    {
        modifyTx = GPIO_NUM_16;
        modifyRx = GPIO_NUM_17;
    }
    ESP_ERROR_CHECK(uart_set_pin(mUart, modifyTx, modifyRx, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (100 * 2);
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(mUart, uart_buffer_size, uart_buffer_size, 2, &mUartQueue, 0));

    LOG_D("[YtDataLink] opened: %d\n", mPortFd);
    return 1;
}
int YtSerialPortESP32::close()
{
    if (mPortFd != 0)
    {
        mPortFd = -1;
        return 1;
    }
    return 0;
}
int YtSerialPortESP32::read(void *buffer, size_t len)
{
    int rv;
    if (!isOpen())
    {
        open();
    }
    rv = uart_read_bytes(mUart, (uint8_t *)buffer, len, 1);
    return rv;
}
int YtSerialPortESP32::write(void *buffer, size_t len)
{
    int ret = 0;
    if (!isOpen())
    {
        open();
    }
    ret = uart_write_bytes(mUart, (const char*)buffer, len);
    return ret;
}
