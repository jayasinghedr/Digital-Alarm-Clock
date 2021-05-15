/*
 * ds1307.h
 *
 * Created: 15/05/2021 22:19:28
 *  Author: User
 */ 


#ifndef DS1307_H_
#define DS1307_H_

#include <avr/io.h>

void i2c_init(){
	TWBR = 0x48;	// set bit rate 72
	TWCR = (1<<TWEN);
	TWSR = 0x00;	//sets the prescaler value to 1
}

void i2c_start(){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);	//initiate the start condition
	while(!((TWCR) & (1<<TWINT)));
	
	if ((TWSR) & 0xF8 != 0x08){
		PORTB = (1<<PORTB5);	//check if the start condition has been transmitted
	}
	else{
		PORTB |= (1<<PORTB0);
	}
}

void i2c_SLA_W(){
	TWDR = 0b11010000;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!((TWCR) & (1<<TWINT)));
	
	if ((TWSR & 0xF8) != 0x18){
		PORTB = (1<<PORTB5);
	}
	else{
		PORTB |= (1<<PORTB1);	//confirm SLA_W has been recieved
	}
}

void i2c_SLA_R(){
	TWDR = 0b11010001;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!((TWCR) & (1<<TWINT)));
	
	if ((TWSR & 0xF8) != 0x40){
		PORTB = (1<<PORTB5);
	}
	else{
		PORTB |= (1<<PORTB3);	//confirm SLA_W has been recieved
	}

}

void i2c_write(uint8_t x){
	TWDR = x;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!((TWCR) & (1<<TWINT)));
	
	
	if ((TWSR & 0xF8) != 0x28){
		PORTB = (1<<PORTB5);
	}
	else{
		PORTB |= (1<<PORTB2);
	}
}


uint8_t i2c_read(){
	
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!((TWCR) & (1<<TWINT)));
	return TWDR;
}



void i2c_stop(){
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

void set_time(rtc_t * rtc){
	i2c_init();
	i2c_start();
	i2c_SLA_W();	//initiates the device ds1307
	i2c_write(0x00);	//set the register pointer to 00(seconds reg)
	
	i2c_write(rtc -> seconds);	//seconds -> 50
	i2c_write(rtc -> minute);	//minutes -> 17
	i2c_write(rtc -> hour);	//hour -> 20
	i2c_write(rtc -> weekDay);	//day -> Thursday(4)
	i2c_write(rtc -> date);	//date -> 27
	i2c_write(rtc -> month);	//month -> May
	i2c_write(rtc -> year);	//year -> 2021
	
	//stop transmission
	i2c_stop();
}



uint8_t read_time(uint8_t reg){
	//sets the register pointer to 00H
	uint8_t x;
	i2c_start();
	i2c_SLA_W();	//initiates the device ds1307
	i2c_write(reg);	//set the register pointer to reg)
	i2c_stop();
	
	i2c_start();
	i2c_SLA_R();
	x = i2c_read();
	i2c_stop();
	return x;
}


#endif /* DS1307_H_ */