/*
 * ds1307.h
 *
 * Created: 15/05/2021 22:19:28
 *  Author: User
 */ 


#ifndef DS1307_H_
#define DS1307_H_

#define F_CPU 16000000UL
#include <avr/io.h>

//-------------TWI initialization------------------------------------------

void twi_init(){
	//TWBR = (F_CPU/SCL_freq - 16)/(2*prescalar)
	//F_CPU = 16MHz, SCL_freq(for DS1307) = 100KHz, prescalar = 1 -> TWBR =72
	TWBR = 0x48;	// set bit rate 72 
	TWCR = (1<<TWEN);	//enable TWI
	TWSR = 0x00;	//sets the prescalar value to 1
}

//------------TWI Start----------------------------------------------------

void twi_start(){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);	// initiate the start condition
	while(!((TWCR) & (1<<TWINT)));	// wait for the start condition to transmit
}

//----------TWI Write to Slave(Slave Address)-------------------------------

void twi_SLA_W(){
	//chooses the device address and sends the Write signal
	//DS1307 address = 1101000
	//Write = 0 (last bit)
	TWDR = 0b11010000;	//SLA + W to data register 
	TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	while(!((TWCR) & (1<<TWINT)));	//wait for SLA + W to transmit
}


//---------TWI Read from Slave(Slave Address)------------------------------

void twi_SLA_R(){
	//chooses the device address and sends the Read signal
	//DS1307 address = 1101000
	//Read = 1 (last bit)
	TWDR = 0b11010001;	//SLA + R to data register
	TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	while(!((TWCR) & (1<<TWINT)));	////wait for SLA + R to transmit
}

//-----------TWI Write(to Slave registers)----------------------------------

void twi_write(uint8_t x){
	TWDR = x;	//data byte to be written to the slave
	TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	while(!((TWCR) & (1<<TWINT)));	//wait for data byte to transmit
}

//------------TWI Read(from Slave registers)---------------------------------

uint8_t twi_read(){	
	TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	while(!((TWCR) & (1<<TWINT)));	//wait for data byte to transmit
	return TWDR;	//returns the data read from the slave which is stored in TWDR
}


//------------TWI Stop------------------------------------------------------

void twi_stop(){
	//stops the transmission with TWSTO  
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}


typedef struct
{
	uint8_t seconds;
	uint8_t minute;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc_t;

//----------------Set time to DS1307---------------------------------------

void set_time(rtc_t * rtc){
	twi_init();		
	twi_start();	//sending the start condition to DS1307
	twi_SLA_W();	//initiates the device ds1307 & sends write signal

	twi_write(0x00);	//set the register pointer to 00H(seconds reg)
	
	twi_write(rtc -> seconds);	
	twi_write(rtc -> minute);	
	twi_write(rtc -> hour);	
	twi_write(rtc -> weekDay);	
	twi_write(rtc -> date);	
	twi_write(rtc -> month);	
	twi_write(rtc -> year);	
	
	twi_stop(); //stop writing
}


//-----------------Read time from DS1307---------------------------------

uint8_t read_time(uint8_t reg){
	//sets the register pointer to the register we want -> reg (00H, 01H, etc)
	twi_start();
	twi_SLA_W();	//initiates the device ds1307
	twi_write(reg);	//set the register pointer to reg)
	twi_stop();
	
	//reading from the particular register
	uint8_t x;
	twi_start();
	twi_SLA_R();		//read from the reg
	x = twi_read();		//value read from reg is stored in x
	twi_stop();
	return x;
}


#endif /* DS1307_H_ */