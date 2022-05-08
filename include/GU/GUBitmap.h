#ifndef _GUBITMAP_H_
#define _GUBITMAP_H_

#include <vector>
#include <fstream>
#include <cinttypes>
#include <iostream>

namespace GU
{
    inline void insert4bytes(std::vector<uint8_t> &dest, const uint32_t &data)
    {
        uint8_t* tmp = (uint8_t*)&data;
        dest.push_back(tmp[0]);
        dest.push_back(tmp[1]);
        dest.push_back(tmp[2]);
        dest.push_back(tmp[3]);
    }

    inline void insert2bytes(std::vector<uint8_t> &dest, const uint16_t &data)
    {
        uint8_t* tmp = (uint8_t*)&data;
        dest.push_back(tmp[0]);
        dest.push_back(tmp[1]);
    }

    inline bool LoadBmp(const char* filename, std::vector<uint8_t> &rgb, int &width, int &height)
    {
        std::ifstream file;
        file.open(filename);

        // Check if file exists
        if(!file.good())
            return false;

        char header[54];
        file.read(header, 54);
        width = *(int*)&header[18];
        height = *(int*)&header[22];

		// Skip offset
		for (int i = 54; i < *(int*)&header[10]; i++)
			file.get();


        int size = 3 * width * height;
		std::vector<char> data;
		unsigned char temp;
		int line = 0;
		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < height; x++)
			{
				temp = file.get();
				data.push_back(temp);
				temp = file.get();
				data.push_back(temp);
				temp = file.get();
				data.push_back(temp);
				line++;
			}
			while (line % 4)
			{
				line++;
				file.get();
			}
		}
        file.close();
		
        for(int y = 0; y < height; y++)
        {
			for (int x = 0; x < width; x++)
			{
				rgb.push_back(data[(height - 1 - y) * (width * 3) + x * 3 + 2]);
				rgb.push_back(data[(height - 1 - y) * (width * 3) + x * 3 + 1]);
				rgb.push_back(data[(height - 1 - y) * (width * 3) + x * 3 + 0]);
			}
        }

        return true;
    }

	inline int SaveBmp(const char* filename, std::vector<uint8_t> &rgb, int width, int height)
	{
		std::vector<uint8_t> data;
		// magic number BM
		data.push_back(0x42);
		data.push_back(0x4D);
		size_t fileSizeOffset = data.size();

		// size (fill later)
		insert4bytes(data, 0xFFFFFFFF);

		// reserved (default 0)
		data.push_back(0x00);
		data.push_back(0x00);
		data.push_back(0x00);
		data.push_back(0x00);
		size_t pixelOffset = data.size();

		// offset (fill later)
		insert4bytes(data, 0);

		// BITMAPINFOHEADER        
		insert4bytes(data, 40);         // header size
		insert4bytes(data, width);      // width
		insert4bytes(data, height);     // height
		insert2bytes(data, 1);          // color planes
		insert2bytes(data, 24);         // bits per pixel
		insert4bytes(data, 0);          // no compression
		size_t rawPixelOffset = data.size();

		insert4bytes(data, 0);          // raw data size, fill later
		insert4bytes(data, 2835);       // horizontal resolution
		insert4bytes(data, 2835);       // vertical resolution
		insert4bytes(data, 0);          // number of colors
		insert4bytes(data, 0);          // important colors

		uint32_t dataSize = data.size();
		memcpy(&data[pixelOffset], &dataSize, 4);
		uint32_t headerSize = data.size();

		for (uint_fast32_t y = 0; y < height; ++y)
		{
			for (uint_fast32_t x = 0; x < width; ++x)
			{
				uint8_t b = rgb.at((height - 1 - y) * (width * 3) + x * 3 + 2);
				uint8_t g = rgb.at((height - 1 - y) * (width * 3) + x * 3 + 1);
				uint8_t r = rgb.at((height - 1 - y) * (width * 3) + x * 3 + 0);
				data.push_back(b);
				data.push_back(g);
				data.push_back(r);
			}
			while ((data.size() - headerSize) % 4)
			{
				data.push_back(0);
			}
		}

		uint32_t fileSize = data.size();
		memcpy(&data[fileSizeOffset], &fileSize, 4);

		uint32_t pixelSize = data.size() - headerSize;
		memcpy(&data[rawPixelOffset], &pixelSize, 4);

		uint8_t *output = new uint8_t[data.size()];
		memcpy(output, &data[0], data.size());
		std::ofstream file;
		file.open(filename, std::ofstream::binary);
		int counter = 0;
		size_t size = sizeof(data);
		for (std::vector<uint8_t>::iterator it = data.begin(); it != data.end(); it++)
		{
			file << (uint8_t)*it;
			counter += sizeof(*it);
		}
		file.close();

		delete[] output;

        return 0;
    }
}

#endif