#include "gd.h"

#include <string>
#include <iostream> // Console and streams output
#include <stdio.h> // File output

int main() {
	FILE* outpng, * outjpeg;

	gdImagePtr image = NULL;

	int devider = 2;
	std::string filename;

	std::cout << "Filename: ";
	std::cin >> filename;
	std::cout << std::endl;

	std::cout << "Devider: ";
	std::cin >> devider;
	std::cout << std::endl;
	
	const std::string extension = filename.substr(filename.find_last_of('.') + 1);

	FILE* in = fopen(filename.c_str(), "rb");
	if (in == NULL) {
		std::cout << "File does not exist" << std::endl;
		return 0;
	}
	if(extension == "png") {
		image = gdImageCreateFromPng(in);
	}
	else if(extension == "jpg") {
		image = gdImageCreateFromJpeg(in);
	}

	int newW = gdImageSX(image) / devider;
	int newH = gdImageSY(image) / devider;
	gdImagePtr cimage = gdImageCreateTrueColor(newW, newH);

	gdImageCopyResampled(cimage, image, 0, 0, 0, 0, newW, newH, gdImageSX(image), gdImageSY(image));

	gdImagePtr huge = gdImageCreateTrueColor(gdImageSX(image), gdImageSY(image));

	gdImageCopyResampled(huge, cimage, 0, 0, 0, 0, gdImageSX(huge), gdImageSY(huge), newW, newH);

	std::string symbs = "@MNHQ$OC?7>!:-;. ";
	for (int i = 0; i < gdImageSY(cimage); ++i) {
		for(int j = 0; j < gdImageSX(cimage); ++j) {
			int color = gdImageGetTrueColorPixel(cimage, j, i);
			int red = gdTrueColorGetRed(color), blue = gdTrueColorGetBlue(color), green = gdTrueColorGetGreen(color);
			float brightness = 0.2126 * red / 255 + 0.7152 * green / 255 + 0.0722 * blue / 255;

			//std::cout << brightness / 255 * symbs.length() << " ";

			std::cout << symbs[symbs.length() - (brightness * symbs.length())];
		}
		std::cout << std::endl;
	}

	outpng = fopen("out.png", "wb");
	outjpeg = fopen("out.jpg", "wb");

	gdImagePng(huge, outpng);
	gdImageJpeg(huge, outjpeg, -1);

	fclose(outpng);
	fclose(outjpeg);

	gdImageDestroy(image);
	gdImageDestroy(cimage);
	gdImageDestroy(huge);
}