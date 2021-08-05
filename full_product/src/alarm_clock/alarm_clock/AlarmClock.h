/*
 * AlarmClock.h
 *
 * Created: 16/06/2021 20:01:31
 *  Author: User
 */ 


#ifndef ALARMCLOCK_H_
#define ALARMCLOCK_H_

class AlarmClock{

	private:
	int num;
	
	public:
	char* int_to_char(int num);
	void displayTime();	
	void setTimetoRTC();
	int* setNewAlarm();
};


#endif /* ALARMCLOCK_H_ */