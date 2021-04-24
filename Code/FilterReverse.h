#include "Image.h"
#include "Filter.h"
#include "Array.h"

#ifndef FILTER_REVERSE
#define FILTER_REVERSE
namespace math {
	class FilterReverse :public Filter {
	public:
		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getWidth(), (unsigned int)image.getHeight());
			int i, j;
			int w = image.getWidth(), h = image.getHeight();
			Color clr;
			for (i = 0; i < w; i++) {
				for (j = 0; j < h; j++) {
					clr = image.getCell(i, j);
					img.setCell(w - i - 1, j, clr);
				}
			}
			return img;
		}

	};
}
#endif // !FILTER_REVERSE
