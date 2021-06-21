/*
 * ds1307.cpp
 *
 * Created: 22/05/2021 00:32:53
 *  Author: User
 */ 

  #include <avr/io.h>
  #include "ds1307.h"


  //-------------TWI initialization------------------------------------------

  void ds1307::twi_init(){
	  //TWBR = (F_CPU/SCL_freq - 16)/(2*prescalar)
	  //F_CPU = 16MHz, SCL_freq(for DS1307) = 100KHz, prescalar = 1 -> TWBR =72
	  TWBR = 0x48;	// set bit rate 72
	  TWCR = (1<<TWEN);	//enable TWI
	  TWSR = 0x00;	//sets the prescalar value to 1
  }

  //------------TWI Start----------------------------------------------------

  void ds1307::twi_start(){
	  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);	// initiate the start condition
	  while(!((TWCR) & (1<<TWINT)));	// wait for the start condition to transmit
  }

  //----------TWI Write to Slave(Slave Address)-------------------------------

  void ds1307::twi_SLA_W(){
	  //chooses the device address and sends the Write signal
	  //DS1307 address = 1101000
	  //Write = 0 (last bit)
	  TWDR = 0b11010000;	//SLA + W to data register
	  TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	  while(!((TWCR) & (1<<TWINT)));	//wait for SLA + W to transmit
  }


  //---------TWI Read from Slave(Slave Address)------------------------------

  void ds1307::twi_SLA_R(){
	  //chooses the device address and sends the Read signal
	  //DS1307 address = 1101000
	  //Read = 1 (last bit)
	  TWDR = 0b11010001;	//SLA + R to data register
	  TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	  while(!((TWCR) & (1<<TWINT)));	////wait for SLA + R to transmit
  }

  //-----------TWI Write(to Slave registers)----------------------------------

  void ds1307::twi_write(uint8_t x){
	  TWDR = x;	//data byte to be written to the slave
	  TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	  while(!((TWCR) & (1<<TWINT)));	//wait for data byte to transmit
  }

  //------------TWI Read(from Slave registers)---------------------------------

  uint8_t ds1307::twi_read(){
	  TWCR = (1<<TWINT) | (1<<TWEN);	//clear TWINT to start transmission
	  while(!((TWCR) & (1<<TWINT)));	//wait for data byte to transmit
	  return TWDR;	//returns the data read from the slave which is stored in TWDR
  }


  //------------TWI Stop------------------------------------------------------

  void ds1307::twi_stop(){
	  //stops the transmission with TWSTO
	  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
  }

  //----------------Set time to DS1307---------------------------------------

  

  void ds1307::set_time(rtc_t * rtc){
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

  int ds1307::read_time(uint8_t reg){
	  //sets the register pointer to the register we want -> reg (00H, 01H, etc)
	  twi_start();
	  twi_SLA_W();	//initiates the device ds1307
	  twi_write(reg);	//set the register pointer to reg)
	  twi_stop();
	  
	  //reading from the particular register
	  uint8_t x;
	  int y;
	  twi_start();
	  twi_SLA_R();		//read from the reg
	  x = twi_read();		//value read from reg is stored in x
	  twi_stop();
	  y = bcd_to_dec(x);
	  return y;
  }

  //-----------------Convert BCD to decimal---------------------------------

  int ds1307::bcd_to_dec(uint8_t num){
	  //Data received from DS1307 are in Binary Coded Decimal
	  //This function converts these data to decimal integers
	  int first4, last4, decValue;
	  
	  first4 = num & 0b00001111;	//gets first 4 digits
	  last4 = ((num & 0b11110000) >> 4); //get last 4 digits
	  decValue = last4 * 10 + first4;	//gives the corresponding decimal value
	  
	  return decValue;
  }

  //-----------------Convert decimal to BCD----------------------------------

  uint8_t ds1307::dec_to_bcd(int number){
	int x;
	uint8_t div=0, rem=0;
	uint8_t bcd;
	if (number > 9){
		x = number / 10;
		div = (x<<4);
		rem = (number % (10 * x));
		bcd = div | rem;
	}
	else{
		bcd = number;
	}
	return bcd;
  }