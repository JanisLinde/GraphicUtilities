#ifndef _GUTARGA_H_
#define _GUTARGA_H_

#include <vector>
#include <fstream>

namespace GU
{
    struct TGAHeader
    {
        unsigned char data1[12];
        unsigned short width;
        unsigned short height;
        unsigned char bpp;
        unsigned char data2;
    };

    inline bool LoadTga(const char* filename, std::vector<uint8_t> &rgb, int &width, int &height, int& bpp)
    {
        TGAHeader tgaHeader;
        unsigned char* targaData = nullptr;
        unsigned char* rawTgaData = nullptr;
        int imageSize, i, j, k;

        FILE* filePtr;
        int error = fopen_s(&filePtr, filename, "rb");
        if(error != 0)
            return false;

        unsigned int count = (unsigned int)fread(&tgaHeader, sizeof(TGAHeader), 1, filePtr);
        if (count != 1)
            return false;

        height = (int)tgaHeader.height;
	    width = (int)tgaHeader.width;
	    bpp = (int)tgaHeader.bpp;

        if(bpp == 32)
        {
            imageSize = width * height * 4;
            rawTgaData = new unsigned char[imageSize];
            if(!rawTgaData)
                return false;

            count = (unsigned int)fread(rawTgaData, 1, imageSize, filePtr);
	        if (count != imageSize)
            {
                return false;
            }
            error = fclose(filePtr);
            
            targaData = new unsigned char[imageSize];
            if (!targaData)
            {
                return false;
            }

            k = (width * height * 4) - (width * 4);

		    unsigned char tmp;
            for (j = 0; j < height; j++)
            {
                for (i = 0; i < width; i++)
                {
                    tmp = rawTgaData[k + 2];  // Red.
                    rgb.push_back(tmp);
                    tmp = rawTgaData[k + 1];  // Green.
                    rgb.push_back(tmp);
                    tmp = rawTgaData[k + 0];  // Blue
                    rgb.push_back(tmp);
                    tmp = rawTgaData[k + 3];  // Alpha
                    rgb.push_back(tmp);

                    k += 4;
                }
                k -= (width * 8);
            }

            delete[] rawTgaData;
            rawTgaData = 0;
        }
        else if(bpp == 24)
        {
            imageSize = width * height * 3;
            rawTgaData = new unsigned char[imageSize];
            if(!rawTgaData)
                return false;

            count = (unsigned int)fread(rawTgaData, 1, imageSize, filePtr);
	        if (count != imageSize)
            {
                return false;
            }
            error = fclose(filePtr);
            
            targaData = new unsigned char[imageSize];
            if (!targaData)
            {
                return false;
            }

            k = (width * height * 3) - (width * 3);

		    unsigned char tmp;
            for (j = 0; j < height; j++)
            {
                for (i = 0; i < width; i++)
                {
                    tmp = rawTgaData[k + 2];  // Red.
                    rgb.push_back(tmp);
                    tmp = rawTgaData[k + 1];  // Green.
                    rgb.push_back(tmp);
                    tmp = rawTgaData[k + 0];  // Blue
                    rgb.push_back(tmp);

                    k += 3;
                }
                k -= (width * 6);
            }

            delete[] rawTgaData;
            rawTgaData = 0;
        }
        else
        {
            return false;
        }
        

        return true;
    }
}

#endif