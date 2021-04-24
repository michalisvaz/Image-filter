#include "Image.h"
#include "Filter.h"
#include "Array.h"
#include <math.h>

#ifndef FILTER_GAMMA_H
#define FILTER_GAMMA_H
namespace math {
	class FilterGamma :public Filter {
	private:
		float ekthetis;
	public:
		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getWidth(),(unsigned int)image.getHeight());
			int i, j;
			int w = image.getWidth(), h = image.getHeight();
			for (i = 0; i < w; i++) {
				for (j = 0; j < h; j++) {
					Color clr = image.getCell(i, j);
					clr.r = pow(clr.r, ekthetis);
					clr.g = pow(clr.g, ekthetis);
					clr.b = pow(clr.b, ekthetis);
					clr = between0and1(clr);
					img.setCell(i, j, clr);
				}
			}
			return img;
		}

		FilterGamma() {
			ekthetis = 1;
		}

		FilterGamma(float exp) {
			ekthetis = exp;
		}

		FilterGamma(const FilterGamma &src) {
			ekthetis = src.ekthetis;
		}
	};

}
#endif