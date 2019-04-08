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

	Image::Image(int w, int h, unsigned char * d): width(w), height (h){
		int length = width*height;
		data = unique_ptr<unsigned char[]>(new unsigned char[length]);

		Image::iterator beg = this->begin(), end = this->end();
		int counter = 0;

		while(beg!=end){
			*beg = d[counter]; 
			++beg; ++counter;
		}
	}

	//destructor
	Image::~Image(){

	}

	//copy constructor
	Image::Image(const Image & rhs): width(rhs.width), height(rhs.height){
		int length = width*height;
		data = unique_ptr<unsigned char[]>(new unsigned char[length]);

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while(beg!=end){
			*beg = *inStart; 
			++beg; ++inStart;
		}

	}

	//move constructor
	Image::Image(Image && rhs): width(move(rhs.width)), height(move(rhs.height)){
		int length = width*height;
		data.reset(new unsigned char[length]);

		int index = 0;
		for(Image::iterator i = rhs.begin(); i!=rhs.end(); ++i){
			data[index++] = std::move(*i);
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
		width = move(rhs.width);
		height = move(rhs.height);
		data = move(rhs.data);

		return *this;

	}
	
	void Image::printVals(){
		cout<<(float)data[10000]<<endl;
	}


	Image & Image::operator+=(const Image & rhs){
		
		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while(beg!=end){
			if((float)*beg+(float)*inStart > 255){
				*beg = 255;
			}
			else{
				*beg += *inStart;
			}
			++beg; ++inStart;
		}
		
		return *this;
	}

	Image Image::operator+(const Image & rhs) const{
		Image result = *this;
		result += rhs;
		
		return result;
	}

	Image & Image::operator-=(const Image & rhs){
		
		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator inStart = rhs.begin(), inEnd = rhs.end();

		while(beg!=end){
			if((float)*beg-(float)*inStart < 0){
				*beg = 0;
			}
			else{
				*beg -= *inStart;
			}
			++beg; ++inStart;
		}
		
		return *this;
	}

	Image Image::operator-(const Image & rhs) const{
		Image result = *this;
		result -= rhs;
		
		return result;
	}

	Image Image::operator!(void) const{
		Image result = *this;

		Image::iterator beg = result.begin(), end = result.end();
		while(beg!=end){
			*beg = 255-*beg;
			++beg; 
		}
		
		return result;
	}

	Image Image::operator/(const Image & rhs) const{
		Image result = *this;

		Image::iterator res_beg = result.begin(), res_end = result.end();
		Image::iterator mask_start = rhs.begin(), mask_end = rhs.end();

		while(res_beg!=res_end){
			if(*mask_start!=255){
				*res_beg = 0;
			}
			++res_beg; ++mask_start;
		}

		return result;
	}

	Image Image::operator*(int thresh) const{
		Image result = *this;

		Image::iterator beg = this->begin(), end = this->end();
		Image::iterator res_beg = result.begin(), res_end = result.end();

		while(beg!=end){
			if(*beg>thresh){
				*res_beg = 255;
			}
			else{
				*res_beg = 0;
			}
			++beg; ++res_beg;
		}

		return result;
	}

	Image Image::operator%(std::string g) const{
		Image result = *this;

		//open filter file
		ifstream f;
		f.open(g);
		if(!f){
			cerr << "File not found\n";
			f.close();
		}
		
		//build array for filter
		int N;
		f>>N>>ws;
		float arr[N][N];
		for(int i = 0; i<N; i++){
			for(int j = 0; j<N; j++){
				f>>arr[i][j]>>ws;
			}
		}

		//build 2D array from image
		unsigned char img[height][width];
		//unsigned char img_result[height][width];
		Image::iterator beg = this->begin(), end = this->end();
		

		for(int i = 0; i<height; i++){
			for(int j = 0; j<width; j++){
				img[i][j] = *beg;
				++beg;
			}
		}

		Image::iterator res_beg = result.begin(), res_end = result.end();

		int span = (N-1)/2;
		int & m = span;
		int sum, row, col;
		for(int i = 0; i<height; i++){
			for(int j = 0; j<width; j++){
				sum = 0;
				for(int x = -span; x<span; x++){
					for(int y = -span; y<span; y++){
						
						if(col>=width){
							col = 2*width-col-1;
						}
						else if(col<0){
							col = -col;
						}
						else{
							col = j+y;
						}
						if(row>=height){
							row = 2*height-row-1;
						}
						else if(row<0){
							row = -row;
						}
						else{
							row = i+x;
						}
						sum+= (img[row][col])*(arr[m+x][m+y]);
					}
				}
				*res_beg=sum;
				++res_beg;

			}
		}
		
		f.close();
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
			img[index++] = *i;
		}
		
		//create output file
	    ofstream myfile;
	  	myfile.open (output);
	    myfile << "P5\n"<<height<<" "<<width<<"\n255\n";
	  	myfile.write (img,length);
	  	myfile.close();
	  
	  	delete [] img;
	}

	int Image::getWidth(void){
		return width;
	}

	int Image::getHeight(void){
		return height;
	}

	unsigned char * Image::getData(void){
		return data.get();
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

	Image::iterator & Image::iterator::operator+(int offset){
		ptr+=offset;
		return *this;
	}
	Image::iterator & Image::iterator::operator-(int offset){
		ptr-=offset;
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






