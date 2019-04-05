/**
*imageops.h file
*/

#ifndef IMAGEOPS_H
#define IMAGEOPS_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

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

			//move constructor
			Image(Image && rhs);

			//copy assignment operator
			Image & operator=(const Image & rhs);

			//move assignment operator
			Image & operator=(Image && rhs);
			

			void load(std::string input);
			void save(std::string output);
			void printVals(void);

			//overload operations
			Image & operator+=(const Image & rhs);
			Image & operator-=(const Image & rhs);
			Image operator+(const Image & rhs) const;
			Image operator-(const Image & rhs) const;
			Image operator!(void) const;
			Image operator/(const Image & rhs) const;
			Image operator*(int thresh) const;
			Image operator%(std::string g) const;

			class iterator{
				friend class Image;
				private:
					unsigned char *ptr;
					//construct only via Image class (begin/end)
					iterator(u_char *p);

				public:
					//copy constructor is public 
					iterator(const iterator & rhs);

					//define overload ops: *, ++, --, =
					iterator & operator=(const iterator & rhs);

					unsigned char & operator*();

					iterator & operator++();

					iterator & operator--();

					bool operator !=(const iterator & rhs);

					//other methods for iterator

					iterator & operator+(int offset);
					iterator & operator-(int offset);

			};

			//define begin()/end() to get iterator to start and "one-past" end
			iterator begin(void) const;
			iterator end(void) const;



	};
}


#endif