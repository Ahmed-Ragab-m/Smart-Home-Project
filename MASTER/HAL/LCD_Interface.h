

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Init(void);
void LCD_Write_char(u8 ch);
void LCD_Write_char(u8 ch);
void LCD_Write_String(u8*str);
void LCD_Write_Number(s16 num);
void LCD_Clear(void);
void LCD_Set_Cursor(u8 line,u8 cell);
void LCD_Binary(u8 num);
void LCD_Hex_Num(s16 num);
void LCD_string_snake(u8*str);
void lcd_write_shape(u8*shape_arr,u8 address);



#endif /* LCD_INTERFACE_H_ */