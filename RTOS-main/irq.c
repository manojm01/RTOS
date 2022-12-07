/*****************************************************************************
 *                       �жϷ����������
******************************************************************************/
#include "define.h"			

#if   INTERRPUT_EN
/******************************************************************************
** ������:		DefaultVICHandler
**
** ��������:		Ĭ�ϵ�VIC�жϴ������ڴ���α�ж�.
**				    ����жϷ�������VICaddress �Ĵ���, ��IRQ slot ��Ӧ�������������������ַ.
** ��ڲ���:		
** ���ڲ���:		
** 
******************************************************************************/
void DefaultVICHandler (void) __irq
{
    /*���IRQû��װ��VIC, ���жϲ���,���Ĭ�ϵ�VIC address ���ᱱʹ��. �⽫���������ѭ��. 
	�ڵ������������ѭ�����е��Ը���. */
    VICVectAddr = 0;
    while ( 1 );
}

/******************************************************************************
** ������   :		init_VIC
**
** ��������:	��ʼ��VIC interrupt ������.
** 
******************************************************************************/
void init_VIC(void) 
{
    uint8 i = 0;
    uint32 *vect_addr, *vect_cntl;
   	
    /* ��ʼ�� VIC*/
    VICIntEnClr = 0xffffffff;		 /*�������ж�*/
    VICVectAddr = 0;
    VICIntSelect = 0;

    /*���������ж�����Ϊ0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	*vect_addr = 0;	
	*vect_cntl = 0;
    }

    /* װ��Ĭ�ϵ��жϴ����ַ*/
    VICDefVectAddr = (uint32*)DefaultVICHandler;   
}

/******************************************************************************
** ������:		install_irq
**
** ��������:	װ���жϴ��������ĿΪ16, ��������32���жϹ���. ���Բ���ͬʱװ�����з���.
**				���ж�����Ĺ������ȷ�������
** ��ڲ���:			�жϺź��жϷ����ַ
** ���ڲ���:	0����1
** 
******************************************************************************/
boolen install_irq( uint8 IntNumber, void *HandlerAddr )
{
    uint8 i;
    uint32 *vect_addr;
    uint32 *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* ��ֹ�ж� */
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* �ҳ���һ��δ��������ַ */

	vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	if ( *vect_addr == (uint32)NULL )
	{
	    *vect_addr = (uint32)HandlerAddr;	/* �����ж����� */
	    *vect_cntl = (uint32)(IRQ_SLOT_EN | IntNumber);
	    break;
	}
    }
    if ( i == VIC_SIZE )
    {
	return( FALSE );		/* û�пյ�vector slot */
    }
    VICIntEnable = 1 << IntNumber;	/* ʹ��Interrupt */
    return( TRUE );
}

/******************************************************************************
** ������:		uninstall_irq
**
** ��������:	ж���жϴ���
**				ͨ���жϺ��ҵ��÷����ַ, ������Ϊ����ʵ��ж��.
** ��ڲ���:	�жϺ�
**���ڲ���:		0��1�ɹ����
** 
******************************************************************************/
boolen uninstall_irq( uint8 IntNumber )
{
    uint8 i;
    uint32 *vect_addr;
    uint32 *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* �ҵ���һ��δ�����VIC address  */
	vect_addr = (uint32 *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (uint32 *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	if ( (*vect_cntl & ~IRQ_SLOT_EN ) == IntNumber )
	{
	    *vect_addr = (uint32)NULL;	/* ��VIC��ַ */
	    *vect_cntl &= ~IRQ_SLOT_EN;	/*��ʹ��λ */	
	    break;
	}
    }
    if ( i == VIC_SIZE )
    {
	return( FALSE );		
    }
    VICIntEnable = 1 << IntNumber;
    return( TRUE );
}

#endif
/******************************************************************************
**                            End Of File
******************************************************************************/
