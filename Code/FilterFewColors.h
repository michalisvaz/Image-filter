#include "Image.h"
#include "Filter.h"
#include "Array.h"

#ifndef FILTER_FEW_COLORS_H
#define FILTER_FEW_COLORS_H
namespace math {
	class FilterFewColors : public Filter {
	private:
		unsigned int steps;
		float fsteps;
	public:

		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getWidth(), (unsigned int)image.getHeight());
			int i, j;
			float r, g, b;
			Color clr;
			int w = image.getWidth(), h = image.getHeight();
			for (i = 0; i < w; i++) {
				for (j = 0; j < h; j++) {
					Color tempcol = image.getCell(i, j);
					r = tempcol.r;
					g = tempcol.g;
					b = tempcol.b;
					clr = Color((int)(r * steps + 0.5) / fsteps, (int)(g * steps + 0.5) / fsteps, (int)(b * steps + 0.5) / fsteps);
					img.setCell(i, j, clr);
				}
			}
			return img;
		}

		FilterFewColors() {
			steps = 4;
			fsteps = (float)steps;
		}

		FilterFewColors(unsigned int s) {
			steps = s;
			fsteps = (float)steps;
		}
	};
}
#endif // !FILTER_FEW_COLORS_H
