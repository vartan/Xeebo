#include "uart.h"
#include "lpc11uxx.h"
#include "message_handler.h"
#include "message_queue.h"


/*****************************************************************************
** Function name:       UART_IRQHandler
**
** Descriptions:        Receives messages one byte at a time through the UART
*                       interface. The first byte is the message id. Next,
*                       space is for the size of the message requested. Each
*                       byte of the message is filled with the following 
*                       characters received. Once the message is filled 
*                       completely, it is added to the message queue for 
*                       the main loop to handle.
**
** parameters:          None
** Returned value:      None
** 
*****************************************************************************/
void UART_IRQHandler(void)
{
    uint8_t IIRValue, LSRValue;
    uint8_t message_index = 0;
    struct message_type *currentHandler;
    currentHandler = NULL;
    uint8_t *message;


    // what the hell does shifting right do?? seems like it'd mess up the 
    // bit names
    IIRValue = LPC_USART->IIR;
    IIRValue >>= 1;         /* skip pending bit in IIR */
    IIRValue &= 0x07;           /* check bit 1~3, interrupt identification */
    if (IIRValue == IIR_RLS)        /* Receive Line Status */
    {
        LSRValue = LPC_USART->LSR;
        /* Receive Line Status */
        if (LSRValue & (LSR_OE | LSR_PE | LSR_FE | LSR_RXFE | LSR_BI))
        {
            /* There are errors or break interrupt */
            /* Read LSR will clear the interrupt */
            //UARTStatus = LSRValue;
            //Dummy = LPC_USART->RBR;   /* Dummy read on RX to clear 
            //                  interrupt, then bail out */
            //return;
        }
        if (LSRValue & LSR_RDR) /* Receive Data Ready */            
        {
            /* If no error on RLS, normal ready, save into the data buffer. */
            /* Note: read RBR will clear the interrupt */
            /*UARTBuffer[UARTCount++] = LPC_USART->RBR;
            if (UARTCount == BUFSIZE)
            {
                UARTCount = 0;      buffer overflow 
            }*/ 
        }
    }
    else if (IIRValue == IIR_RDA)   /* Receive Data Available */
    {
        if(currentHandler == NULL) {
            currentHandler = &message_handlers[LPC_USART->RBR];
            message = malloc(currentHandler->receiveLength * sizeof(uint8_t)); 
            message_index = 0;
        } else {
            message[message_index++] = LPC_USART->RBR;
            if(message_index == currentHandler->receiveLength) {
                message_queue_push(currentHandler, message);
            }
            currentHandler = NULL;
        }
        
        /* Receive Data Available */
        
        //UARTBuffer[UARTCount++] = LPC_USART->RBR;
        //if (UARTCount == BUFSIZE)
        //{
        //  UARTCount = 0;      /* buffer overflow */
        //}
    }
    else if (IIRValue == IIR_CTI)   /* Character timeout indicator */
    {
        /* Character Time-out indicator */
        //UARTStatus |= 0x100;      /* Bit 9 as the CTI error */
    }
    else if (IIRValue == IIR_THRE)  /* THRE, transmit holding register empty */
    {
        /*
        LSRValue = LPC_USART->LSR;      
        if (LSRValue & LSR_THRE)
        {
            UARTTxEmpty = 1;
        }
        else
        {
            UARTTxEmpty = 0;
        }*/
    }
    
    return;
}
