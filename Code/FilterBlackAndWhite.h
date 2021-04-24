#include "Image.h"
#include "Filter.h"
#include "Array.h"

#ifndef FILTER_BLACK_AND_WHITE_H
#define FILTER_BLACK_AND_WHITE_H
namespace math {
	class FilterBlackAndWhite :public Filter {
	public:
		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getWidth(), (unsigned int)image.getHeight());
			int i, j;
			float avg;
			Color clr;
			int w = image.getWidth(), h = image.getHeight();
			for (i = 0; i < w; i++) {
				for (j = 0; j < h; j++) {
					clr = image.getCell(i, j);
					avg = (clr.r + clr.g + clr.b) / 3;
					clr = Color(avg, avg, avg);
					img.setCell(i, j, clr);
				}
			}
			return img;
		}

	};
}
#endif // !FILTER_BLACK_AND_WHITE_H
