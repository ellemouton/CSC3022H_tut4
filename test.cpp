#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "imageops.h"
#include "imageops.cpp"
using namespace std;

TEST_CASE("Move and Copy Semantics","[move_copy]"){
		
		
		SECTION( "Copy Constructor" ) {
			std::cout << "Copy Constructor tests" << std::endl;

			unsigned char buffer1 [] = {1,2,3,4,5,6,7,8,9};
			unsigned char buffer2 [] = {10,11,12,13,14,15,16,17,18};

			MTNELL004::Image i1(3,3, buffer1);
			MTNELL004::Image i2(i1);

			MTNELL004::Image::iterator it_i1_beg = i1.begin(), it_i1_end = i1.end();
			MTNELL004::Image::iterator it_i2_beg = i2.begin(), it_i2_end = i2.end();

			//Require that both i1 and i2 have the same values but differnet pointers to the data
			REQUIRE(i1.getWidth() == 3);
			REQUIRE(i1.getHeight() == 3);
			REQUIRE(i2.getWidth() == 3);
			REQUIRE(i2.getHeight() == 3);
			REQUIRE_FALSE(i1.getData() == i2.getData()); //pointer are different

			while(it_i1_beg!=it_i1_end){
				REQUIRE(*it_i1_beg == *it_i2_beg);
				++it_i1_beg; ++it_i2_beg;
			}

		}

		SECTION( "Copy Assignement operator" ) {
			std::cout << "Copy Assignement operator test" << std::endl;
			unsigned char buffer1 [] = {1,2,3,4,5,6,7,8,9};
			unsigned char buffer2 [] = {10,11,12,13,14,15,16,17,18};

			MTNELL004::Image i1(3,3, buffer1);
			MTNELL004::Image i2(3,3, buffer2);
			MTNELL004::Image i3(3,3, buffer2); //same values as i2

			MTNELL004::Image::iterator it_i1_beg = i1.begin(), it_i1_end = i1.end();
			MTNELL004::Image::iterator it_i2_beg = i2.begin(), it_i2_end = i2.end();
			MTNELL004::Image::iterator it_i3_beg = i3.begin(), it_i3_end = i3.end();

			while(it_i1_beg!=it_i1_end){
				REQUIRE_FALSE(*it_i1_beg == *it_i2_beg);
				++it_i1_beg; ++it_i2_beg;
			}

			i1 = i2;

			//require that the images now have the same values but different pointers
			//also ensure that the values of i2 have not changes (thus are equal to values in i3 which was creates with the same buffer as i2)
			REQUIRE_FALSE(i1.getData() == i2.getData()); 
			while(it_i1_beg!=it_i1_end){
				REQUIRE(*it_i1_beg == *it_i2_beg);
				REQUIRE(*it_i2_beg == *it_i3_beg);
				++it_i1_beg; ++it_i2_beg; ++it_i3_beg;
			}

			
		}

		SECTION( "Move Constructor" ) {
			std::cout << "Move Constructor tests" << std::endl;

			unsigned char buffer1 [] = {1,2,3,4,5,6,7,8,9};

			MTNELL004::Image i1(3,3, buffer1);
			MTNELL004::Image i2(std::move(i1));

			MTNELL004::Image::iterator it_i1_beg = i1.begin(), it_i1_end = i1.end();
			MTNELL004::Image::iterator it_i2_beg = i2.begin(), it_i2_end = i2.end();

			
			REQUIRE(i2.getWidth() == 3);
			REQUIRE(i2.getHeight() == 3);
			REQUIRE_FALSE(i1.getData() == i2.getData()); //pointer are different

			//Require that the values of i2 are the same as in 'buffer' 
			int index = 0;
			while(it_i1_beg!=it_i1_end){
				REQUIRE(*it_i2_beg == buffer1[index]);
				++it_i1_beg; ++it_i2_beg; ++index;
			}

		}

		SECTION( "Move Assignement operator" ) {
			std::cout << "Move Assignement operator test" << std::endl;

			unsigned char buffer1 [] = {1,2,3,4,5,6,7,8,9};
			unsigned char buffer2 [] = {10,11,12,13,14,15,16,17,18};

			MTNELL004::Image i1(3,3, buffer1);
			MTNELL004::Image i2(3,3, buffer2);
			MTNELL004::Image i3(3,3, buffer2); //same values as i2

			MTNELL004::Image::iterator it_i1_beg = i1.begin(), it_i1_end = i1.end();
			MTNELL004::Image::iterator it_i2_beg = i2.begin(), it_i2_end = i2.end();
			MTNELL004::Image::iterator it_i3_beg = i3.begin(), it_i3_end = i3.end();

			while(it_i1_beg!=it_i1_end){
				REQUIRE_FALSE(*it_i1_beg == *it_i2_beg);
				++it_i1_beg; ++it_i2_beg;
			}

			i1 = std::move(i2);

			//require that the images now have the same values but different pointers
			//also ensure that the values of i2 have not changes (thus are equal to values in i3 which was creates with the same buffer as i2)
			REQUIRE_FALSE(i1.getData() == i2.getData()); 
			while(it_i1_beg!=it_i1_end){
				REQUIRE(*it_i1_beg == *it_i2_beg);
				REQUIRE(*it_i2_beg == *it_i3_beg);
				++it_i1_beg; ++it_i2_beg; ++it_i3_beg;
			}
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
		
		unsigned char buffer1 [] = {11,101,200,255,0,40,120,230,24};
		unsigned char buffer2 [] = {55,90,100,3,3,5,60,112,4};
		MTNELL004::Image U1(3,3, buffer1);
		MTNELL004::Image U2(3,3, buffer2);
		MTNELL004::Image M1;
		MTNELL004::Image M2;
		MTNELL004::Image M3;
		MTNELL004::Image M4;
		MTNELL004::Image FinalImage;

		//--------------thresholding--------------
		int threshold = 100;
		M1 = U1*threshold;

		//require that U1 remains unchanged
		MTNELL004::Image::iterator it_U1_beg = U1.begin(), it_U1_end = U1.end();
		REQUIRE(*it_U1_beg == 11);
		++it_U1_beg;
		REQUIRE(*it_U1_beg == 101);

		//require that M1 values below threshold = 0, else 255
		MTNELL004::Image::iterator it_M1_beg = M1.begin(), it_M1_end = M1.end();
		REQUIRE(*it_M1_beg == 0);
		++it_M1_beg;
		REQUIRE(*it_M1_beg == 255);

		//-----------------inverting-------------
		M2 = !M1;

		//require that all M! values remain unchanged
		it_M1_beg = M1.begin(), it_M1_end = M1.end();
		REQUIRE(*it_M1_beg == 0);
		++it_M1_beg;
		REQUIRE(*it_M1_beg == 255);

		//require that valus in M2 are the inverted values of M1
		MTNELL004::Image::iterator it_M2_beg = M2.begin(), it_M2_end = M2.end();
		REQUIRE(*it_M2_beg == 255);
		++it_M2_beg;
		REQUIRE(*it_M2_beg == 0);

		//------------------masking--------------
		M3 = U1/M1;
		M4 = U2/M2;

		MTNELL004::Image::iterator it_M3_beg = M3.begin(), it_M3_end = M3.end();
		MTNELL004::Image::iterator it_M4_beg = M4.begin(), it_M4_end = M4.end();

		//require that values for U1,M1,U2 and M2 remain unchanged
		MTNELL004::Image::iterator it_U2_beg = U2.begin(), it_U2_end = U2.end();
		it_U1_beg = U1.begin(), it_U1_end = U1.end();
		it_M1_beg = M1.begin(), it_M1_end = M1.end();
		it_M2_beg = M2.begin(), it_M2_end = M2.end();
		REQUIRE(*it_M1_beg==0);
		REQUIRE(*it_M2_beg==255);
		REQUIRE(*it_U1_beg == 11);
		REQUIRE(*it_U2_beg == 55);

		//require the values in M3 to be values in U1 masked with M1 
		while(it_M1_beg!=it_M1_end){
			if(*it_M1_beg==255){
				REQUIRE(*it_M3_beg == *it_U1_beg);
			}
			else{
				REQUIRE(*it_M3_beg == 0);
			}
			++it_M1_beg; ++it_M3_beg; ++it_U1_beg;
		}

		//require values in M4 to be values in U2 masked with value in M2

		while(it_M2_beg!=it_M2_end){
			if(*it_M2_beg==255){
				REQUIRE(*it_M4_beg == *it_U2_beg);
			}
			else{
				REQUIRE(*it_M4_beg == 0);
			}
			++it_M2_beg; ++it_M4_beg; ++it_U2_beg;
		}


		//---------------Addition of images---------------
		// -> ensure that pixels are clamped properly

		FinalImage = M3+M4;
		MTNELL004::Image::iterator it_FinalImage_beg = FinalImage.begin(), it_FinalImage_end = FinalImage.end();
		it_M3_beg = M3.begin(), it_M3_end = M3.end();
		it_M4_beg = M4.begin(), it_M4_end = M4.end();

		int sum;

		while(it_FinalImage_beg!=it_FinalImage_end){
			sum = *it_M3_beg + *it_M4_beg;
			if(sum>255){
				REQUIRE(*it_FinalImage_beg==255);
			}
			else{
				REQUIRE(*it_FinalImage_beg==sum);
			}
			++it_FinalImage_beg; ++it_M4_beg; ++it_M3_beg;
		}

		//---------------Subtraction of images---------------
		// -> ensure that pixels are clamped properly

		FinalImage = M3-M4;
		it_FinalImage_beg = FinalImage.begin(), it_FinalImage_end = FinalImage.end();
		it_M3_beg = M3.begin(), it_M3_end = M3.end();
		it_M4_beg = M4.begin(), it_M4_end = M4.end();

		int diff;

		while(it_FinalImage_beg!=it_FinalImage_end){
			diff = *it_M3_beg - *it_M4_beg;
			if(diff<0){
				REQUIRE(*it_FinalImage_beg==0);
			}
			else{
				REQUIRE(*it_FinalImage_beg==diff);
			}
			++it_FinalImage_beg; ++it_M4_beg; ++it_M3_beg;
		}
		

		//---------------Test filter----------------
		// operation -> check boundary conditons

		
		

}











