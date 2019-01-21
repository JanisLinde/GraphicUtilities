#include <Math3D.h>
#include <BMPLoader.h>

int main()
{
	uint8_t data2[3 * 512 * 512];
	srand(3245325346);
	for (int i = 0; i < 3 * 512 * 512; i+=3)
	{
		if (rand() % 2)
		{
			data2[i + 0] = 0x00;
			data2[i + 1] = 0x00;
			data2[i + 2] = 0x00;
		}
		else
		{
			data2[i + 0] = 0xFF;
			data2[i + 1] = 0xFF;
			data2[i + 2] = 0xFF;
		}
	}

	GraphUtil::SaveBMP("test.bmp", data2, 512, 512);
	return 0; 
}