#include <stdlib.h>

#include <TFT.h>

const uint32_t _acon[] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x11101010, 0x5C595959, 0x9E9B9B9B, 0xCFCCCCCC, 0xEEECECEC, 0xFDF9F9F9, 0xFDF9F9F9, 0xEEECECEC, 0xCFCCCCCC, 0x9E9B9B9B, 0x5D595959, 
        0x11101010, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x28262626, 0xA09D9D9D, 0xF7F5F5F5, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFDFEFD, 0xFFE3F0E3, 0xFFD1E7D1, 0xFFD1E7D1, 0xFFE3F0E3, 0xFFFDFEFD, 0xFFFFFFFF, 0xFFFFFFFF, 
        0xF7F5F5F5, 0xA09D9D9D, 0x28272727, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0A0A0A0A, 0x8F8C8C8C, 0xFBF9F9F9, 0xFFFFFFFF, 0xFFE5F1E5, 0xFF8BCB8A, 0xFF43B93F, 0xFF11AF0A, 0xFF08B500, 0xFF08BA00, 0xFF08BA00, 0xFF08B500, 0xFF10AF0A, 0xFF43B93F, 0xFF8BCB8A, 
        0xFFE5F1E5, 0xFFFFFFFF, 0xFBF9F9F9, 0x908C8C8C, 0x0B0B0B0B, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x26242424, 0xD5D2D2D2, 0xFFFFFFFF, 0xFFE5F1E5, 0xFF64BA62, 0xFF0BA605, 0xFF07B300, 0xFF07B300, 0xFF07B300, 0xFF07B300, 0xFF07B300, 0xFF07B300, 0xFF07B300, 0xFF07B300, 0xFF07B300, 0xFF07B300, 
        0xFF0AA505, 0xFF63BA62, 0xFFE5F1E5, 0xFFFFFFFF, 0xD6D2D2D2, 0x27252525, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x33313131, 0xECE9E9E9, 0xFFFFFFFF, 0xFFA3D1A3, 0xFF129B0F, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 0xFF05A300, 
        0xFF05A300, 0xFF05A300, 0xFF129B0F, 0xFFA3D1A2, 0xFFFFFFFF, 0xECE9E9E9, 0x33323232, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x26252525, 0xECE9E9E9, 0xFFFEFFFE, 0xFF77BB76, 0xFF038E00, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 0xFF039200, 
        0xFF039200, 0xFF039200, 0xFF039200, 0xFF038E00, 0xFF76BA76, 0xFFFEFFFE, 0xECE9E9E9, 0x27252525, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x0B0A0A0A, 0xD6D2D2D2, 0xFFFFFFFF, 0xFF76B976, 0xFF018100, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 
        0xFF018200, 0xFF018200, 0xFF018200, 0xFF018200, 0xFF018100, 0xFF76B876, 0xFFFFFFFF, 0xD6D2D2D2, 0x0B0B0B0B, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x8F8C8C8C, 0xFFFFFFFF, 0xFFA3CFA3, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF379937, 0xFF389938, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 
        0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFFA2CFA2, 0xFFFFFFFF, 0x908C8C8C, 0x00000000, 0x00000000,
  0x00000000, 0x28262626, 0xFBF9F9F9, 0xFFE5F1E5, 0xFF0F840F, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF158715, 0xFFFBFDFB, 0xFFFBFDFB, 0xFF168816, 0xFF007D00, 0xFF007D00, 0xFF007D00, 
        0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF0E840E, 0xFFE4F1E4, 0xFBFAFAFA, 0x28272727, 0x00000000,
  0x00000000, 0xA09D9D9D, 0xFFFFFFFF, 0xFF62AE62, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF248E24, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF248F24, 0xFF007D00, 0xFF007D00, 0xFF007D00, 
        0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF62AE62, 0xFFFFFFFF, 0xA19D9D9D, 0x00000000,
  0x11101010, 0xF7F5F5F5, 0xFFE5F1E5, 0xFF057F05, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF017D01, 0xFF017D01, 0xFF007D00, 0xFF248E24, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF248F24, 0xFF007D00, 0xFF017D01, 0xFF007D00, 
        0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF057F05, 0xFFE4F1E4, 0xF7F5F5F5, 0x11101010,
  0x5C595959, 0xFFFFFFFF, 0xFF8AC38A, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF218E21, 0xFFD7EAD7, 0xFFD7EAD7, 0xFF0A8309, 0xFF249124, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF249124, 0xFF0A8309, 0xFFD7EAD7, 0xFFD7EAD7, 
        0xFF228E22, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF89C289, 0xFFFFFFFF, 0x5D595959,
  0x9E9B9B9B, 0xFFFFFFFF, 0xFF3F9C3F, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF0D830D, 0xFFD9EBD9, 0xFFFFFFFF, 0xFFF6FAF6, 0xFF148E13, 0xFF259624, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF259624, 0xFF138D12, 0xFFF6FAF6, 0xFFFFFFFF, 
        0xFFD9EBD9, 0xFF0D840D, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF3F9C3F, 0xFFFFFFFF, 0x9F9C9C9C,
  0xCFCCCCCC, 0xFFFDFEFD, 0xFF0A820A, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007E00, 0xFF8BC48B, 0xFFFFFFFF, 0xFFF9FCF9, 0xFF43A742, 0xFF028B00, 0xFF259B24, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF269C24, 0xFF028B00, 0xFF43A741, 0xFFF9FCF9, 
        0xFFFFFFFF, 0xFF8BC48B, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF0A820A, 0xFFFDFEFD, 0xCFCCCCCC,
  0xEEECECEC, 0xFFE3F0E3, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007E00, 0xFF0A8609, 0xFFF2F8F2, 0xFFFFFFFF, 0xFF82C782, 0xFF028F00, 0xFF039100, 0xFF26A124, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF27A124, 0xFF039100, 0xFF028F00, 0xFF82C681, 
        0xFFFFFFFF, 0xFFF2F8F2, 0xFF0A850A, 0xFF007E00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFFE3F0E3, 0xEFEDEDED,
  0xFDF9F9F9, 0xFFD1E7D1, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF018100, 0xFF43A442, 0xFFFFFFFF, 0xFFFEFEFE, 0xFF1A9C18, 0xFF039400, 0xFF039700, 0xFF27A624, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF28A624, 0xFF039700, 0xFF039400, 0xFF1A9B17, 
        0xFFFEFEFE, 0xFFFFFFFF, 0xFF44A443, 0xFF018100, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFFD1E7D1, 0xFEF9F9F9,
  0xFDF9F9F9, 0xFFD1E7D1, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF008000, 0xFF018500, 0xFF65B764, 0xFFFFFFFF, 0xFFE5F3E5, 0xFF039700, 0xFF049A00, 0xFF049D00, 0xFF27AB23, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF27AB23, 0xFF049C00, 0xFF049A00, 0xFF039600, 
        0xFFE4F3E4, 0xFFFFFFFF, 0xFF65B764, 0xFF018500, 0xFF008000, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFFD1E7D1, 0xFEF9F9F9,
  0xEEECECEC, 0xFFE3F0E3, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFF007E00, 0xFF018400, 0xFF028900, 0xFF64B863, 0xFFFFFFFF, 0xFFE7F5E6, 0xFF049C00, 0xFF059F00, 0xFF05A200, 0xFF0BA606, 0xFFC1E9C0, 0xFFC1E9C0, 0xFF0BA606, 0xFF05A200, 0xFF059F00, 0xFF049B00, 
        0xFFE6F4E6, 0xFFFFFFFF, 0xFF64B863, 0xFF028800, 0xFF018300, 0xFF007E00, 0xFF007D00, 0xFF007D00, 0xFF007D00, 0xFFE3F0E3, 0xEFEDEDED,
  0xCFCCCCCC, 0xFFFDFEFD, 0xFF0A820A, 0xFF007D00, 0xFF007D00, 0xFF018100, 0xFF018600, 0xFF028C00, 0xFF40AB3E, 0xFFFFFFFF, 0xFFFEFFFE, 0xFF21AB1D, 0xFF05A400, 0xFF06A800, 0xFF06AA00, 0xFF06AC00, 0xFF06AC00, 0xFF06AA00, 0xFF06A800, 0xFF05A400, 0xFF1EA91A, 
        0xFFFEFFFE, 0xFFFFFFFF, 0xFF41AB3F, 0xFF028B00, 0xFF018600, 0xFF008000, 0xFF007D00, 0xFF007D00, 0xFF0A820A, 0xFFFDFEFD, 0xCFCCCCCC,
  0x9E9B9B9B, 0xFFFFFFFF, 0xFF3F9C3F, 0xFF007D00, 0xFF007E00, 0xFF018300, 0xFF028900, 0xFF028F00, 0xFF099707, 0xFFEDF7ED, 0xFFFFFFFF, 0xFF8FD68D, 0xFF06A900, 0xFF07AD00, 0xFF07B000, 0xFF07B200, 0xFF07B200, 0xFF07B000, 0xFF06AD00, 0xFF06A900, 0xFF87D385, 
        0xFFFFFFFF, 0xFFEEF8ED, 0xFF0A9607, 0xFF028E00, 0xFF018800, 0xFF018200, 0xFF007D00, 0xFF007D00, 0xFF3F9C3F, 0xFFFFFFFF, 0x9F9C9C9C,
  0x5C595959, 0xFFFFFFFF, 0xFF8AC38A, 0xFF007D00, 0xFF007F00, 0xFF018400, 0xFF028B00, 0xFF039000, 0xFF039700, 0xFF81CD7F, 0xFFFFFFFF, 0xFFFCFEFC, 0xFF56C752, 0xFF07B200, 0xFF08B600, 0xFF08B800, 0xFF08B800, 0xFF08B500, 0xFF07B100, 0xFF4BC347, 0xFFFAFDFA, 
        0xFFFFFFFF, 0xFF82CD81, 0xFF039600, 0xFF039000, 0xFF028A00, 0xFF018400, 0xFF007E00, 0xFF007D00, 0xFF89C289, 0xFFFFFFFF, 0x5D595959,
  0x11101010, 0xF7F5F5F5, 0xFFE5F1E5, 0xFF057F05, 0xFF007F00, 0xFF018600, 0xFF028C00, 0xFF039200, 0xFF049800, 0xFF0CA108, 0xFFCFEDCE, 0xFFFFFFFF, 0xFFFCFEFC, 0xFF94DF91, 0xFF2AC424, 0xFF09BE00, 0xFF09BE00, 0xFF28C221, 0xFF8DDC8A, 0xFFFAFDFA, 0xFFFFFFFF, 
        0xFFD0EDCF, 0xFF0CA009, 0xFF049700, 0xFF039100, 0xFF028B00, 0xFF018500, 0xFF007F00, 0xFF057F05, 0xFFE4F1E4, 0xF7F5F5F5, 0x11101010,
  0x00000000, 0xA09D9D9D, 0xFFFFFFFF, 0xFF62AE62, 0xFF008000, 0xFF018600, 0xFF028C00, 0xFF039300, 0xFF049900, 0xFF059F00, 0xFF1CAD18, 0xFFCDEECD, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFF0FBEF, 0xFFEFFBEF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFCFEECE, 
        0xFF1DAC19, 0xFF049E00, 0xFF049800, 0xFF039200, 0xFF028B00, 0xFF018500, 0xFF007F00, 0xFF62AE62, 0xFFFFFFFF, 0xA19D9D9D, 0x00000000,
  0x00000000, 0x28262626, 0xFBF9F9F9, 0xFFE5F1E5, 0xFF0F870F, 0xFF018600, 0xFF028C00, 0xFF039200, 0xFF049900, 0xFF059F00, 0xFF05A500, 0xFF0DAD07, 0xFF7ED67B, 0xFFE9F8E9, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFEAF8E9, 0xFF7FD67C, 0xFF0DAC08, 
        0xFF05A400, 0xFF049E00, 0xFF049800, 0xFF039200, 0xFF028B00, 0xFF018500, 0xFF0E860E, 0xFFE4F1E4, 0xFBFAFAFA, 0x28272727, 0x00000000,
  0x00000000, 0x00000000, 0x8F8C8C8C, 0xFFFFFFFF, 0xFFA3D1A3, 0xFF018500, 0xFF028B00, 0xFF039200, 0xFF049800, 0xFF049E00, 0xFF05A400, 0xFF06AA00, 0xFF07AF00, 0xFF0BB604, 0xFF3CC736, 0xFF5ED359, 0xFF5ED259, 0xFF3CC737, 0xFF0BB504, 0xFF07AE00, 0xFF06A900, 
        0xFF05A300, 0xFF049D00, 0xFF049700, 0xFF039100, 0xFF028B00, 0xFF018500, 0xFFA2D0A2, 0xFFFFFFFF, 0x908D8D8D, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x0B0A0A0A, 0xD6D2D2D2, 0xFFFFFFFF, 0xFF77BD76, 0xFF028A00, 0xFF039000, 0xFF039600, 0xFF049C00, 0xFF05A100, 0xFF06A700, 0xFF06AC00, 0xFF07B000, 0xFF07B400, 0xFF08B600, 0xFF08B600, 0xFF07B400, 0xFF07B000, 0xFF06AB00, 0xFF06A600, 
        0xFF05A100, 0xFF049B00, 0xFF039500, 0xFF028F00, 0xFF028900, 0xFF76BC76, 0xFFFFFFFF, 0xD6D2D2D2, 0x0B0B0B0B, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x26252525, 0xECE9E9E9, 0xFFFEFFFE, 0xFF77BF76, 0xFF028E00, 0xFF039400, 0xFF049900, 0xFF059E00, 0xFF05A300, 0xFF06A800, 0xFF06AC00, 0xFF07AE00, 0xFF07B000, 0xFF07B000, 0xFF07AE00, 0xFF06AB00, 0xFF06A700, 0xFF05A300, 
        0xFF049E00, 0xFF049800, 0xFF039300, 0xFF028D00, 0xFF77BE76, 0xFFFEFFFE, 0xECE9E9E9, 0x27252525, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x33313131, 0xECE9E9E9, 0xFFFFFFFF, 0xFFA3D5A3, 0xFF11970F, 0xFF039600, 0xFF049A00, 0xFF059F00, 0xFF05A300, 0xFF06A600, 0xFF06A900, 0xFF06AA00, 0xFF06AA00, 0xFF06A800, 0xFF06A600, 0xFF05A200, 0xFF059E00, 
        0xFF049A00, 0xFF039500, 0xFF11960F, 0xFFA3D5A2, 0xFFFFFFFF, 0xECE9E9E9, 0x33323232, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x26242424, 0xD5D2D2D2, 0xFFFFFFFF, 0xFFE5F3E5, 0xFF64BC62, 0xFF099805, 0xFF049A00, 0xFF049E00, 0xFF05A100, 0xFF05A300, 0xFF05A400, 0xFF05A400, 0xFF05A300, 0xFF05A000, 0xFF049D00, 0xFF049A00, 
        0xFF089805, 0xFF64BB62, 0xFFE5F3E5, 0xFFFFFFFF, 0xD6D2D2D2, 0x27252525, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0A0A0A0A, 0x8F8C8C8C, 0xFBF9F9F9, 0xFFFFFFFF, 0xFFE5F4E5, 0xFF8BCF8A, 0xFF42B23F, 0xFF0E9F0A, 0xFF049D00, 0xFF049E00, 0xFF049E00, 0xFF049D00, 0xFF0E9E0A, 0xFF42B13F, 0xFF8BCE8A, 
        0xFFE5F4E5, 0xFFFFFFFF, 0xFBF9F9F9, 0x908C8C8C, 0x0B0B0B0B, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x28262626, 0xA09D9D9D, 0xF7F5F5F5, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFDFEFD, 0xFFE4F3E3, 0xFFD2ECD1, 0xFFD2ECD1, 0xFFE4F3E3, 0xFFFDFEFD, 0xFFFFFFFF, 0xFFFFFFFF, 
        0xF7F5F5F5, 0xA09D9D9D, 0x28272727, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x11101010, 0x5C595959, 0x9E9B9B9B, 0xCFCCCCCC, 0xEEECECEC, 0xFDF9F9F9, 0xFDF9F9F9, 0xEEECECEC, 0xCFCCCCCC, 0x9E9B9B9B, 0x5C595959, 
        0x11101010, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

Bitmap bmp_on_3232 = { 32, // xSize
		32, // ySize
		NULL, // steam8
		NULL,
		NULL, 32, (uint32_t *)_acon[0] };
