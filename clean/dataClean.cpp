#include<iostream> 
#include<fstream> 

using namespace std;
int dataClean()
{
    ifstream in("qhulldata.txt"); 
    ofstream out( "usefuldata.txt" ); 
    if (!in){
        cout <<"open source file error!"<<endl;
        return -1;
    }
	const int LINE_LENGTH = 100; 
    	char str[LINE_LENGTH];  
   	 while( in.getline(str,LINE_LENGTH) )
    	{    
       		cout << "Read from file: " << str << endl;
		if(str[2]==str[3]||str[4]==str[5]
		||str[6]==str[7]){}
		else if(str[2] > str[3]||str[4] > str[5]
		||str[6] > str[7]){}
		else
		{
			out<<str<<endl;
		}
    	}
    in.close();
    out.close();
    return 0;
}

int main()
{
	dataClean();
	return 0;	
}

//123