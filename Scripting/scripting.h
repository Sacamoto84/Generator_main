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

#include "HiSpeedDWT.h"

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
 *
 * G-> GOTO
 *
 *┌─ Задержка──┬────┐
 *│ DELAY 4000 │ OK │
 *└────────────┴────┘
 *
 * I-> IF
 *
 *┌─ Завершение──┬────┐
 *│ END          │ OK │
 *└──────────────┴────┘
 *
 * TEXT-> T Текст Нужно протестировать
 *
 *┌── Арифметика ────┬──────────────────────────────┬────┐
 *│ MINUS R1 5000    │  R1 - 5000-> R1     R0-R9    │ OK │ !Добавить принт
 *│ MINUS F1 5000.0  │  F1 - 5.1 -> F1     F0-F9    │ ?? │
 *│                  │                              │    │
 *│ MINUS R1 R2      │  R1-R2->R1                   │ OK │
 *│ MINUS F1 F2      │  F1-F2->F1                   │ ?? │
 *│                  │                              │    │
 *│ PLUS R1 4555     │  R1 + 4555 -> 4555    R0-R9  │ ?? │
 *│ PLUS F1 4555.5   │  F1 + 4555.5 -> 4555  R0-R9  │ ?? │
 *│                  │                              │    │
 *│ PLUS R1 R2       │  R1+R2->R1                   │ ?? │
 *│ PLUS F1 F2       │  F1+F2->F1                   │ ?? │
 *└──────────────────┴──────────────────────────────┴────┘
 *
 *//* ┌ ┐ └ ┘├ ┤ ┬ ┴ ┼ ─ │
 *┌── Загрузка константы в регистр ─┬────┐
 *│ LOAD  R1 2344    │ 2344 -> R1   │ OK │
 *│ LOAD  F1 2344.0  │ 2344 -> F1   │ OK │
 *└──────────────────┴──────────────┴────┘
 *┌── Копирование регистров───┐ Не готово
 *│ COPY R1 R2       │ R2->R1 │
 *│ COPY F1 F2       │ F2->F1 │
 *└──────────────────┴────────┘
 *┌── Отобразить дамп регистров ─┬────┐
 *│ PRINTR - Дамп регистров R    │ OK │
 *│ PRINTF - Дамп регистров F    │    │
 *└──────────────────────────────┴────┘
 *
 *
 * Переход если равно и не равно
 *
 */

extern HiSpeedDWT TimerDWT;

//Структура ответа для выделения пары операндов из команды
typedef struct {
	mString<20> operand0;
	mString<20> operand1;
}pair_operand;

//Структура ответа для выделения пары операндов из команды
typedef struct {
	mString<20> operand0;
	mString<20> operand1;
	mString<20> operand2;
}triple_operand;

class Scripting {
public:

	mString<20> Name; //Имя текущего скрипта

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

	void start(void) {
		pc = 1;
		end = false;
	}

	//Выполнить команду по строке pc
	void CMD_EXE(void) {
		mString<20> comand;
		comand = list[pc];

		//┌── END ─────────────────────────────────────┐
		if (comand.indexOf((char*) "END", 0) == 0) {
			SEGGER_RTT_printf(0, "Script:%d:END\r\n", pc);
			end = true;
			return;
		}
		//└────────────────────────────────────────────┘

		char c = comand.buf[0];
		switch (c) {

		//┌── MINUS ───────────────────────────────────┐
		case 'M':
			comandPlusMinus();
			pc++;
			break;
		//└────────────────────────────────────────────┘
		//┌── PLUS ───────────────────────────────────┐
		case 'P':

			if (comand.indexOf((char*) "PLUS", 0) == 0) {
			  comandPlusMinus();
			}

			if (comand.indexOf((char*) "PRINTR", 0) == 0) {
			  printR();
			}

			if (comand.indexOf((char*) "PRINTF", 0) == 0) {
			  printF();
			}

			pc++;
			break;
		//└────────────────────────────────────────────┘
		//┌── GOTO ────────────────────────────────────┐
		case 'G':
			if (comand.indexOf((char*) "GOTO", 0) == 0) {
				pc = comand.toUint(4);
				SEGGER_RTT_printf(0, "S:GOTO->pc:%d\r\n", pc);
			}
			break;
		//└────────────────────────────────────────────┘
		//┌── YELD ────────────────────────────────────┐
		case 'Y':
			if (comand.indexOf((char*) "YIELD", 0) == 0) {
				yield = true;
				SEGGER_RTT_printf(0, "\x1B[0mScript:%d:YIELD\r\n", pc);
				pc++;
			}
			break;
		//└────────────────────────────────────────────┘
		//┌── DELAY ───────────────────────────────────┐
		case 'D':
			if (comand.indexOf((char*) "DELAY", 0) == 0) {
				//TimerDWT.Start();
				uint32_t d = comand.toUint(5);
				sprintf(str, "\x1B[0mScript:%lu:DELAY %lu\r\n", pc, d);
				SEGGER_RTT_WriteString(0, str);
				endTime = uwTick + d;
				pc++;
			}
			break;
		//└────────────────────────────────────────────┘
		//┌── TEXT ────────────────────────────────────┐
		case 'T': {
			SEGGER_RTT_printf(0, "\x1B[0mScript:%d:%s", pc, comand.buf[5]);
			pc++;
			break;
		}
		//└────────────────────────────────────────────┘

		//┌── LOAD ────────────────────────────────────┐
		case 'L': {
			SEGGER_RTT_printf(0, "\x1B[0mScript:%d:%s", pc, comand.buf);
			triple = excretionTripleOperand(comand);
			if (triple.operand0 == (char*)"LOAD")
			{
			   int index = triple.operand1.buf[1]-0x30;

			   if (triple.operand1.buf[0] == 'R')
				   R[index] = triple.operand2.toInt();
			   else
				   F[index] = triple.operand2.toFloat();
			}
			pc++;
			break;
		}
		//└────────────────────────────────────────────┘


		default:
			SEGGER_RTT_printf(0, "Script:? pc:%d:%s\r\n", pc, comand.buf);
			pc++;
			break;

		};

	}



	void comandPlusMinus()	{
		mString<20> comand;
		comand = list[pc];

		triple = excretionTripleOperand(comand);

		int index = triple.operand1.buf[1] - 0x30;//Индекс первой ячейки 0..9

		if (( triple.operand2.buf[0] == 'R') || ( triple.operand2.buf[0] == 'F'))
		{
		  //Втокой операнд это регистор
		  int secondIndex = triple.operand2.buf[1]-0x30; //Индекс второго регистра

		  //┌── MINUS ────────────────────────────────────┐
		  if (triple.operand0 == (char*)"MINUS") {
			    if (triple.operand1.buf[0] == 'R'){
				  R[index] = R[index]-R[secondIndex]; } //MINUS R* R*
			    else {
			      F[index] = F[index]-F[secondIndex]; } //MINUS F* F*
		  }
		  //└────────────────────────────────────────────┘
		  //┌── PLUS ────────────────────────────────────┐
		  if (triple.operand0 == (char*)"PLUS") {
		    if (triple.operand1.buf[0] == 'R'){
			  R[index] = R[index]+R[secondIndex]; } //MINUS R* R*
		    else {
		      F[index] = F[index]+F[secondIndex]; } //MINUS F* F*
		  }
		  //└────────────────────────────────────────────┘
		}
	    else
		{

		  //Второй операнд это константа
	      int value;
	      float fvalue;

		  if (triple.operand1.buf[0] == 'R'){
			  value = triple.operand2.toInt(); }
		  else{
			  fvalue = triple.operand2.toFloat(); }

		  //┌── MINUS ────────────────────────────────────┐
		  if (triple.operand0 == (char*)"MINUS") {
			if (triple.operand1.buf[0] == 'R'){
		      R[index] = R[index]-value; } //MINUS R* R*
		    else {
			  F[index] = F[index]-fvalue; } //MINUS F* F*
		  }
		  //└────────────────────────────────────────────┘
		  //┌── PLUS ────────────────────────────────────┐
		  if (triple.operand0 == (char*)"PLUS") {
		    if (triple.operand1.buf[0] == 'R'){
			  R[index] = R[index]+value; } //MINUS R* R*
		    else {
		      F[index] = F[index]+fvalue; } //MINUS F* F*
		  }
		  //└────────────────────────────────────────────┘
		}
	}

	void run() {
		if (end)
			return;
		end = false;
		yield = false;
		if (uwTick < endTime)
			return;
		endTime = 0;
		while ((yield == false) && (end == false)) {
			CMD_EXE();
			if (uwTick <= endTime)
				return;
		}
	}



	void printR()
	{
		SEGGER_RTT_printf(0, "\x1B[0mR 0:%d 1:%d 2:%d 3:%d 4:%d 5:%d 6:%d 7:%d 8:%d 9:%d\r\n", R[0],R[1],R[2],R[3],R[4],R[5],R[6],R[7],R[8],R[9]);
	}

	void printF()
	{
		SEGGER_RTT_printf(0, "\x1B[0mF 0:%.1f 1:%.1f 2:%.1f 3:%.1f 4:%.1f 5:%.1f 6:%.1f 7:%.1f 8:%.1f 9:%.1f\r\n", F[0],F[1],F[2],F[3],F[4],F[5],F[6],F[7],F[8],F[9]);
	}


    //Выделение пары операндов из строки
	pair_operand excretionPairOperand(mString<20> str){
		pair_operand out;
		char* strings[3];
		str.split(strings, ' ');
		out.operand0 = strings[1];
		out.operand1 = strings[2];
		out.operand1.truncate(1);
		return out;
	}

    //Выделение пары операндов из строки
	triple_operand excretionTripleOperand(mString<20> str){
		triple_operand out;
		char* strings[3];
		str.split(strings,' ');
		out.operand0 = strings[0];
		out.operand1 = strings[1];
		out.operand2 = strings[2];
		out.operand2.truncate(1);
		return out;
	}

	pair_operand   pair;
	triple_operand triple;

	bool end = true;
	bool yield = false;
	uint32_t pc;

	uint32_t endTime; //Время > которого можно продолжать работу

	int16_t R[10]; //10 INT регистров
	float   F[10]; //10 FLOAT регистров

	char str[32];           //Временная строка
	mString<20> list[128]; //Список команд

	uint8_t line = 0; //Текучая строка
};

#endif
