#ifndef   __UART_h
#define   __UART_h 

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define BUFSIZE		0x10

//#if  UART0_EN
//#if UART_INTERRUPT_FLAG
/*****************************************************************************
** 函数名	：	UART0Handler
**
**  功能描述：  UART0中断处理
** 
*****************************************************************************/
extern void Uart0_Exception (void);

//#endif 
/****************************************************************************
* 名称：SendByte0()
* 功能：向串口发送字节数据。
* 入口参数：data--要发送的数据
* 出口参数：无
****************************************************************************/
extern void  SendByte0(uint8 data);

/****************************************************************************
* 名称：ISendBuf()
* 功能：将缓冲区的数据发送回主机，并等待发送完毕。
* 入口参数：无
* 出口参数：无
****************************************************************************/
extern void  UART0_SendData(char *str);

/****************************************************************************
* 名称：UART0_Init()
* 功能：初始化串口0,设置其工作模式及波特率。
* 入口参数：baud         波特率	
* 出口参数：返回值为1时表示初化成功，为0表示初始化失败
****************************************************************************/

unsigned char  UART0_RecvByte(void);

extern void UART0_Init(void);

//#endif
#if  UART1_EN

#if UART_INTERRUPT_FLAG
/*****************************************************************************
** 函数名	：	UART1Handler
**
**  功能描述：  UART1中断处理
** 
*****************************************************************************/
extern void UART1Handler (void) __irq;
#endif
/****************************************************************************
* 名称：SendByte0()
* 功能：向串口发送字节数据。
* 入口参数：data--要发送的数据
* 出口参数：无
****************************************************************************/
extern void  SendByte1(uint8 data);

/****************************************************************************
* 名称：ISendBuf()
* 功能：将缓冲区的数据发送回主机，并等待发送完毕。
* 入口参数：无
* 出口参数：无
****************************************************************************/
extern void  UART1_SendData(uint8 *str);

/****************************************************************************
* 名称：UART0_Init()
* 功能：初始化串口0,设置其工作模式及波特率。
* 入口参数：baud         波特率	
* 出口参数：返回值为1时表示初化成功，为0表示初始化失败
****************************************************************************/

extern void UART1_Init(void);

#endif
#endif

