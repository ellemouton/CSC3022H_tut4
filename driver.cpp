#include "imageops.h"

using namespace std;

int main(int argc, char * argv[]){
	
	if(argc>1){
		//read in option
		string op = argv[1];
		string image1_name;
		string image2_name;
		string output_name;

		//based on option chosen, read in input image names and call appropritate functions
		if(op=="-a"){
			cout<<"-------------adding-----------------"<<endl;
			output_name = argv[4];
			MTNELL004::Image l1;
			MTNELL004::Image l2;
			MTNELL004::Image l3;

			l1.load(argv[2]);
			l2.load(argv[3]);
			
			l3 = l1+l2;

			l2.save("output.pgm");
			

		}
		else if (op=="-s"){
			output_name = argv[4];
			MTNELL004::Image l1;
			MTNELL004::Image l2;
			l1.load(argv[2]);
			l2.load(argv[3]);
		}
		else if(op=="-i"){
			cout<<"invert"<<endl;
			output_name = argv[3];
			MTNELL004::Image l1;
			l1.load(argv[2]);
		}
		else if(op=="-l"){
			cout<<"mask"<<endl;
			output_name = argv[4];
			MTNELL004::Image l1;
			MTNELL004::Image l2;
			l1.load(argv[2]);
			l2.load(argv[3]);
		}
		else if(op=="-t"){
			cout<<"threshold"<<endl;
			int threshold = MTNELL004::convertToInt(argv[3]);
			output_name = argv[4];
			MTNELL004::Image l1;
			l1.load(argv[2]);


		}
		else{
			cout << "invalid option chosed"<<endl;
		}

	}
	else{
		cout << "invalid arguments"<<endl;
	}




	return 0;
}