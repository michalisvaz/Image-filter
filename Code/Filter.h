#include "Image.h"

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED
namespace math {
	
	Color between0and1(Color a) {
		Color b = a.clampToUpperBound(1);
		b = b.clampToLowerBound(0);
		return b;
	}

	float distance(Color a, Color b) {

	}

	class Filter {
		public:
			virtual Image operator << (const Image & image)=0;
			Filter() {}
			Filter(const Filter &src) {}
	};

}
#endif