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

#include "tim.h"

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
 * T-> T Текст
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
		SEGGER_RTT_printf(0, "%d:%s\r\n", line, list[line].buf);
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

	void start(void){
		pc = 1;
		end = false;
	}


	//Выполнить команду по строке pc
	void CMD_EXE(void) {
		mString<12> comand;
		comand = list[pc];

		//- END -
		if (comand.indexOf((char*)"END", 0) == 0)
		{
			SEGGER_RTT_printf(0, "Script:%d:END\r\n", pc);
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
				SEGGER_RTT_printf(0, "S:GOTO->pc:%d\r\n", pc);
			}
			break;

			case 'Y':
			if (comand.indexOf((char*)"YIELD", 0) == 0)
			{
				yield = true;
				SEGGER_RTT_printf(0, "\x1B[0mScript:%d:YIELD\r\n", pc);
				pc++;
			}
			break;

			case 'D':
			if (comand.indexOf((char*)"DELAY", 0) == 0)
			{
				uint32_t d =  comand.toUint(5);
				sprintf(str, "\x1B[0mScript:%lu:DELAY %lu\r\n", pc , d);
				SEGGER_RTT_WriteString(0, str);
				endTime = uwTick+d;
				pc++;
			}
			break;

			case 'T':
				SEGGER_RTT_printf(0, "\x1B[0mScript:%d:%s", pc, comand.buf);
				pc++;
			break;

			default:
				SEGGER_RTT_printf(0, "Script:? pc:%d:%s\r\n", pc, comand.buf );
				pc++;
				break;

		};

	}

	void run()
	{
		if (end)
			        return;

		end = false;
		yield = false;

		if (uwTick < endTime)
			return;

		endTime = 0;

		while((yield == false) && (end == false))
		{
		  CMD_EXE();
		  if (uwTick < endTime) 	return;
		}

	}

	bool  end   = true;
	bool  yield = false;
	uint32_t pc;

	uint32_t endTime; //Время > которого можно продолжать работу

	uint16_t R[8]; //10 INT регистров
	uint16_t F[8]; //10 FLOAT регистров

	char str[32];           //Временная строка
	mString<12> list[128]; //Список команд

	uint8_t line = 0; //Текучая строка
};

#endif
