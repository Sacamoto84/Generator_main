#include "Page.h"
#include "global_define.h"
#include "stdio.h"

void generator_pre_CH1_FR(uint32_t index) {

	uint32_t temp;

	if (menu_generator.field.encoder_block) {

		///////////////////////////////////////
		if (index == INDEX_CH1_FR) //CH1 Carrier Fr
		{
			temp = Gen.CH1.Carrier_fr;
			if (Encoder.Left) {
				Encoder.Left = 0;
				temp -= 100;
				if (temp < 200)
					temp = 200;
				Gen.CH1.Carrier_fr = temp;

#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				temp += 100;
				if (temp > 10000)
					temp = 10000;
				Gen.CH1.Carrier_fr = temp;

#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif

			}
			sprintf(item_generator[INDEX_CH1_FR].text, "* %d *",
					Gen.CH1.Carrier_fr);

		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH1_FR].text, " %d Hz",
				Gen.CH1.Carrier_fr);
	}

}

void generator_pre_CH2_FR(uint32_t index) {

	uint32_t temp;
	float tempf;

	if (menu_generator.field.encoder_block) {

		if (index == INDEX_CH2_FR) //CH2 Carrier Fr
		{
			temp = Gen.CH2.Carrier_fr;
			if (Encoder.Left) {
				Encoder.Left = 0;
				temp -= 100;
				if (temp < 200)
					temp = 200;
				Gen.CH2.Carrier_fr = temp;
#ifdef USE_CLI
						sendStructCHtoHost(1);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				temp += 100;
				if (temp > 4000)
					temp = 4000;
				Gen.CH2.Carrier_fr = temp;
#ifdef USE_CLI
						sendStructCHtoHost(1);
#endif
			}
			sprintf(item_generator[INDEX_CH2_FR].text, "* %d *",
					Gen.CH2.Carrier_fr);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH2_FR].text, " %d Hz",
				Gen.CH2.Carrier_fr);
	}

}

void generator_pre_CH1_AM_FR(uint32_t index) {

	float tempf;

	if (menu_generator.field.encoder_block) {

		///////////////////////////////////////
		if (index == INDEX_CH1_AM_FR) //CH1 AM Fr
		{
			tempf = Gen.CH1.AM_fr;

			if (Encoder.Left) {
				Encoder.Left = 0;

				if (tempf <= 10.0F)
					tempf -= 0.1F;
				else
					tempf -= 1.0F;

				if (tempf < 0.1F)
					tempf = 0.1F;

				Gen.CH1.AM_fr = tempf;
#ifdef USE_CLI
				sendStructCHtoHost(0);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;

				if (tempf < 10.0F)
					tempf += 0.1F;
				else
					tempf += 1.0F;

				if (tempf > 100.0F)
					tempf = 100.0F;

				Gen.CH1.AM_fr = tempf;
#ifdef USE_CLI
				sendStructCHtoHost(0);
#endif
			}
			sprintf(item_generator[INDEX_CH1_AM_FR].text, "> %.1f Hz <",
					Gen.CH1.AM_fr);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH1_AM_FR].text, " %.1f Hz",
				Gen.CH1.AM_fr);
	}

}

void generator_pre_CH2_AM_FR(uint32_t index) {

	float tempf;

	if (menu_generator.field.encoder_block) {

		///////////////////////////////////////
		if (index == INDEX_CH2_AM_FR) //CH1 AM Fr
		{
			tempf = Gen.CH2.AM_fr;

			if (Encoder.Left) {
				Encoder.Left = 0;

				if (tempf <= 10.0F)
					tempf -= 0.1F;
				else
					tempf -= 1.0F;

				if (tempf < 0.1F)
					tempf = 0.1F;

				Gen.CH2.AM_fr = tempf;
#ifdef USE_CLI
				sendStructCHtoHost(0);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;

				if (tempf < 10.0F)
					tempf += 0.1F;
				else
					tempf += 1.0F;

				if (tempf > 100.0F)
					tempf = 100.0F;

				Gen.CH2.AM_fr = tempf;
#ifdef USE_CLI
				sendStructCHtoHost(0);
#endif
			}
			sprintf(item_generator[INDEX_CH2_AM_FR].text, "> %.1f Hz <",
					Gen.CH2.AM_fr);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH2_AM_FR].text, " %.1f Hz",
				Gen.CH2.AM_fr);
	}

}

void generator_pre_CH1_FM_BASE(uint32_t index) {

	uint32_t temp;

	if (menu_generator.field.encoder_block) {

		if (index == INDEX_CH1_FM_BASE) //CH1 FM Base
		{
			if (Encoder.Left) {
				Encoder.Left = 0;
				temp = Gen.CH1.FM_Base;
				temp -= 100;
				if (temp < 200)
					temp = 200;
				Gen.CH1.FM_Base = temp;
#ifdef USE_CLI
			sendStructCHtoHost(0);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				temp = Gen.CH1.FM_Base;
				temp += 100;
				if (temp > 5000)
					temp = 5000;
				Gen.CH1.FM_Base = temp;
#ifdef USE_CLI
			sendStructCHtoHost(0);
#endif
			}
			sprintf(item_generator[INDEX_CH1_FM_BASE].text, " Base * %d *",
					Gen.CH1.FM_Base);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH1_FM_BASE].text, " Base %d Hz",
				Gen.CH1.FM_Base);
	}
}

void generator_pre_CH2_FM_BASE(uint32_t index) {

	uint32_t temp;

	if (menu_generator.field.encoder_block) {

		if (index == INDEX_CH2_FM_BASE) //CH1 FM Base
		{
			if (Encoder.Left) {
				Encoder.Left = 0;
				temp = Gen.CH2.FM_Base;
				temp -= 100;
				if (temp < 200)
					temp = 200;
				Gen.CH2.FM_Base = temp;
#ifdef USE_CLI
			sendStructCHtoHost(0);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				temp = Gen.CH2.FM_Base;
				temp += 100;
				if (temp > 5000)
					temp = 5000;
				Gen.CH2.FM_Base = temp;
#ifdef USE_CLI
			sendStructCHtoHost(0);
#endif
			}
			sprintf(item_generator[INDEX_CH1_FM_BASE].text, " Base * %d *",
					Gen.CH2.FM_Base);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH1_FM_BASE].text, " Base %d Hz",
				Gen.CH2.FM_Base);
	}
}

void generator_pre_CH1_FM_DEV(uint32_t index) {

	uint32_t temp;

	if (menu_generator.field.encoder_block) {
		if (index == INDEX_CH1_FM_DEV) //CH1 FM Dev
		{
			if (Encoder.Left) {
				Encoder.Left = 0;
				temp = Gen.CH1.FM_Dev;
				temp -= 100;
				if (temp < 200)
					temp = 200;
				Gen.CH1.FM_Dev = temp;
#ifdef USE_CLI
						sendStructCHtoHost(0);
	#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				temp = Gen.CH1.FM_Dev;
				temp += 100;
				if (temp > 5000)
					temp = 5000;
				Gen.CH1.FM_Dev = temp;
#ifdef USE_CLI
						sendStructCHtoHost(0);
	#endif
			}
			sprintf(item_generator[INDEX_CH1_FM_DEV].text, " Dev * %d *",
					Gen.CH1.FM_Dev);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH1_FM_DEV].text, " Dev   %d Hz",
				Gen.CH1.FM_Dev);
	}

}

void generator_pre_CH2_FM_DEV(uint32_t index) {

	uint32_t temp;

	if (menu_generator.field.encoder_block) {
		if (index == INDEX_CH2_FM_DEV) //CH1 FM Dev
		{
			if (Encoder.Left) {
				Encoder.Left = 0;
				temp = Gen.CH2.FM_Dev;
				temp -= 100;
				if (temp < 200)
					temp = 200;
				Gen.CH2.FM_Dev = temp;
#ifdef USE_CLI
						sendStructCHtoHost(0);
	#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				temp = Gen.CH2.FM_Dev;
				temp += 100;
				if (temp > 5000)
					temp = 5000;
				Gen.CH2.FM_Dev = temp;
#ifdef USE_CLI
						sendStructCHtoHost(0);
	#endif
			}
			sprintf(item_generator[INDEX_CH2_FM_DEV].text, " Dev * %d *",
					Gen.CH2.FM_Dev);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH2_FM_DEV].text, " Dev   %d Hz",
				Gen.CH2.FM_Dev);
	}
}

void generator_pre_CH1_FM_FR(uint32_t index) {

	float tempf;

	if (menu_generator.field.encoder_block) {

		if (index == INDEX_CH1_FM_FR) //CH1 FM_mod_fr
		{
			tempf = Gen.CH1.FM_mod_fr;

			if (Encoder.Left) {
				Encoder.Left = 0;
				if (tempf <= 10.0F)
					tempf -= 0.1F;
				else
					tempf -= 1.0F;
				if (tempf < 0.1F)
					tempf = 0.1F;
				Gen.CH1.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				if (tempf < 10.0F)
					tempf += 0.1F;
				else
					tempf += 1.0F;
				if (tempf > 100.0F)
					tempf = 100.0F;
				Gen.CH1.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
			}
			sprintf(item_generator[INDEX_CH1_FM_FR].text, "> %.1f Hz <",
					Gen.CH1.FM_mod_fr);
		}

		menu_generator.field.needUpdate = 1;

	} else {
		sprintf(item_generator[INDEX_CH1_FM_FR].text, " %.1f Hz",
				Gen.CH1.FM_mod_fr);
	}
}

void generator_pre_CH2_FM_FR(uint32_t index) {

	float tempf;

	if (menu_generator.field.encoder_block) {

		if (index == INDEX_CH2_FM_FR) //CH1 FM_mod_fr
		{
			tempf = Gen.CH2.FM_mod_fr;

			if (Encoder.Left) {
				Encoder.Left = 0;
				if (tempf <= 10.0F)
					tempf -= 0.1F;
				else
					tempf -= 1.0F;
				if (tempf < 0.1F)
					tempf = 0.1F;
				Gen.CH2.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
			}

			if (Encoder.Right) {
				Encoder.Right = 0;
				if (tempf < 10.0F)
					tempf += 0.1F;
				else
					tempf += 1.0F;
				if (tempf > 100.0F)
					tempf = 100.0F;
				Gen.CH2.FM_mod_fr = tempf;
#ifdef USE_CLI
					sendStructCHtoHost(0);
#endif
			}
			sprintf(item_generator[INDEX_CH1_FM_FR].text, "> %.1f Hz <",
					Gen.CH2.FM_mod_fr);
		}
		menu_generator.field.needUpdate = 1;
	} else {
		sprintf(item_generator[INDEX_CH1_FM_FR].text, " %.1f Hz",
				Gen.CH2.FM_mod_fr);
	}
}

void generator_pre_CH1_EN(uint32_t index)
{
	if (Gen.CH1.CH_EN)
	  sprintf(item_generator[INDEX_CH1_EN].text,"CH1 [  Вкл  ]");
	else
	  sprintf(item_generator[INDEX_CH1_EN].text,"CH1 [ Откл ]");

}

void generator_pre_CH2_EN(uint32_t index)
{
	if (Gen.CH2.CH_EN)
	  sprintf(item_generator[INDEX_CH2_EN].text,"CH2 [  Вкл  ]");
	else
	  sprintf(item_generator[INDEX_CH2_EN].text,"CH2 [ Откл ]");

}

void generator_pre_CH1_AM_EN(uint32_t index)
{
	if (Gen.CH1.AM_EN)
	  sprintf(item_generator[INDEX_CH1_AM_EN].text,"AM [  Вкл  ]");
	else
	  sprintf(item_generator[INDEX_CH1_AM_EN].text,"AM [ Откл ]");
}

void generator_pre_CH2_AM_EN(uint32_t index)
{
	if (Gen.CH2.AM_EN)
	  sprintf(item_generator[INDEX_CH2_AM_EN].text,"AM [  Вкл  ]");
	else
	  sprintf(item_generator[INDEX_CH2_AM_EN].text,"AM [ Откл ]");
}

void generator_pre_CH1_FM_EN(uint32_t index)
{
	if (Gen.CH1.FM_EN)
	  sprintf(item_generator[INDEX_CH1_FM_EN].text,"FM [  Вкл  ]");
	else
	  sprintf(item_generator[INDEX_CH1_FM_EN].text,"FM [ Откл ]");
}

void generator_pre_CH2_FM_EN(uint32_t index)
{
	if (Gen.CH2.FM_EN)
	  sprintf(item_generator[INDEX_CH2_FM_EN].text,"FM [  Вкл  ]");
	else
	  sprintf(item_generator[INDEX_CH2_FM_EN].text,"FM [ Откл ]");
}
