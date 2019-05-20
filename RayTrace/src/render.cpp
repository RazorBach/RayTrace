#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "math.h"
#include "sphere.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const Sphere &sphere) {
	float sphere_dist = std::numeric_limits<float>::max();
	if (!sphere.ray_intersect(orig, dir, sphere_dist)) {
		return Vec3f(0.2, 0.7, 0.8); // background color
	}
	return Vec3f(0.4, 0.4, 0.3);
}

void render(const Sphere &sphere) {
	int width, height, comp, comp2;
	const int fov = M_PI / 2.;
	unsigned char *data = stbi_load("pic/test.png", &width, &height, &comp, STBI_rgb_alpha);
	unsigned char *data2 = stbi_load("pic/out.jpg", &width, &height, &comp2, STBI_rgb);


	std::vector<Vec3f> framebuffer(width*height);

	if(data == nullptr)
		throw(std::string("Failed to load png"));
	printf("%d, %d, %d\n", width, height, comp);
	printf("%d, %d, %d\n", width, height, comp2);

	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			framebuffer[i + j * width] = Vec3f(255 * (float) j / float(height), 255 * (float) i / float(width), 0);
		}
	}

	for (size_t j = 0; j<height; j++) {
		for (size_t i = 0; i<width; i++) {
			float x = (2 * (i + 0.5) / (float)width - 1)*tan(fov / 2.)*width / (float)height;
			float y = -(2 * (j + 0.5) / (float)height - 1)*tan(fov / 2.);
			Vec3f dir = Vec3f(x, y, -1).normalize();
			framebuffer[i + j * width] = cast_ray(Vec3f(0, 0, 0), dir, sphere);
		}
	}

	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			data[j * width * comp + i * comp + 0] = (char)  framebuffer[i + j * width][0];
			data[j * width * comp + i * comp + 1] = (char)  framebuffer[i + j * width][1];
			data[j * width * comp + i * comp + 2] = (char)  framebuffer[i + j * width][2];
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