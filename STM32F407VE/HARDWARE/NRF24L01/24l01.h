#ifndef __24L01_H
#define __24L01_H
#include "sys.h"
///////////////////////////////////////////////// ///////////////////////////////////////////////// //////
//NRF24L01 register operation command
#define NRF_READ_REG 0x00 //Read configuration register, the lower 5 bits are the register address
#define NRF_WRITE_REG 0x20 //Write the configuration register, the lower 5 bits are the register address
#define RD_RX_PLOAD 0x61 //Read RX valid data, 1~32 bytes
#define WR_TX_PLOAD 0xA0 //Write TX valid data, 1~32 bytes
#define FLUSH_TX 0xE1 //Clear the TX FIFO register. Used in transmit mode
#define FLUSH_RX 0xE2 //Clear RX FIFO register. Used in receive mode
#define REUSE_TX_PL 0xE3 //Reuse the last packet of data, CE is high, and the data packet is continuously sent.
#define NOP 0xFF //No operation, can be used to read the status register
//SPI(NRF24L01) register address
#define CONFIG 0x00 //Configuration register address; bit0: 1 receiving mode, 0 transmitting mode; bit1: electrical selection; bit2: CRC mode; bit3: CRC enable;
                              //bit4: interrupt MAX_RT (maximum number of retransmission interrupts) enable; bit5: interrupt TX_DS enable; bit6: interrupt RX_DR enable
#define EN_AA 0x01 //Enable automatic response function bit0~5, corresponding to channel 0~5
#define EN_RXADDR 0x02 //Receive address is allowed, bit0~5, corresponding to channel 0~5
#define SETUP_AW 0x03 //Set the address width (all data channels): bit1,0: 00, 3 bytes; 01, 4 bytes; 02, 5 bytes;
#define SETUP_RETR 0x04 //Establish automatic retransmission; bit3:0, automatic retransmission counter; bit7:4, automatic retransmission delay 250*x+86us
#define RF_CH 0x05 //RF channel, bit6:0, working channel frequency;
#define RF_SETUP 0x06 //RF register; bit3: transmission rate (0:1Mbps, 1:2Mbps); bit2:1, transmit power; bit0: low noise amplifier gain
#define STATUS 0x07 //Status register; bit0: TX FIFO full flag; bit3:1, receiving data channel number (maximum: 6); bit4, reaching the maximum number of retransmissions
                              //bit5: data transmission complete interrupt; bit6: receive data interrupt;
#define MAX_TX 0x10 // Interrupt when the maximum number of transmissions is reached
#define TX_OK 0x20 //TX transmission complete interrupt
#define RX_OK 0x40 //Data received interrupt

#define OBSERVE_TX 0x08 //Transmission detection register, bit7:4, packet loss counter; bit3:0, retransmission counter
#define CD 0x09 //Carrier detection register, bit0, carrier detection;
#define RX_ADDR_P0 0x0A //Data channel 0 receiving address, maximum length 5 bytes, low byte first
#define RX_ADDR_P1 0x0B //Data channel 1 receiving address, maximum length is 5 bytes, low byte first
#define RX_ADDR_P2 0x0C //Data channel 2 receiving address, the lowest byte can be set, and the high byte must be equal to RX_ADDR_P1[39:8];
#define RX_ADDR_P3 0x0D //Data channel 3 receiving address, the lowest byte can be set, and the high byte must be equal to RX_ADDR_P1[39:8];
#define RX_ADDR_P4 0x0E //Data channel 4 receiving address, the lowest byte can be set, and the high byte must be equal to RX_ADDR_P1[39:8];
#define RX_ADDR_P5 0x0F //Data channel 5 receiving address, the lowest byte can be set, and the high byte must be equal to RX_ADDR_P1[39:8];
#define TX_ADDR 0x10 //Send address (low byte first), in ShockBurstTM mode, RX_ADDR_P0 is equal to this address
#define RX_PW_P0 0x11 //The effective data width of receiving data channel 0 (1~32 bytes), set to 0 is illegal
#define RX_PW_P1 0x12 //The effective data width of receiving data channel 1 (1~32 bytes), set to 0 is illegal
#define RX_PW_P2 0x13 //Receive data channel 2 effective data width (1~32 bytes), set to 0 is illegal
#define RX_PW_P3 0x14 //Receive data channel 3 effective data width (1~32 bytes), set to 0 is illegal
#define RX_PW_P4 0x15 //Receive data channel 4 effective data width (1~32 bytes), set to 0 is illegal
#define RX_PW_P5 0x16 //The effective data width of receiving data channel 5 (1~32 bytes), set to 0 is illegal
#define NRF_FIFO_STATUS 0x17 //FIFO status register; bit0, RX FIFO register empty flag; bit1, RX FIFO full flag; bit2, 3, reserved
                              //bit4, TX FIFO empty flag; bit5, TX FIFO full flag; bit6, 1, cyclically send the last packet. 0, not cyclic;
///////////////////////////////////////////////// ///////////////////////////////////////////////// //////
//24L01 operation line
#define NRF24L01_CE PDout(5) //24L01 chip select signal
#define NRF24L01_CSN PDout(6) //SPI chip select signal
#define NRF24L01_IRQ PDin(7) //IRQ host data input

#define NRF24L01_2_CE PDout(8) //24L01 chip select signal
#define NRF24L01_2_CSN PDout(9) //SPI chip select signal
#define NRF24L01_2_IRQ PDin(10) //IRQ host data input
//24L01 send and receive data width definition
#define TX_ADR_WIDTH 5 //5 byte address width
#define RX_ADR_WIDTH 5 //5 byte address width
#define TX_PLOAD_WIDTH 32 //32-byte user data width
#define RX_PLOAD_WIDTH 32 //32-byte user data width


void NRF24L01_Init(void);//initialization
void NRF24L01_2_Init(void);//initialization

void NRF24L01_RX_Mode(void);//Configure to receive mode
void NRF24L01_2_RX_Mode(void);//Configure to receive mode

void NRF24L01_TX_Mode(void);//Configure to transmit mode
void NRF24L01_2_TX_Mode(void);//Configure to transmit mode

u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 u8s);//write data area
u8 NRF24L01_2_Write_Buf(u8 reg, u8 *pBuf, u8 u8s);//write data area

u8 NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 u8s);//Read data area
u8 NRF24L01_2_Read_Buf(u8 reg, u8 *pBuf, u8 u8s);//Read data area

u8 NRF24L01_Read_Reg(u8 reg); //Read register
u8 NRF24L01_2_Read_Reg(u8 reg); //Read register

u8 NRF24L01_Write_Reg(u8 reg, u8 value);//write register
u8 NRF24L01_2_Write_Reg(u8 reg, u8 value);//write register

u8 NRF24L01_Check(void);//Check whether 24L01 exists
u8 NRF24L01_2_Check(void);//Check whether 24L01 exists

u8 NRF24L01_TxPacket(u8 *txbuf);//Send a packet of data
u8 NRF24L01_2_TxPacket(u8 *txbuf);//Send a packet of data

u8 NRF24L01_RxPacket(u8 *rxbuf);//Receive a packet of data
u8 NRF24L01_2_RxPacket(u8 *rxbuf);//Receive a packet of data


#endif
