/*
 * scripting.h
 *
 *  Created on: Jul 5, 2022
 *      Author: Ivan
 */

#ifndef SCRIPTING_H_
#define SCRIPTING_H_

#include "mString.h"
#include "main.h"
#include "fatfs.h"
#include "SEGGER.h"
#include "SEGGER_RTT.h"

//Команда максимум 12 байт [128]
//Скрипты лежат в папке script

class Scripting {
public:

	mString <12> Name; //Имя текущего скрипта

	//Загрузить скрипт в список
	void load(char * name)
	{
		char patch[32]; //Полный путь к файлу
		sprintf(patch, "/script/%s.txt", name); //Собираем полный путь в файлу
		int res = f_open(&SDFile, patch, FA_READ);
		//Ошибка открытия картинки с microSD
		if(res != FR_OK){
			SEGGER_RTT_printf(0, "\033[01;38;05;51mScripting>\033[01;38;05;196mERROR open>\033[01;38;05;46m%s\r\n", patch);
			f_close(&SDFile);
		    return;
		}

		line = 0;
		SEGGER_RTT_printf(0, "*** Скрипт %s***\r\n", patch);

		while (f_gets(patch, 32, &SDFile)) {
			list[line] = patch;
			SEGGER_RTT_printf(0, "%d:%s\r\n", line, list[line]);
			line++;
		}

		f_close(&SDFile);

		line = 0;
		Name = name;
	}




private:
  char str[24]; //Временная строка
  mString <12> list[128]; //Список команд

  uint8_t line = 0; //Текучая строка


};






#endif /* SCRIPTING_H_ */
