#include <iostream>
#include <string>
#include "Image.h"
#include "Vec3.h"
#include "Array.h"
#include "FilterLinear.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"
#include "FilterGamma.h"
#include "FilterBlackAndWhite.h"
#include "FilterReverse.h"
#include "FilterFewColors.h"
#include "FilterRotate.h"

using namespace std;

bool isnumber(string x) {
	if (x.empty()) {
		return false;
	}
	if (x[0] != '-' && x[0] != '+' && (x[0]<'0' || x[0]>'9')) {
		return false;
	}
	int i, f = 0;
	for (i = 1; i < x.length(); i++) {
		if (x[i] == '.') {
			f++;
		}
		else if (x[i]<'0' || x[i]>'9') {
			return false;
		}
		if (f > 1) {
			return false;
		}
	}
	return true;
}

bool isPositiveInteger(string x) {
	if (x.empty()) {
		return false;
	}
	int i;
	for (i = 0; i < x.length(); i++) {
		if (x[i]<'0' || x[i]>'9') {
			return false;
		}
	}
	return true;
}

int main(int argc, char ** argv)
{
	string str = argv[argc - 1];
	string arg;
	math::Image photo = math::Image();
	int i;
	unsigned char inlinear = 0, ingamma = 0, inblur = 0, isfilter = 0, infew = 0, inrotate = 0;
	if (argc == 1) {
		return -1;
	}
	if (photo.load(str, ".ppm")) {
		if (argc == 2) {//if only an image was passed as cmd argument do nothing and finish the program
			return -1;
		}
		cout << "Photo height: " << photo.getHeight() << "\n" << "Photo width: " << photo.getWidth() << "\n";
		math::Image photo2 = math::Image(photo.getWidth(), photo.getHeight());
		for (i = 1; i < argc - 1; i++) {
			arg = argv[i];
			inlinear = inlinear >> 1;
			ingamma = ingamma >> 1;
			inblur = inblur >> 1;
			infew = infew >> 1;
			inrotate = inrotate >> 1;
			isfilter = isfilter >> 1;
			if (arg == "-f") {
				isfilter = 2;
			}
			else if (isfilter && arg == "linear") {
				inlinear = 64; //2^6
			}
			else if (isfilter && arg == "gamma") {
				ingamma = 2;
			}
			else if (isfilter && arg == "blur") {
				inblur = 2;
			}
			else if (isfilter && arg == "fewcol") {
				infew = 2;
			}
			else if (isfilter && arg == "rotate") {
				inrotate = 2;
			}
			else if (isfilter && arg == "laplace") {
				math::FilterLaplace lapl = math::FilterLaplace();
				photo2 = lapl << photo;
				photo = photo2;
			}
			else if (isfilter && arg == "blackwhite") {
				math::FilterBlackAndWhite wb = math::FilterBlackAndWhite();
				photo2 = wb << photo;
				photo = photo2;
			}
			else if (isfilter && arg == "reverse") {
				math::FilterReverse rev = math::FilterReverse();
				photo2 = rev << photo;
				photo = photo2;
			}
			else if (inlinear && isnumber(arg)) {
				if (inlinear == 1) {
					math::FilterLinear lin = math::FilterLinear(math::Color(stof(argv[i - 5]), stof(argv[i - 4]), stof(argv[i - 3])), math::Color(stof(argv[i - 2]), stof(argv[i - 1]), stof(arg)));
					photo2 = lin << photo;
					photo = photo2;
				}
			}
			else if (ingamma && isnumber(arg)) {
				if (ingamma == 1) {
					math::FilterGamma gam = math::FilterGamma(stof(arg));
					photo2 = gam << photo;
					photo = photo2;
				}
			}
			else if (inblur && isPositiveInteger(arg)) {
				if (inblur == 1) {
					math::FilterBlur bl = math::FilterBlur(stoi(arg));
					photo2 = bl << photo;
					photo = photo2;
				}
			}
			else if (infew && isPositiveInteger(arg)) {
				if (infew == 1) {
					math::FilterFewColors few = math::FilterFewColors(stoi(arg));
					photo2 = few << photo;
					photo = photo2;
				}
			}
			else if (inrotate && (arg == "left" || arg == "right")) {
				if (inrotate == 1) {
					math::FilterRotate rot = math::FilterRotate(arg);
					photo2 = rot << photo;
					photo = photo2;
				}
			}
			else {
				cout << "You messed up the filters" << endl;
				return -1;
			}
		}
		if (isfilter > 1 || inlinear > 1 || ingamma > 1 || inblur > 1 || infew > 1 || inrotate > 1) {
			cout << "You messed up the filters" << endl;
			return -1;
		}
	}
	else {
		cout << "You didn't give image correctly" << endl;
		return -1;
	}
	if (str.rfind('\\') == std::string::npos) {
		str = "filtered_" + str;
	}
	else {
		str.insert(str.rfind('\\') + 1, "filtered_");
	}
	if (photo.save(str, ".ppm")) {
		cout << "Great success" << endl;
	}
	else {
		cout << "Something went wrong in writing" << endl;
	}
	return 0;
}