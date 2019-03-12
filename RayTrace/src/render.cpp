#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "math.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
void testb() {
	int w, h, n;

	//rgba
	//load image
	unsigned char *data = stbi_load("pic/rgb.png", &w, &h, &n, 0);

	printf("%d, %d, %d\n", w, h, n);

	//change pixel

	//rgba,write 10 red pixel at line 11
	for (int dx = 0; dx < 10; ++dx)
	{
		data[n * w * 10 + dx * n + 0] = 255;
		data[n * w * 10 + dx * n + 1] = 0;
		data[n * w * 10 + dx * n + 2] = 0;
		data[n * w * 10 + dx * n + 3] = 255;
	}

	//write image
	stbi_write_png("pic/rgb2.png", w, h, n, data, w * 4);


	stbi_image_free(data);
}

void render() {
	int width, height, comp, comp2;
	unsigned char *data = stbi_load("pic/test.png", &width, &height, &comp, STBI_rgb_alpha);
	unsigned char *data2 = stbi_load("pic/out.jpg", &width, &height, &comp2, STBI_rgb);

	if(data == nullptr)
		throw(std::string("Failed to load png"));
	printf("%d, %d, %d\n", width, height, comp);
	printf("%d, %d, %d\n", width, height, comp2);

	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			data[j * width * comp + i * comp + 0] = (char)(255 *  (float) (j / float(height)));
			data[j * width * comp + i * comp + 1] = (char)(255 * (float) (i / float(width)));
			data[j * width * comp + i * comp + 2] = 0;
			data[j * width * comp + i * comp + 3] = 255;
		}
	}


	//write image
	stbi_write_png("pic/test2.png", width, height, comp, data, width * 4); 
	stbi_image_free(data);

}

int main() {
	render();
	return 0;
}