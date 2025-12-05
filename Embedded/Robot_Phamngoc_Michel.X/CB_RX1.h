/* 
 * File:   CB_RX1.h
 * Author: E306-PC2
 *
 * Created on 5 décembre 2025, 14:31
 */

#ifndef CB_RX1_H
#define	CB_RX1_H


void CB_RX1_Add(unsigned char value);
unsigned char CB_RX1_Get(void);
unsigned char CB_RX1_IsDataAvailable(void);
int CB_RX1_GetDataSize(void);
int CB_RX1_GetRemainingSize(void);
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CB_RX1_H */

