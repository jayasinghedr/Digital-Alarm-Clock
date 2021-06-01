/*
 * ds1307.h
 *
 * Created: 15/05/2021 22:19:28
 *  Author: User
 */ 


#ifndef DS1307_H_
#define DS1307_H_

class ds1307{

	private:
	uint8_t x;
	uint8_t reg;
	uint8_t num;

	public:
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

	void twi_init();
	void twi_start();
	void twi_SLA_W();
	void twi_SLA_R();
	void twi_write(uint8_t x);
	uint8_t twi_read();
	void twi_stop();
	void set_time(rtc_t * rtc);
	uint8_t read_time(uint8_t reg);
	int bcd_to_dec(uint8_t num);
};

#endif /* DS1307_H_ */