#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

///

template<typename T>
class FileArray {
public:

    class Reader
    {
    public:
        Reader(T &a, const char* filename, int &i)
        {
            this->smth = a;
            this->filename = filename;
            this->number = i;
        }
        Reader(Reader &obj) {}

        operator int() {return this->smth;}
        operator double() {return this->smth;}

        int operator = (T inc)
        {
            this->arrBuf = new T[10];
            ifstream* outThisFile = new ifstream;
            outThisFile->open(this->filename, ios::binary);
            outThisFile->seekg(0, outThisFile->beg);
            for (int i = 0; i < 10; i++) {outThisFile->read(reinterpret_cast<char*>(&(this->arrBuf[i])), sizeof(T));}
            this->arrBuf[number] = inc;
            outThisFile->close();
            delete outThisFile;
            ofstream* inThisFile = new ofstream;
            inThisFile->open(this->filename, ios::trunc | ios::binary);
            for (int i = 0; i < 10; i++) {inThisFile->write(reinterpret_cast<char*>(&(this->arrBuf[i])), sizeof(T));}
            inThisFile->close();
            delete inThisFile;
            delete this->arrBuf;
            return 0;
        }
    private:
        T smth, *arrBuf;
        int number;
        const char* filename;

    };

    FileArray(const char *filename) {this->filename = filename;}
    int size()
    {
        ifstream* outThisFile = new ifstream;
        outThisFile->open(this->filename, ios::binary);
        int ans = 0;
        outThisFile->seekg(0, outThisFile->end);
        ans = outThisFile->tellg() / sizeof(T);
        outThisFile->close();
        delete outThisFile;
        return ans;
    }

    Reader operator [] (int &i)
    {
        T a;
        ifstream* outThisFile = new ifstream;
        outThisFile->open(this->filename, ios::binary);
        outThisFile->seekg(i*sizeof(T), outThisFile->beg);
        outThisFile->read(reinterpret_cast<char*>(&a), sizeof(T));
        outThisFile->close();
        delete outThisFile;
        Reader obj(a, this->filename, i);
        return obj;
    }

private:
    const char* filename;
};

///

int main() {
	//test sequence
	//h
	//i426664d537775
	//0
	//753
	//0
	while (1){
		char ch;
		cin.get(ch);
		switch (ch) {
		case 'i':
		{
			ofstream out("txt.txt", ios::trunc | ios::binary);
			for (int i = 0; i < 10; i++) {
				out.write(reinterpret_cast<char*>(&i), sizeof(int));
			}

			out.close();
		}
		break;
		case 'd':
		{
			ofstream out("txt.txt", ios::trunc | ios::binary);
			double d = 0;
			for (int i = 0; i < 10; i++) {
				out.write(reinterpret_cast<char*>(&d), sizeof(double));
				d += 1.3333;
			}
			out.close();
		}
		break;
		case '2':
		{
			FileArray<int> t("txt.txt");
			for (int i = 0; i < t.size(); i++) {
				cout << int(t[i]) << " ";
			}
			cout << endl;
		}
		break;
		case '3':
		{
			FileArray<double> t("txt.txt");
			for (int i = 0; i < t.size(); i++) {
				cout << double(t[i]) << " ";
			}
			cout << endl;
		}
		break;
		case '4':
		{
			FileArray<int> t("txt.txt");
			cout << "count of int variables in txt.txt is " << t.size() << endl;
		}
		break;
		case '5':
		{
			FileArray<double> t("txt.txt");
			cout << "count of double variables in txt.txt is " << t.size() << endl;
		}
		break;
		case '6':
		{
			FileArray<int> t("txt.txt");
			for (int i = 0; i < t.size(); i++) {
				t[i] = (int(t[i]) + 1);
			}
		}
		break;
		case '7':
		{
			FileArray<double> t("txt.txt");
			for (int i = 0; i < t.size(); i++) {
				t[i] = (double(t[i]) + 1.1);
			}
		}
		break;
		case 'h':
			cout <<
				"i - create(replace) file with 10 int variables\n"
				"d - create(replace) file with 10 double variables\n"
				"2 - cout 10 int variables from file\n"
				"3 - cout 10 double variables from file\n"
				"4 - cout count of int variables in file\n"
				"5 - cout count of double variables in file\n"
				"6 - write +1 to each of int variables in file\n"
				"7 - write +1.1 to each of double variables in file\n"
				"h - this help\n"
				"0 - exit\n";
			break;
		case '0':
			return 0;
			break;
		}

	}
	return 0;
}