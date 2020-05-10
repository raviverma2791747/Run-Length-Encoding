#include <iostream>
#include<fstream>
#include<string>


class Encode : protected std::fstream //inheriting fstream class in protected mode
{
private:
    std::string path;     //input text file path 
    std::string output;  // output file path
public:
    //default constructor
    Encode() :
        path(),
        output("output.txt"),
        std::fstream()
    {

    }
    //parametrized constructorn with 1 arguement
    Encode(const std::string& path) :
        path(path),
        output( "output.txt"),
        std::fstream(path,std::ios::in)
    {
        if (!is_open())
        {
            std::cout << "Error opening file!";
        }
    }

    //parametrized constructor with 2 arguements
    Encode(const std::string& path,const std::string& output) :
        path(path),
        output(output),
        std::fstream(path, std::ios::in)
    {
        if (!is_open())
        {
            std::cout << "Error opening file!";
        }
    }

    //Destructor
    ~Encode()
    {
        if (is_open())
        {
            this->close();
        }
    }

    //overidden open function of fstream class
    void open(const std::string& path)    
    {
        this->path = path;
        std::fstream::open(path, std::ios::in);
        if (!is_open())
        {
            std::cout << "Error opening file!";
        }
    }

    void open(const std::string& path,const std::string& output)
    {
        this->path = path;
        this->output = output;
        std::fstream::open(path, std::ios::in);
        if (!is_open())
        {
            std::cout << "Error opening file!";
        }
    }

    //function to encode text file
    void encode()
    {
        if(!is_open())
        {
            std::cout << "File not opened!";
            return;
        }
        std::ofstream fout(output, std::ios::out);
        //Run length encoding 
        //eg. converts this string "aabbbcccc" into "a2b3c4"
        int count = 1; //store count 
        char curr_ch, prev_ch; 
        get(prev_ch);
        while (!eof())
        {
            get(curr_ch);
            while (curr_ch == prev_ch && !eof())
            {
                count += 1;
                prev_ch = curr_ch;
                get(curr_ch);
            }
            fout << prev_ch << count;
            prev_ch = curr_ch;
            count = 1;
        }
        close();
        fout.close();
    }

    //display encoded text file
    void print() 
    {
        std::ifstream fin(output,std::ios::in);
        char ch;
        while (fin.get(ch))
        {
            std::cout << ch;
        }
        fin.close();
    }
};

int main()
{
    Encode e;
    e.open("test.txt");
    e.encode();
    e.print();
    return 0;
}