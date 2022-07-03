#include "Page.h"
#include "global_define.h"
#include "stdio.h"

void PAGE_Setting(void)
{
  PAGE_Menu(&menu_setting , &item_setting[0], 8);
}

void setting_save_click(void)
{
  item_setting[1].gif->command(PLAY); //Команда запуска анимации
}
