/*
 * LOG.c
 *
 *  Created on: 27 дек. 2021 г.
 *      Author: Ivan
 */
#include "LOG.h"

char log_str[256] __attribute__((aligned (4)));

const char log_i_s1[] = "\x1B[2;30m\x1B[4;43m"; //RTT_CTRL_TEXT_BLACK, RTT_CTRL_BG_BRIGHT_YELLOW

const char log_i_s2[] = "\x1B[1;37m\x1B[4;44m"; //RTT_CTRL_TEXT_BRIGHT_WHITE, RTT_CTRL_BG_BRIGHT_BLUE
const char log_reset[] = "\x1B[0m";             //RTT_CTRL_RESET
const char log_i_s4[] = "\x1B[24;44m";          //RTT_CTRL_BG_BLUE

const char log_d_s2[] = "\x1B[1;32m\x1B[4;44m"; //RTT_CTRL_TEXT_BRIGHT_GREEN, RTT_CTRL_BG_BRIGHT_BLUE;
const char log_d_s4[] = "\x1B[24;40m";          //RTT_CTRL_BG_BLACK //Фон Текста


void LOG_init(void)
{
	strcat(log_str, log_i_s1);
}

void LOG(char * tag, char TYPE, char * text)
{
	char * p;
	p = &log_str[14];

	while(*tag)
	{ *p++=*tag++; }

	*p++ = '>';

	if (TYPE == 'I'){
	  *p++ = log_i_s2[0];	*p++ = log_i_s2[1];	*p++ = log_i_s2[2];	*p++ = log_i_s2[3];	*p++ = log_i_s2[4];	*p++ = log_i_s2[5];	*p++ = log_i_s2[6];
	  *p++ = log_i_s2[7];	*p++ = log_i_s2[8];	*p++ = log_i_s2[9];	*p++ = log_i_s2[10];*p++ = log_i_s2[11];*p++ = log_i_s2[12];*p++ = log_i_s2[13];
	  *p++ = 'I';*p++ = '>';
	  *p++ = log_i_s4[0];	*p++ = log_i_s4[1];	*p++ = log_i_s4[2];	*p++ = log_i_s4[3];	*p++ = log_i_s4[4];	*p++ = log_i_s4[5];	*p++ = log_i_s4[6];*p++ = log_i_s4[7];
	  *p++ = ' ';

	}

	if (TYPE == 'D'){
	  *p++ = log_d_s2[0];	*p++ = log_d_s2[1];	*p++ = log_d_s2[2];	*p++ = log_d_s2[3];	*p++ = log_d_s2[4];	*p++ = log_d_s2[5];	*p++ = log_d_s2[6];
	  *p++ = log_d_s2[7];	*p++ = log_d_s2[8];	*p++ = log_d_s2[9];	*p++ = log_d_s2[10];*p++ = log_d_s2[11];*p++ = log_d_s2[12];*p++ = log_d_s2[13];
	  *p++ = 'D';*p++ = '>';
	  *p++ = log_d_s4[0];	*p++ = log_d_s4[1];	*p++ = log_d_s4[2];	*p++ = log_d_s4[3];	*p++ = log_d_s4[4];	*p++ = log_d_s4[5];	*p++ = log_d_s4[6]; *p++ = log_d_s4[7];
	  *p++ = ' ';
	}

	while(*text)
	{ *p++=*text++;	}

	*p++ = log_reset[0];	*p++ = log_reset[1];	*p++ = log_reset[2];	*p++ = log_reset[3];;
	*p++= '\n';
	*p++= 0; //Конец строки
	SEGGER_RTT_WriteString(0, log_str);
}


