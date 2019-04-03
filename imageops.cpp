/**
*imageops.cpp file
*/

# include "imageops.h"
using namespace std;

namespace MTNELL004{

	int convertToInt(string str){
		int i;
		istringstream is(str);
		is >> i;
		return i;
	}

	//-------------------------------------------------Image functions-------------------------------------
	//constructor
	Image::Image(){

	}

	//destructor
	Image::~Image(){

	}

	//copy constructor
	Image::Image(const Image & rhs): width(rhs.width), height(rhs.height){
		int length = width*height;
		data.reset(new unsigned char[length]);

		int index = 0;
		for(Image::iterator i = rhs.begin(); i!=rhs.end(); ++i){
			data[++index] = *i;
		}

	}

	//move constructor
	Image::Image(Image && rhs): width(move(rhs.width)), height(move(rhs.height)){
		int length = width*height;
		data.reset(new unsigned char[length]);

		int index = 0;
		for(Image::iterator i = rhs.begin(); i!=rhs.end(); ++i){
			data[++index] = move(*i);
		}
	}

	//copy assignment operator
	Image & Image::operator=(const Image & rhs){
		width = rhs.width;
		height = rhs.height;

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while(beg!=end){
			*beg = *inStart; 
			++beg; ++inStart;
		}
		return *this;
	}
	
	//move assignment operator
	Image & Image::operator=(Image && rhs){
		width = move(width);
		height = move(height);

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while(beg!=end){
			*beg = move(*inStart); 
			++beg; ++inStart;
		}
		return *this;

	}
	
	void Image::printVals(){
		cout<<(float)data[10000]<<endl;
	}


	Image & Image::operator+=(const Image & rhs){

	}

	Image Image::operator+(const Image & rhs){
		Image result = *this;
		result += rhs;
		return result;
	}



	void Image::load(string input){
		//first read header info
		//open the file
		ifstream f;
		f.open(input);
		if(!f){
			cerr << "File not found\n";
			f.close();
		}

		//read in dimensions and use them to set class variables
		int rows, cols;
		string line;
		getline(f, line);
		if(line == "P5"){
			bool comments = true;
			while(comments){
				getline(f, line);
				if(line[0]!='#'){
					comments = false;
				}
			}
			stringstream l;
			l<<line;
			l>>rows>>ws>>cols;
			getline(f, line); //will read the 255 line

			// get length of file:
			int length = rows*cols;

			//create a memory block for it
		    char* img = new char[length];

		    //read in from binary file. "img" pointer points to where it is stored
		    f.read (img,length);

		    //cast it to an unsigned char * array
		    unsigned char *u_img = (unsigned char *)img;

		    //set members of the image
		    width = cols;
		    height = rows;
		    data.reset(new unsigned char[length]);

		    for(int i =0; i<length; i++){
		    	data[i]=u_img[i];
		    }

		    delete [] img;
		    //delete [] u_img;
		}

		else{
			cout<<"invalid PGM pic"<<endl;
		}

		f.close();
	}
	void Image::save(string output){

		int length = width*height;
		char* img = new char[length];
		int index = 0;
		
		for(Image::iterator i = begin(); i!=end(); ++i){
			img[++index] = *i;
		}

		//create output file
	    ofstream myfile;
	  	myfile.open (output);
	    myfile << "P5\n"<<height<<" "<<width<<"\n255\n";
	  	myfile.write (img,length);
	  	myfile.close();

	  	delete [] img;
	}
	//-------------------------------------------------Image::iterator functions-------------------------------------

	Image::iterator::iterator(u_char *p): ptr(p){}

	Image::iterator::iterator(const Image::iterator & rhs): ptr(rhs.ptr){}

	Image::iterator & Image::iterator::operator=(const Image::iterator & rhs){
		ptr = rhs.ptr;
		return *this;
	}

	unsigned char & Image::iterator::operator*() {
		return *ptr;
	}

	Image::iterator & Image::iterator::operator++(){
		++ptr;
		return *this;
	}

	Image::iterator & Image::iterator::operator--(){
		--ptr;
		return *this;
	}

	bool Image::iterator::operator !=(const Image::iterator & rhs){
		return ptr != rhs.ptr;
	}

	Image::iterator Image::begin(void) const{
		return Image::iterator(data.get());
	}
	Image::iterator Image::end(void) const{
		return Image::iterator(data.get()+(width*height));
	}

}