/*
 * LCD_Display.h
 *
 * Created: 21/05/2021 11:30:24 PM
 *  Author: Jayabawan
 */ 


#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_
class LCD_Display{
	private:
	unsigned char comand;
	unsigned char data_00;
	char *string_00;
	char row_1;
	char position;
	public:
	void LCD_Commandgiver( unsigned char comand);
	void LCD_Initializer();
	void LCD_Character( unsigned char data_00);
	void LCD_String(char *string_00);
	void LCD_Clear();
	void LCD_String_xy(char row_1, char position, char *string_00);
};
	




#endif /* LCD_DISPLAY_H_ */