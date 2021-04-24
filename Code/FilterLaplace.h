#include "Image.h"
#include "Filter.h"
#include "FilterBlur.h"
#include "Array.h"

#ifndef FILTER_LAPLACE_H
#define FILTER_LAPLACE_H
namespace math {
	class FilterLaplace :public FilterBlur {

	public:

		virtual Image operator << (const Image & image) {
			Image img = Image((unsigned int)image.getWidth(), (unsigned int)image.getHeight());
			unsigned int i, j;
			int xxx = image.getWidth();
			int yyy = image.getHeight();
			for (i = 0; i < xxx; i++) {
				for (j = 0; j < yyy; j++) {
					Color clr = Color(0, 0, 0);
					/*
					faster than accessing the vector
					we still make a vector because we were asked to
					we could make two more nested for loops but from the 9 values of the vector
					4 are zeros so we do not need to add them, another 4 are ones so
					we don't need to make the multiplication and only one is -4
					we only made the vector because it said so in the ekfonisi
					*/
					if (j - 1 >= 0 && j - 1 < yyy) {
						clr += image.getCell(i, j - 1);
					}
					if (j + 1 >= 0 && j + 1 < yyy) {
						clr += image.getCell(i, j + 1);
					}
					if (i - 1 >= 0 && i - 1 < xxx) {
						clr += image.getCell(i - 1, j);
					}
					if (i + 1 >= 0 && i + 1 < xxx) {
						clr += image.getCell(i + 1, j);
					}
					clr -= 4 * image.getCell(i, j);
					clr = between0and1(clr);
					img.setCell(i, j, clr);
				}
			}
			return img;
		}

		//no need for other constructors since all laplace filters are the same
		/* FilterLaplace() {
			width = 3;
			height = 3;
			float arr[] = { 0 , 1 , 0 , 1 , -4 , 1 , 0 , 1 , 0 };
			std::vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
			buffer = vec;
		} */

	};

}
#endif