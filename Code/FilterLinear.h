#include "Image.h"
#include "Filter.h"
#include "Array.h"

#ifndef FILTER_LINEAR_H
#define FILTER_LINEAR_H
namespace math {
	class FilterLinear:public Filter {
	private:
		Color a, b;
	public:
		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getWidth(), (unsigned int)image.getHeight());
			int i, j;
			Color clr;
			unsigned int w = image.getWidth(), h = image.getHeight();
			for (i = 0; i < w; i++) {
				for (j = 0; j < h; j++) {
					Color tempcol = image.getCell(i, j);
					clr = tempcol * a + b;
					clr = between0and1(clr);
					img.setCell(i, j, clr);
				}
			}
			return img;
		}

		FilterLinear() {
			a = 0;
			b = 0;
		}

		FilterLinear(Color aa, Color bb) {
			a = aa;
			b = bb;
		}

		FilterLinear(const FilterLinear &src) {
			a = src.a;
			b = src.b;
		}
	};

}
#endif