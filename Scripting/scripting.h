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

#include "generator.h"

extern uint8_t render;

extern HiSpeedDWT TimerT5;

//Команда максимум 20 байт [128]
//Скрипты лежат в папке script

/*
 * ----------------- Логика -----------------
 * IF R1 = 2
 * ...
 * ELSE
 * ...
 * ENDIF
 *
 * DELAY 1000 - Задержка работы
 */

/*
 *╭─ Выйти ─╮╭─ Переход ─╮╭─ Задержка ─╮╭─ Завершение ─╮╭─ Текст ────╮
 *│ YIELD   ││ GOTO 2    ││ DELAY 4000 ││ END          ││ TEXT Текст │
 *╰─────────╯╰───────────╯╰────────────╯╰──────────────╯╰────────────╯
 *╭─ Арифметика ────┬─────────────────────╮╭─ Загрузка константы в регистр ─╮
 *│ MINUS R1 5000   │ R1 - 5000-> R1      ││ LOAD R1 2344    │ 2344 -> R1   │
 *│ MINUS F1 5000.0 │ F1 - 5.1 -> F1      ││ LOAD F1 2344.0  │ 2344 -> F1   │
 *│                 │                     │╰─────────────────┴──────────────╯
 *│ MINUS R1 R2     │ R1-R2->R1           │╭─ Отобразить дамп регистров ──╮
 *│ MINUS F1 F2     │ F1-F2->F1           ││ PRINTR - Дамп регистров R    │
 *│                 │                     ││ PRINTF - Дамп регистров F    │
 *│ PLUS R1 4555    │ R1 + 4555 -> 4555   │╰──────────────────────────────╯
 *│ PLUS F1 4555.5  │ F1 + 4555.5 -> 4555 │
 *│                 │                     │
 *│ PLUS R1 R2      │ R1+R2->R1           │
 *│ PLUS F1 F2      │ F1+F2->F1           │
 *╰─────────────────┴─────────────────────╯
 *╭─ Генератор ─────────────────╮╭─╮
 *│ CH[1 2] [CR AM FM] [ON OFF] ││✓│
 *│                             ││ │
 *│ CR[1 2] FR 1000.0           ││✓│
 *│ CR[1 2] MOD 02_HWawe        ││✓│
 *│                             ││ │
 *│ AM[1 2] FR 1000.3           ││✓│
 *│ AM[1 2] MOD 02_HWawe        ││✓│
 *│                             ││ │
 *│ FM[1 2] BASE 1234.6         ││✓│
 *│ FM[1 2] DEV  123.8          ││✓│
 *│ FM[1 2] MOD  02_HWawe       ││✓│
 *│ FM[1 2] FR   3.5            ││✓│
 *╰─────────────────────────────╯╰─╯
 * ┌ ┐ └ ┘├ ┤ ┬ ┴ ┼ ─ │╭╮╯╰│ ─ ✓
 *╭─ Копирование регистров ───╮ Не готово
 *│ COPY R1 R2       │ R2->R1 │
 *│ COPY F1 F2       │ F2->F1 │
 *╰──────────────────┴────────┘
 *
 *
 * Переход если равно и не равно
 *
 *
 *
 *
 *
 *
 *
 *
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

		mString<20> com;
		com = comand;
		com.truncate(1);
		SEGGER_RTT_WriteString(0, "\x1B[01;38;05;208;48;05;234mScript \x1B[01;38;05;7;48;05;234m:");
		SEGGER_RTT_printf(0, "%d \x1B[01;38;05;10;48;05;234m%s \x1B[0m \n", pc, com.buf);

		//SEGGER_RTT_WriteString(0, "\x1B[0m");

		//┌── END ─────────────────────────────────────┐
		if (comand.indexOf((char*) "END", 0) == 0) {
			end = true;
			return;
		}
		//└────────────────────────────────────────────┘

		char c = comand.buf[0];

		switch (c) {

		//┌── Генератор ──────────────────────────────┐
		case 'C':
			generatorComand();
			pc++;
			break;

		case 'A':
			generatorComand();
			pc++;
			break;

		case 'F':
			generatorComand();
			pc++;
			break;
		//└────────────────────────────────────────────┘


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
			}
			break;
		//└────────────────────────────────────────────┘
		//┌── YELD ────────────────────────────────────┐
		case 'Y':
			if (comand.indexOf((char*) "YIELD", 0) == 0) {
				yield = true;
				pc++;
			}
			break;
		//└────────────────────────────────────────────┘
		//┌── DELAY ───────────────────────────────────┐
		case 'D':
			if (comand.indexOf((char*) "DELAY", 0) == 0) {
				uint32_t d = comand.toUint(5);
				endTime = uwTick + d;
				pc++;
			}
			break;
		//└────────────────────────────────────────────┘
		//┌── TEXT ────────────────────────────────────┐
		case 'T': {
			pc++;
			break;
		}
		//└────────────────────────────────────────────┘

		//┌── LOAD ────────────────────────────────────┐
		case 'L': {
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
	      int   value  = 0;
	      float fvalue = 0.0F;

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
		char s[80];
		sprintf(s, "\x1B[0mF 0:%.1f 1:%.1f 2:%.1f 3:%.1f 4:%.1f 5:%.1f 6:%.1f 7:%.1f 8:%.1f 9:%.1f\r\n", F[0],F[1],F[2],F[3],F[4],F[5],F[6],F[7],F[8],F[9]);
		SEGGER_RTT_printf(0, s );
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

	GENERATOR * G;



	void generatorComand(void)
	{
		mString<20> comand;
		comand = list[pc];

		triple = excretionTripleOperand(comand);

		uint8_t chanel = 1;
		chanel = triple.operand0.buf[2] - 0x30; //Номер канала

		uint8_t onoff = 0;

	//╭─ CH1 CH2 ───────────────────────────────────────────────────────────────────╮
	    if ((triple.operand0 == (char*)"CH1")||(triple.operand0 == (char*)"CH2")) //│
	    {                                                                         //│
	      if (triple.operand2 == (char*)"ON") onoff = 1; else onoff = 0;          //│
	                                                                              //│
	      if (triple.operand1 == (char*)"CR")                                     //│
	      {                                                                       //│
	    	  if (chanel == 1)                                                    //│
	    		  G->CH1.CH_EN = onoff;                                           //│
	    	  else                                                                //│
	    		  G->CH2.CH_EN = onoff;                                           //│
	      }                                                                       //│
	                                                                              //│
	      if (triple.operand1 == (char*)"AM")                                     //│
	      {                                                                       //│
	    	  if (chanel == 1)                                                    //│
	    		  G->CH1.AM_EN = onoff;                                           //│
	    	  else                                                                //│
	    		  G->CH2.AM_EN = onoff;                                           //│
	      }                                                                       //│
	                                                                              //│
	      if (triple.operand1 == (char*)"FM")                                     //│
	      {                                                                       //│
	    	  if (chanel == 1)                                                    //│
	    		  G->CH1.FM_EN = onoff;                                           //│
	    	  else                                                                //│
	    		  G->CH2.FM_EN = onoff;                                           //│
	      }                                                                       //│
	                                                                              //│
	      render = 1;                                                             //│
	                                                                              //│
	      return;                                                                 //│
	    }                                                                         //│
	//╰─────────────────────────────────────────────────────────────────────────────╯

	//╭─ CR1 CR2 ───────────────────────────────────────────────────────────────────╮
		if ((triple.operand0 == (char*)"CR1")||(triple.operand0 == (char*)"CR2")) //│
		{                                                                         //│
			//CR[1 2] MOD 01_Sine_12b                                             //│
		    if (triple.operand1 == (char*)"MOD")                                  //│
		    {                                                                     //│
		       if (chanel == 1){                                                  //│
		      	sprintf(G->CH1.Carrier_mod,"%s.dat",triple.operand2.buf);         //│
	              G->Create_Carrier1();                                           //│
		       }                                                                  //│
		       else                                                               //│
		       {                                                                  //│
		      	sprintf(G->CH2.Carrier_mod,"%s.dat",triple.operand2.buf);         //│
		      	G->Create_Carrier2();                                             //│
		       }                                                                  //│
		      render = 1;                                                         //│
		    }                                                                     //│
		                                                                          //│
			//CR[1 2] FR 1000.3                                                   //│
		    if (triple.operand1 == (char*)"FR")                                   //│
			{                                                                     //│
			   float value = triple.operand2.toFloat();                           //│
			   if (chanel == 1)                                                   //│
			     G->CH1.Carrier_fr = (uint16_t)value;                             //│
			   else                                                               //│
			     G->CH2.Carrier_fr = (uint16_t)value;                             //│
			   render = 1;                                                        //│
			}                                                                     //│
                                                                                  //│
		  return;                                                                 //│
		}                                                                         //│
	//╰─────────────────────────────────────────────────────────────────────────────╯

	//╭─ AM1 AM2 ───────────────────────────────────────────────────────────────────╮
	    if ((triple.operand0 == (char*)"AM1")||(triple.operand0 == (char*)"AM2")) //│
	    {                                                                         //│
	      //SEGGER_RTT_printf(0, "╭─ AM1 AM2 ─╮\n");                              //│
	    	                                                                      //│
	      //AM[1 2] FR 1000.3                                                     //│
	      if (triple.operand1 == (char*)"FR")                                     //│
	      {                                                                       //│
             float value = triple.operand2.toFloat();                             //│
             if (chanel == 1)                                                     //│
               G->CH1.AM_fr = value;                                              //│
             else                                                                 //│
               G->CH2.AM_fr = value;                                              //│
             render = 1;                                                          //│
	      }                                                                       //│
	                                                                              //│
	      //AM[1 2] MOD 02_HWawe { 1.9ms }                                        //│
	      if (triple.operand1 == (char*)"MOD")                                    //│
	      {                                                                       //│
	         if (chanel == 1){                                                    //│
	        	sprintf(G->CH1.AM_mod,"%s.dat",triple.operand2.buf);              //│
                G->Create_AM_Modulation1();                                       //│
	         }                                                                    //│
	         else                                                                 //│
	         {                                                                    //│
	        	sprintf(G->CH2.AM_mod,"%s.dat",triple.operand2.buf);              //│
	        	G->Create_AM_Modulation2();                                       //│
	         }                                                                    //│
	        render = 1;                                                           //│
	      }                                                                       //│
	      return;                                                                 //│
	    }                                                                         //│
	//╰─────────────────────────────────────────────────────────────────────────────╯
	//╭─ FM1 FM2 ───────────────────────────────────────────────────────────────────╮
	    if ((triple.operand0 == (char*)"FM1")||(triple.operand0 == (char*)"FM2")) //│
	    {                                                                         //│
	      SEGGER_RTT_printf(0, "╭─ FM1 FM2 ─╮\n");                                //│
	                                                                              //│
	      //FM[1 2] BASE 1234.6                                                   //│
	      if (triple.operand1 == (char*)"BASE")                                   //│
	      {                                                                       //│
	    	  float value = triple.operand2.toFloat();                            //│
	    	  if (chanel == 1){                                                   //│
	    	    G->CH1.FM_Base = (uint16_t)value;                                 //│
	    	    G->Refresh_FM_Modulation1();                                      //│
	    	  }                                                                   //│
	    	  else{                                                               //│
	    	    G->CH2.FM_Base = (uint16_t)value;                                 //│
	    	    G->Refresh_FM_Modulation2();                                      //│
	    	  }                                                                   //│
	    	  render = 1;                                                         //│
	      }                                                                       //│
                                                                                  //│
	      //FM[1 2] DEV  123.8                                                    //│
	      if (triple.operand1 == (char*)"DEV")                                    //│
	      {                                                                       //│
	    	  float value = triple.operand2.toFloat();                            //│
	    	  if (chanel == 1){                                                   //│
	    	    G->CH1.FM_Dev = value;                                            //│
	    	    G->Refresh_FM_Modulation1();                                      //│
	    	  }                                                                   //│
	    	  else{                                                               //│
	    	    G->CH2.FM_Dev = value;                                            //│
	    	    G->Refresh_FM_Modulation2();                                      //│
	    	  }                                                                   //│
	    	  render = 1;                                                         //│
	      }                                                                       //│
	                                                                              //│
	      //FM[1 2] MOD 02_HWawe                                                  //│
	      if (triple.operand1 == (char*)"MOD")                                    //│
	      {                                                                       //│
	    	  if (chanel == 1){                                                   //│
	    	 	 sprintf(G->CH1.FM_mod,"%s.dat",triple.operand2.buf);             //│
	    	     G->Create_FM_Modulation1();                                      //│
	    	  }                                                                   //│
	    	  else                                                                //│
	    	  {                                                                   //│
	    	 	 sprintf(G->CH2.FM_mod,"%s.dat",triple.operand2.buf);             //│
	    	 	 G->Create_FM_Modulation2();                                      //│
	    	  }                                                                   //│
                                                                                  //│
	    	  render = 1;                                                         //│
	      }                                                                       //│
                                                                                  //│
	      //FM[1 2] FR   3.5                                                      //│
	      if (triple.operand1 == (char*)"FR")                                     //│
	      {                                                                       //│
	    	  float value = triple.operand2.toFloat();                            //│
	    	  if (chanel == 1)                                                    //│
	    	    G->CH1.FM_mod_fr = value;                                         //│
	    	  else                                                                //│
	    	    G->CH2.FM_mod_fr = value;                                         //│
	    	  render = 1;                                                         //│
	      }                                                                       //│
                                                                                  //│
	      return;                                                                 //│
	    }                                                                         //│
	//╰─────────────────────────────────────────────────────────────────────────────╯
	}

















};








#endif
