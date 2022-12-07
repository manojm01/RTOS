/*****************************************************************************
 *  
  ADת������
 *
******************************************************************************/
//#include "define.h"
#if ADC_EN                      /*�������ADC*/



uint32 ADC0Value[ADC_NUM];
uint32 ADC0IntDone = 0;

#if ADC_INTERRUPT_FLAG
/**************************************************************************************
** �������� ��ADC0Handler (void) __irq
** �������� ��ADC0�жϴ���
** ��ڲ��� ��
** ���ڲ��� ��
***************************************************************************************/
void ADC0Handler (void) __irq 
{
    uint32 regVal;
  
    IENABLE;			/* ����Ƕ���ж� */

    regVal = AD0STAT;		/* ��ADC�����ADC�жϱ�־ */
    if ( regVal & 0x0000FF00 )	/*���OVERRUN  */
    {
	regVal = (regVal & 0x0000FF00) >> 0x08;
	switch ( regVal )
	{
	    case 0x01:
		regVal = AD0DR0;
		break;
	    case 0x02:
		regVal = AD0DR1;
		break;
	    case 0x04:
		regVal = AD0DR2;
		break;
	    case 0x08:
		regVal = AD0DR3;
		break;
	    case 0x10:
		regVal = AD0DR4;
		break;
	    case 0x20:
		regVal = AD0DR5;
		break;
	    case 0x40:
		regVal = AD0DR6;
		break;
	    case 0x80:
		regVal = AD0DR7;
		break;
	    default:
		break;
	}
	AD0CR &= 0xF8FFFFFF;	/*ֹͣADC */ 
	ADC0IntDone = 1;
	return;	
    }
    
    if ( regVal & ADC_ADINT )
    {
	switch ( regVal & 0xFF )	/* ���DONEλ */
	{
	    case 0x01:
		ADC0Value[0] = ( AD0DR0 >> 6 ) & 0x3FF;
		break;
	    case 0x02:
		ADC0Value[1] = ( AD0DR1 >> 6 ) & 0x3FF;
		break;
	    case 0x04:
		ADC0Value[2] = ( AD0DR2 >> 6 ) & 0x3FF;
		break;
	    case 0x08:
		ADC0Value[3] = ( AD0DR3 >> 6 ) & 0x3FF;
		break;
	    case 0x10:
		ADC0Value[4] = ( AD0DR4 >> 6 ) & 0x3FF;
		break;
	    case 0x20:
		ADC0Value[5] = ( AD0DR5 >> 6 ) & 0x3FF;
		break;
	    case 0x40:
		ADC0Value[6] = ( AD0DR6 >> 6 ) & 0x3FF;
		break;
	    case 0x80:
		ADC0Value[7] = ( AD0DR7 >> 6 ) & 0x3FF;
		break;		
	    default:
		break;
	}
	AD0CR &= 0xF8FFFFFF;	/*ֹͣADC */ 
	ADC0IntDone = 1;
    }

    IDISABLE;
    VICVectAddr = 0;	
}
#endif
/**************************************************************************************
** �������� ��ADCInit (uint32)
** �������� ��ADC��ʼ��
** ��ڲ��� ��Ҫ��ʼ����ͨ��
** ���ڲ��� ��
***************************************************************************************/
boolen ADC_Init(uint32 ADCCLK )
{
/* ��������ΪADC����, AD0.0~7*/	
    PINSEL0 = 0x0F333F00;

    AD0CR = ( 0x01 << 0 ) |   	        /* ����ΪNʱѡ��ͨ��N  */
	( ( Fpclk / (ADCCLK - 1 )) << 8 ) |  /* CLKDIV = Fpclk / 1000000 - 1  */
	( 0 << 16 ) | 		// BURST = 0, 1
	( 0 << 17 ) |  		// CLKS = 0, 11
	( 1 << 21 ) |  		// PDN = 1, 
	( 0 << 22 ) |  		// TEST1:0 = 00 
	( 0 << 24 ) |  		// START = 0 A/D ת��ֹͣ
	( 0 << 27 );		/* EDGE = 0 (CAP/MAT �������½����� A/D conversion) */


#if ADC_INTERRUPT_FLAG
    AD0INTEN = 0x11E;		/*ʹ������ADC�ж�*/

    if ( install_irq( ADC0_INT, (uint32*)ADC0Handler ) == FALSE )
    {
	return (FALSE);
    }
#endif
    return (TRUE);
}
/*****************************************************************************
**������:		ADC0Read
**
** ��������:	��ADC0ת�����
**
** ��ڲ���:			ͨ����
** ���ڲ���:	
** 
*****************************************************************************/
uint32 ADC0Read( uint8 channelNum )
{
#if !ADC_INTERRUPT_FLAG
    uint32 regVal, ADC_Data;
#endif

    /* ͨ���� */
    if ( channelNum >= ADC_NUM )
    {
	channelNum = 0;		/*����������ADCͨ������7��������ͨ��Ϊ0 */
    }
    AD0CR &= 0xFFFFFF00;
    AD0CR |= (1 << 24) | (1 << channelNum);	
				/* ѡ��ͨ������ADC��ʼת��*/
#if !ADC_INTERRUPT_FLAG
    while ( 1 )			/* �ȴ�ADCת������ */
    {
	regVal = *(volatile unsigned long *)(AD0_BASE_ADDR 
			+ ADC_OFFSET + ADC_INDEX * channelNum);
				/* ��ADCת����� */
	if ( regVal & ADC_DONE )
	{
	    break;
	}
    }	
        
    AD0CR &= 0xF8FFFFFF;	/* ֹͣADC */    
    if ( regVal & ADC_OVERRUN )	/* ��û�д��������±������� */
    {
	return ( 0 );
    }
    ADC_Data = ( regVal >> 6 ) & 0x3FF;
    return ( ADC_Data );	/* ����ADCת����ֵ */
#else
    return ( channelNum );	/* ���ADC�ж���������ô���������ADC�жϷ�������еõ�����ֻ����ͨ���� */
#endif
}

#endif
/*********************************************************************************
**                            End Of File
*********************************************************************************/
