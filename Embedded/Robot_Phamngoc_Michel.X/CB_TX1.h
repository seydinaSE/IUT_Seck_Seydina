/* 
 * File:   CB_TX1.h
 * Author: E306-PC2
 *
 * Created on 4 décembre 2025, 10:36
 */

#ifndef CB_TX1_H
#define	CB_TX1_H

#ifdef	__cplusplus
extern "C" {
#endif
void SendMessage(unsigned char* message, int length);
void CB_TX1_Add(unsigned char value);
unsigned char CB_TX1_Get(void);
void SendOne();
unsigned char CB_TX1_IsTranmitting(void);
int CB_TX1_GetDataSize(void);
int CB_TX1_GetRemainingSize(void);




#ifdef	__cplusplus
}
#endif

#endif	/* CB_TX1_H */

