#include "Image.h"
#include "Filter.h"
#include "Array.h"
#include <iostream>

#ifndef FILTER_BLUR_H
#define FILTER_BLUR_H
namespace math {
	class FilterBlur : public Filter {
	private:
		float fvalue;
		unsigned int dimensions;
	public:

		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getWidth(), (unsigned int)image.getHeight());
			int i, j, m, n, w = dimensions;
			int xxx = image.getWidth();
			int yyy = image.getHeight();
			for (i = 0; i < xxx; i++) {
				for (j = 0; j < yyy; j++) {
					Color clr = Color(0, 0, 0);
					for (m = -w / 2; m <= w / 2; m++) {
						for (n = -w / 2; n <= w / 2; n++) {
							if ((m + i >= 0 && m + i < xxx) && (n + j >= 0 && n + j < yyy)) {
								clr += (fvalue * image.getCell(i + m, j + n));
							}
						}
					}
					clr = between0and1(clr);
					img.setCell(i, j, clr);
				}
			}
			return img;
		}

		FilterBlur() {
			fvalue = 0;
			dimensions = 0;
		}

		FilterBlur(unsigned int n) {
			dimensions = n;
			fvalue = 1.0f / ((float)n*(float)n);
		}

		FilterBlur(const FilterBlur &src) {
			fvalue = src.fvalue;
			dimensions = src.dimensions;
			std::cout << "src" << std::endl;
		}
	};

}
#endif