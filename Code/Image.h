#include "Vec3.h"
#include "Array.h"
#include <string>
#include <stdlib.h>
#include "ppm.h"

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED
namespace math {
	typedef Vec3<float> Color;
	class Image : public Array< Vec3<float> > {
	public:
		Image() : Array< Vec3< float > >() {}

		Image(unsigned int w, unsigned int h) : Array< Vec3< float > >(w, h) {}

		Image(unsigned int w, unsigned int h, const Color * data_ptr) : Array< Vec3< float > >(w, h, data_ptr) {}

		Image(const Image &src) : Array< Vec3< float > >(src) {}

	private:
		bool endsWith(std::string const &full, std::string const &end) {						//returns whether string full ends with string end
			if (full.length() >= end.length()) {
				return (0 == full.compare(full.length() - end.length(), end.length(), end));
			}
			else {
				return false;
			}
		}

		std::string toUpperCase(std::string x) {												//method to upper the letters
			int i;
			std::string temp = "";
			for (i = 0; !x[i]; i++) {
				if (x[i] > 96 && x[i] < 123) { temp += x[i] - 32; }
			}
			return temp;
		}
	public:
		bool load(const std::string & filename, const std::string & format) {

			std::string dot = ".";
			const char *fname = filename.c_str();
			dot.append(format);
			if (endsWith(filename, dot) || endsWith(toUpperCase(filename), toUpperCase(dot))) {	//if the filename's extension is ppm
				unsigned int* pwidth = &width;
				unsigned int* pheight = &height;
				float* tmp = imaging::ReadPPM(fname, (int*)pwidth, (int*)pheight);
				if (!tmp) {
					return false;
				}
				Color * bufferr = (Color*)malloc(width*height * sizeof(Color));
				for (int i = 0; i < 3 * width*height; i += 3) {
					bufferr[i / 3] = Color(tmp[i], tmp[i + 1], tmp[i + 2]);
				}
				free(tmp);
				if (bufferr) {
					std::vector<Color> temp(bufferr, bufferr + width * height);
					buffer = temp;
					free(bufferr);
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}

		bool save(const std::string & filename, const std::string & format) {
			std::string dot = ".";
			const char *fname = filename.c_str();
			dot.append(format);
			if (endsWith(filename, dot) || endsWith(toUpperCase(filename), toUpperCase(dot)) && !buffer.empty()) {
				//Color* bufferr = (Color*)malloc(width*height * sizeof(Color));
				Color* bufferr = &buffer[0];

				float* buf = (float*)malloc(3 * width*height * sizeof(float));
				for (int i = 0; i < width*height * 3; i += 3) {
					buf[i] = bufferr[i / 3].r;
					buf[i + 1] = bufferr[i / 3].g;
					buf[i + 2] = bufferr[i / 3].b;
				}
				//free(bufferr);
				bool flag = imaging::WritePPM(buf, (int)width, (int)height, fname);
				free(buf);
				return flag;
			}
			else {
				return false;
			}
		}

	};
}
#endif