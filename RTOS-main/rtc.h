/*****************************************************************************
 *   rtc.h
******************************************************************************/
#ifndef __RTC_H 
#define __RTC_H

#if     RTC_EN
typedef struct {
    uint32 RTC_Sec;     /* �� - [0,59] */
    uint32 RTC_Min;     /* �� - [0,59] */
    uint32 RTC_Hour;    /* Сʱ - [0,23] */
    uint32 RTC_Mday;    /* ��������- [1,31] */
    uint32 RTC_Mon;     /* �� - [1,12] */
    uint32 RTC_Year;    /* �� - [0,4095] */
    uint32 RTC_Wday;    /* ����- [0,6] */
    uint32 RTC_Yday;    /* �������� - [1,365] */
} RTCTime;

#define IMSEC		0x00000001
#define IMMIN		0x00000002
#define IMHOUR		0x00000004
#define IMDOM		0x00000008
#define IMDOW		0x00000010
#define IMDOY		0x00000020
#define IMMON		0x00000040
#define IMYEAR		0x00000080

#define AMRSEC		0x00000001  /* ���������� */
#define AMRMIN		0x00000002  /* ���������*/
#define AMRHOUR		0x00000004  /* ����Сʱ���� */
#define AMRDOM		0x00000008  /* ������*/
#define AMRDOW		0x00000010  /*���ڰ�������*/
#define AMRDOY		0x00000020  /* ���ε�����*/
#define AMRMON		0x00000040  /* ������*/
#define AMRYEAR		0x00000080  /* ���� */

#define PREINT_RTC	0x000001C8  /* ��Ƶ��������,PCLK = 15Mhz */
#define PREFRAC_RTC	0x000061C0  /* ��ƵС������ PCLK = 15Mhz */
#define ILR_RTCCIF	0x01
#define ILR_RTCALF	0x02

#define CCR_CLKEN	0x01
#define CCR_CTCRST	0x02
#define CCR_CLKSRC	0x10

extern void RTCHandler (void) __irq;
extern void RTCInit( void );
extern void RTCStart( void );
extern void RTCStop( void );
extern void RTC_CTCReset( void );
extern void RTCSetTime( RTCTime );
extern RTCTime RTCGetTime( void );
extern void RTCSetAlarm( RTCTime );
extern void RTCSetAlarmMask( uint32 AlarmMask );

#endif

#endif 
/*****************************************************************************
**                            End Of File
******************************************************************************/
