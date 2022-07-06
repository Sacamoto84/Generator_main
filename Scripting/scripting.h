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
/*
 * CH1 ON OFF -
 * CH2 ON OFF -
 *
 * CR1 SINUS
 *
 *
 *
 *
 * ----------------- Логика -----------------
 * GOTO 10
 *
 * IF R1 = 2
 * ...
 * ELSE
 * ...
 * ENDIF
 *
 * DELAY 1000 - Задержка работы
 *
 *
 *
 */

/*
 * Y-> YIELD
 * G-> GOTO
 *
 * D-> DELAY []
 *
 * I-> IF
 *
 * E-> END
 *
 */

class Scripting {
public:

	mString<12> Name; //Имя текущего скрипта

	//Загрузить скрипт в список
	void load(char *name) {
		char patch[32]; //Полный путь к файлу
		sprintf(patch, "/script/%s.txt", name); //Собираем полный путь в файлу
		int res = f_open(&SDFile, patch, FA_READ);
		//Ошибка открытия картинки с microSD
		if (res != FR_OK) {
			SEGGER_RTT_printf(0,
					"\033[01;38;05;51mScripting>\033[01;38;05;196mERROR open>\033[01;38;05;46m%s\r\n",
					patch);
			f_close(&SDFile);
			return;
		}

		line = 0;
		SEGGER_RTT_printf(0, "*** Скрипт %s***\r\n", patch);

		list[line] = name; //Для того чтобы строки начинались с 1
		SEGGER_RTT_printf(0, "%d:%s", line, list[line].buf);
		line++;

		while (f_gets(patch, 32, &SDFile)) {
			list[line] = patch;
			SEGGER_RTT_printf(0, "%d:%s", line, list[line].buf);
			line++;
		}
		f_close(&SDFile);
		SEGGER_RTT_printf(0, "\r\n*** Скрипт Конец ***\r\n");

		line = 0;
		Name = name;
	}

	//Выполнить команду по строке pc
	void CMD_EXE(void) {
		mString<12> comand;
		comand = list[pc];
		if (comand.indexOf((char*)"END", 0) == 0)
		{
			end = true;
			return;
		}
		//
		char c = comand.buf[0];
		switch (c) {
			case 'G':
			if (comand.indexOf((char*)"GOTO", 0) == 0)
			{
				pc = comand.toUint(4);
				SEGGER_RTT_printf(0, "Sс:GOTO->pc:%d", pc);
			}
			break;




			default:
				SEGGER_RTT_printf(0, "Sс:ХЗ pc:%d:%s", pc, comand.buf);
				pc++;
				break;
		};

	}

	void run()
	{
		end = false;
		while(end == false)
		{
		  CMD_EXE();
		}
	}

	bool  end;

	uint32_t pc;

	uint32_t Tick;

	uint16_t R[8]; //10 INT регистров
	uint16_t F[8]; //10 FLOAT регистров

	char str[24];           //Временная строка
	mString<12> list[128]; //Список команд

	uint8_t line = 0; //Текучая строка
};

#endif
