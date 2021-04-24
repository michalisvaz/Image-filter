#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>

namespace imaging{
	int max;
	float * ReadPPM(const char * filename, int * w, int * h) {
		float *temp;
		unsigned char *tempc;
		FILE* fp=fopen(filename, "rb");
		char format[3] = "\0\0";
		int width, height,x;
		if (fp) {
			x = fscanf(fp, "%s%*[ ,\t,\n,\r]%d%*[ ,\t,\n,\r]%d%*[ ,\t,\n,\r]%d%*[ ,\t,\n,\r]", format, &width, &height, &max);
			if (x < 4) {
				return temp=0;
			} else if (format[0] == 'P' && format[1] == '6' && !format[2] && max <= 255) {
				*w=width;
				*h=height;
				tempc=(unsigned char*)malloc(3*width*height*sizeof(unsigned char));
				fread(tempc,width,3*height,fp);
				temp=(float*)malloc(3*width*height*sizeof(float));
				for (int i = 0; i < 3*width*height; i++) {
					temp[i] = (float)tempc[i]/255.0f;
				}
				free(tempc);
			} else {
				temp = 0;
			}
		} else {
			return 0;
		}
		fclose(fp);
		return temp;
	}

	bool WritePPM(const float * data, int w, int h, const char * filename) {
		FILE* fp=fopen(filename, "wb");
		unsigned char* c= (unsigned char*)malloc(3*w*h);//sizeof(unsigned char) is 1
		if (!fp) {
			return false;
		}else {
			fprintf(fp, "P6\n%d\n%d\n%d\n",w,h,max);
			for (int i = 0; i < w*h*3; i++) {
				c[i] = (unsigned char)(data[i] * 255.0f);
			}
		}
		fwrite(c, 3*w, h, fp);
		fclose(fp);
		free(c);
		return true;
	}
}