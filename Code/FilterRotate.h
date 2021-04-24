#include "Image.h"
#include "Filter.h"
#include "Array.h"

#ifndef FILTER_ROTATE_H
#define FILTER_ROTATE_H
#define LEFT 1
#define RIGHT 0
namespace math {
	class FilterRotate :public Filter {
	private:
		int direction; // 0 to right, 1 to left
	public:
		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getHeight(), (unsigned int)image.getWidth());
			int i, j;
			Color clr;
			unsigned int w = image.getWidth(), h = image.getHeight();
			if (direction == LEFT) {
				for (i = 0; i < w; i++) {
					for (j = 0; j < h; j++) {
						clr = image.getCell(i, j);
						img.setCell(j, w - i - 1, clr);
					}
				}
			}
			else {
				for (i = 0; i < w; i++) {
					for (j = 0; j < h; j++) {
						clr = image.getCell(i, j);
						img.setCell(h - j - 1, i, clr);
					}
				}
			}
			return img;
		}

		FilterRotate() {
			direction = RIGHT;
		}

		FilterRotate(std::string arg) {
			if (arg == "left") {
				direction = LEFT;
			}
			else {
				direction = RIGHT;
			}
		}

		FilterRotate(const FilterRotate &src) {
			direction = src.direction;
		}
	};

}
#endif