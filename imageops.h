/**
*imageops.h file
*/

#ifndef IMAGEOPS_H
#define IMAGEOPS_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace MTNELL004{
	int convertToInt(std::string str);

	class Image{
		friend class iterator;
		private:
			int width, height;
			std::unique_ptr<unsigned char[]> data;

		public:

			//constructor
			Image();

			//destructor
			~Image();

			
			//copy constructor
			Image(const Image & rhs);

			/*
			//move constructor
			Image(Image && rhs);

			//copy assignment operator
			Image & operator=(const Image & rhs);

			//move assignment operator
			Image & operator=(Image && rhs);
			*/

			void load(std::string input);
			void save(std::string output);
			void printVals(void);

			//overload operations
			Image & operator+=(const Image & rhs);
			Image operator+(const Image & rhs);

			class iterator{
				friend class Image;
				private:
					unsigned char *ptr;
					//construct only via Image class (begin/end)
					iterator(u_char *p): ptr(p){}

				public:
					//copy constructor is public 
					iterator(const iterator & rhs): ptr(rhs.ptr){}

					//define overload ops: *, ++, --, =
					iterator & operator=(const iterator & rhs){
						ptr = rhs.ptr;
						return *this;
					}

					unsigned char & operator*() {
						return *ptr;
					}

					iterator & operator++(){
						++ptr;
						return *this;
					}

					iterator & operator--(){
						--ptr;
						return *this;
					}

					bool operator !=(const iterator & rhs){
						return ptr == rhs.ptr;
					}

					//other methods for iterator
			};

			//define begin()/end() to get iterator to start and "one-past" end
			iterator begin(void) const{
				return iterator(data.get());
			}
			iterator end(void) const{
				return iterator(&data[width*height]);
			}
			void start(void) const{
				std::cout<<(float)*data.get()<<std::endl;
			}
			void finish(void) const{
				std::cout<<(float)(data[width*height])<<std::endl;
			}



	};
}


#endif