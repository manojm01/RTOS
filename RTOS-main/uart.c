
#include  	"config.h"

#if  UART0_EN

#if UART_INTERRUPT_FLAG
/*****************************************************************************
** UART0Handler
**
** UART0
** 
*****************************************************************************/
void Uart0_Exception(void)
{
    uint8 IIRValue, LSRValue;
    uint8 Dummy;
	OS_ENTER_CRITICAL();	        
    IIRValue = U0IIR;
    Dummy = U0RBR;		          	
	LSRValue = U0LSR; 
	VICVectAddr = 0; 
	OS_EXIT_CRITICAL();	
	     
	Dummy = Dummy;                      	   
    IIRValue >>= 1;			
    IIRValue &= 0x07;			
    if ( IIRValue == IIR_RLS )		
    {
	
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
		UART0_SendData("Help~~~");
		return;
	}
	if ( LSRValue & LSR_RDR )				
	{
	   UART0_SendData("Thankyou for ~~~");	/*  write the code yourself*/
	   return ;
	}
    }
    else if ( IIRValue == IIR_RDA )	
    {
	UART0_SendData("UART0...");
	return ;
    }
    else if ( IIRValue == IIR_CTI )	
    {
	/**/
    }
    else if ( IIRValue == IIR_THRE )	
    {
	if ( LSRValue & LSR_THRE )
	{
     /**/
	}
	else
	{
      /*  */
	}
    }
}

#endif

/****************************************************************************
* SendByte()
****************************************************************************/
void  SendByte0(uint8 data)
{  
	U0THR = data;                                //��������
	while((U0LSR & 0x40) == 0);                 // �ȴ����ݷ������
}

/****************************************************************************
* ReceiveByte()
****************************************************************************/
unsigned char  UART0_RecvByte(void)
{  
	while(!(U0LSR & 0x01)){OSTimeDly(2);};

	return (unsigned char)U0RBR ;	              
}

/****************************************************************************
* ���ƣ�ISendBuf()
* ���ܣ��������������ݷ��ͻ����������ȴ�������ϡ�
* ��ڲ���������ָ��
* ���ڲ�������
****************************************************************************/
void  UART0_SendData(char *str)
{  
	while(1)
   {  
   		if( *str == '\0' ) break;
		SendByte0(*str++);	    			// ��������
   }   
}   

/****************************************************************************
* ���ƣ�UART0_Init()
* ���ܣ���ʼ������0,�����乤��ģʽ�������ʡ�
* ��ڲ�����
****************************************************************************/
void UART0_Init(void)
{  

/*��������ͨ��ѡ��*/ 
	PINSEL0 |= 0x00000005;


/* ���ô��ڲ������ڱ�׼��48M��Ƶ��1/2VBP�£�*/
    U0LCR = 0x83;                    //DLABλ��1,8λ����λ,1λֹͣλ,����żУ��
#if Baud0==19600						 //���ò�����Ϊ19600 ��0��6��
    U0DLM=0;
	U0DLL=38;
#endif
									
#if Baud0==57600        				  //57600  error:0.16%
    U0DLM=0;						  
	U0DLL=13;
#endif

#if Baud0==115200        				  //57600  error:0.16%
    U0DLM=0;						  
	U0DLL=13;
#endif
	U0LCR = 0x03; 					 //DLAB
    U0FCR = 0x07;		


#if UART_INTERRUPT_FLAG  
    U0IER = IER_RBR | IER_THRE | IER_RLS;	
#endif

}


#endif




#if  UART1_EN



#if UART_INTERRUPT_FLAG

/*****************************************************************************
** UART1Handler
**
** 
** 
*****************************************************************************/
void Uart1_Exception (void)
{
    uint8 IIRValue, LSRValue;
    uint8 Dummy;
	OS_ENTER_CRITICAL();	       /*  */ 
    IIRValue = U1IIR; 
	LSRValue = U1LSR;
    Dummy = U1RBR;		          /* ��RBR�Ĵ�������ж� */
	OS_EXIT_CRITICAL();	   
	Dummy = Dummy;               /* ��ֹ���������� */       	   
    IIRValue >>= 1;			
    IIRValue &= 0x07;			/* �жϱ�ʶλ1��3 */
    if ( IIRValue == IIR_RLS )		/* ������״̬*/
    {

	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{ 
		UART0_SendData("Help~~~");
	    return;
	}
	if ( LSRValue & LSR_RDR )	/* ��������׼���� */			
	{
	    /* ����ڽ�������û�д���, ����׼����, �򱣴�����.��RBR������ж� */
	   UART0_SendData("Thankyou for ~~~");	/*  write the code yourself*/
	}
    }
    else if ( IIRValue == IIR_RDA )	/* �������ݿ��� */
    {
	UART0_SendData("UART1�жϣ���");
    }
    else if ( IIRValue == IIR_CTI )	/* �ַ���ʱ��ʾ */
    {
	/**/
    }
    else if ( IIRValue == IIR_THRE )	/* THRE, ���ͼĴ����� */
    {
	LSRValue = U0LSR;		/* ���LSR�Ĵ�����U0THR�����Ƿ���ȷ���� */
	if ( LSRValue & LSR_THRE )
	{
     /**/
	}
	else
	{
      /*  */
	}
    }
}

#endif

/****************************************************************************
* ���ƣ�SendByte()
* ���ܣ��򴮿ڷ����ֽ����ݡ�
* ��ڲ�����data--Ҫ���͵�����
* ���ڲ�������
****************************************************************************/
void  SendByte1(uint8 data)
{  
	U0THR = data;                                //��������
	while((U1LSR & 0x40) == 0);                 // �ȴ����ݷ������
}

/****************************************************************************
* ���ƣ�ISendBuf()
* ���ܣ��������������ݷ��ͻ����������ȴ�������ϡ�
* ��ڲ���������ָ��
* ���ڲ�������
****************************************************************************/
void  UART_SendData1(uint8 *str)
{  
	while(1)
   {  
   		if( *str == '\0' ) break;
		SendByte1(*str++);	    			// ��������
   }   
}   

/****************************************************************************
* ���ƣ�UART0_Init()
* ���ܣ���ʼ������0,�����乤��ģʽ�������ʡ�
* ��ڲ�����baud         ������
* ���ڲ�����
****************************************************************************/
void UART1_Init(void)
{  

/*��������ͨ��ѡ��*/ 
	PINSEL0 |= 0x00050000;


/* ���ô��ڲ������ڱ�׼��48M��Ƶ��1/2VBP�£�*/
    U1LCR = 0x83;                    //DLABλ��1,8λ����λ,1λֹͣλ,����żУ��
#if Baud1==19600						 //���ò�����Ϊ19600 ��0��6��
    U1DLM=0;
	U1DLL=76;
#endif
									
#if Baud1==57600        				  //���ò�����Ϊ57600  error:0.16%
    U1DLM=0;						  
	U1DLL=26;
#endif

#if Baud1==115200        				  //���ò�����Ϊ57600  error:0.16%
    U1DLM=0;						  
	U1DLL=13;
#endif
	U1LCR = 0x03; 					 //DLABλ�ָ�0,8λ����λ,1λֹͣλ,����żУ��
    U0FCR = 0x07;		/* ʹ�ܲ�����Rx��Tx����Ĵ��� */

#if UART_INTERRUPT_FLAG
    if ( install_irq( UART1_INT, (void *)UART1Handler ) == FALSE )
    {
	return (FALSE);
    }
   
    U0IER = IER_RBR | IER_THRE | IER_RLS;	/* ʹ���ж� */
	return (TURE);
#endif

}


#endif


/*********************************************************************************
**                            End Of File
*********************************************************************************/

