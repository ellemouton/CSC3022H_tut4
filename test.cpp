#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "imageops.h"
#include "imageops.cpp"
using namespace std;

TEST_CASE("Move and Copy Semantics","[move_copy]"){
		
		
		SECTION( "Copy Constructor" ) {
			std::cout << "Copy Constructor tests" << std::endl;
			MTNELL004::Image i1;
			i1.load("shrek_rectangular.pgm");
			MTNELL004::Image i2(i1);

			REQUIRE(i1.getWidth() == i2.getWidth());
			REQUIRE(i1.getHeight() == i2.getHeight());
			REQUIRE_FALSE(i1.getData() == i2.getData()); //pointer are different
			REQUIRE(*i1.getData() == *i2.getData()); //values that pointers point to are the same.

		}

		SECTION( "Copy Assignement operator" ) {
			std::cout << "Copy Assignement operator test" << std::endl;
			MTNELL004::Image i1;
			MTNELL004::Image i2;

			i1.load("shrek_rectangular.pgm");
			i2.load("Lenna_standard.pgm");

			REQUIRE_FALSE(i1.getWidth() == i2.getWidth());
			REQUIRE_FALSE(i1.getHeight() == i2.getHeight());
			REQUIRE_FALSE(i1.getData() == i2.getData()); 
			REQUIRE_FALSE(*i1.getData() == *i2.getData());

			i1 = i2;

			REQUIRE(i1.getWidth() == i2.getWidth());
			REQUIRE(i1.getHeight() == i2.getHeight());
			REQUIRE_FALSE(i1.getData() == i2.getData()); 
			REQUIRE(*i1.getData() == *i2.getData());

			
		}

		SECTION( "Move Constructor" ) {
			std::cout << "Move Constructor tests" << std::endl;

			MTNELL004::Image i1;
			i1.load("shrek_rectangular.pgm");
			

			REQUIRE(i1.getWidth());
			REQUIRE(i1.getHeight());
			REQUIRE(i1.getData()); 

			MTNELL004::Image i2(std::move(i1));

		
			REQUIRE_FALSE(i1.getData() == i2.getData());
			//need to add more here

		}

		SECTION( "Move Assignement operator" ) {
			std::cout << "Move Assignement operator test" << std::endl;

			MTNELL004::Image i1;
			MTNELL004::Image i2;

			i1.load("shrek_rectangular.pgm");
			i2.load("Lenna_standard.pgm");

			REQUIRE_FALSE(i1.getWidth() == i2.getWidth());
			REQUIRE_FALSE(i1.getHeight() == i2.getHeight());
			REQUIRE_FALSE(i1.getData() == i2.getData()); 
			REQUIRE_FALSE(*i1.getData() == *i2.getData());

			i1 = std::move(i2);

			REQUIRE_FALSE(i1.getData() == i2.getData()); 
			//need to add more here
		}

}

TEST_CASE("Iterator","[iterator]"){
		std::cout << "Iterator tests" << std::endl;
		
		SECTION( "Iterator operations" ) {
			unsigned char buffer1 [] = {1,2,3,4,5,6,7,8,9};
			unsigned char buffer2 [] = {10,11,12,13,14,15,16,17,18};

			MTNELL004::Image i1(3,3, buffer1);
			MTNELL004::Image::iterator beg = i1.begin(), end = i1.end();

			//testing the 'begin' function and  '*' operator
			REQUIRE(*beg == 1);

			//testing the 'end' function and the '*' operator
			--end;
			REQUIRE(*end == 9);

			//testing the '++', '--' and '*' operator
			++beg;
			++beg;
			REQUIRE(*beg == 3);

			--beg;
			REQUIRE(*beg ==2);

			//testing the '!=' operator
			REQUIRE(beg!=end);

			//testing the '=' operator
			beg = end;
			REQUIRE(*beg == *end);



		}

		SECTION( "Boundary Conditions" ) {
			

		}

}

TEST_CASE("Image operations","[image_ops]"){
		std::cout << "Image operation tests" << std::endl;
		
		unsigned char buffer1 [] = {11,40,200,255,0,130,120,230,24};
		unsigned char buffer2 [] = {55,90,100,3,3,5,60,112,4};
		MTNELL004::Image U1(3,3, buffer1);
		MTNELL004::Image U2(3,3, buffer2);
		MTNELL004::Image M1;
		MTNELL004::Image M2;
		MTNELL004::Image M3;
		MTNELL004::Image M4;
		MTNELL004::Image FinalImage;

		//thresholding
		int threshold = 10;
		M1 = U1*threshold;

		//inverting
		M2 = !M1;

		//masking
		M3 = U1/M1;
		M4 = U2/M2;

		//Addition and subtraction of images -> ensure that pixels are clamped properly
		FinalImage = M3+M4;

		//test filter operation -> check boundary conditons

}











