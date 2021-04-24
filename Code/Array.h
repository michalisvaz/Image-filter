#include <vector>
#include <iostream>

#ifndef _ARRAY
#define _ARRAY
namespace math{
	template <class T>
	class Array{ 
		protected:
			std::vector<T> buffer;
			unsigned int width,height;
		public:
			const unsigned int getWidth() const {return width;}
			
			const unsigned int getHeight() const {return height;}

			std::vector<T> getBuffer();// previously getRawDataptr
			
			T getCell(unsigned int x, unsigned int y) const { 
				if (x < width && y < height && x >= 0 && y >= 0) {
					return buffer[x + width * y];
				}
				else {
					return 0;
				}
			}
			
			void setCell(unsigned int x, unsigned int y, T & value);
			
			void setData(const T * & data_ptr);

			Array();
			
			Array(unsigned int width, unsigned int height);
			
			Array(unsigned int width, unsigned int height, const T * data_ptr);
			
			Array(const Array &src);
			
			Array & operator = (const Array & right);

			Array & operator () (int i,int j);
	};
			
	template <class T> Array <T>::Array(){
		width = 0;
		height = 0;
		std::vector<T> temp(width*height, 0);
		buffer = temp;
	}

	template <class T> Array <T>::Array(unsigned int w, unsigned int h) {
		width = w;
		height = h;
		std::vector<T> temp(width*height, 0);
		buffer = temp;
	}

	template<class T> Array <T>::Array(unsigned int w, unsigned int h, const T * data_ptr) {
		width = w;
		height = h;
		std::vector<T> temp(data_ptr, data_ptr + width*height);
		buffer = temp;
	}
			
	template <class T> Array <T>::Array(const Array &src) {
		width = src.width;
		height = src.height;
		buffer = src.buffer;
	}

	template <class T> Array<T> & Array<T>::operator = (const Array & right) {
		if (this == &right) {
			return *this;
		}
		width = right.width;
		height = right.height;
		buffer = right.buffer;
		return *this;
	}

	template <class T> Array<T> & Array<T>::operator () (int i, int j) {
		return  buffer[i + width * j];
	}

	template<class T> std::vector<T> Array<T>::getBuffer() {
		return buffer;
	}

	template<class T> void Array<T>::setCell(unsigned int x, unsigned int y, T & value) {
		if (x < width && y < height && x >= 0 && y >= 0) {
			buffer[x + width * y] = value;
		}
		else {
			std::cout << "Index out of bounds" << std::endl;
		}
	}

	template<class T> void Array<T>::setData(const T * & data_ptr) {
		if (!data_ptr || !width || !height) {
			return;
		}
		else {
			std::vector<T> temp(data_ptr, data_ptr + width * height);
			buffer = temp;
		}
	}	
}
#endif