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

		}

		SECTION( "Boundary Conditions" ) {

		}

}

TEST_CASE("Image operations","[image_ops]"){
		std::cout << "Image operation tests" << std::endl;
		
		//thresholding, inverting and masking operator overloads

		//Addition and subtraction of images -> ensure that pixels are clamped properly

		//test filter operation -> check boundary conditons

}











