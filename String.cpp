#include <iostream>
#include <cstdio>
#include <string.h>
#include "List.cpp"
using namespace std;

class String{
public:
    String();
    ~String();
    String(const String& in_string);
    String(const char* in_string);
    String(List<char>& in_string);
    void operator=(const String &in_string);
    int size()const;
    const char* c_str()const;
protected:
    char* entries;
    int length;
};

String::String(){
    length = 0;
    entries = new char(1);
    entries[0] = '\0';
}

int String::size()const{
    return length;
}


String::String(const char* in_string){
    length = strlen(in_string);
    entries = new char(length+1);
    strcpy(entries, in_string);
}

String::String(const String& in_string){
    length = in_string.size();
    entries = new char(length+1);
    const char* rem = in_string.c_str();
    strcpy(entries, rem);
}

String::String(List<char>& in_string){
    length = in_string.size();
    entries = new char(length+1);
    for(int i=0; i<length; i++)
        in_string.retrieve(i, entries[i]);
    entries[length] = '\0';
}

void String::operator=(const String &in_string){
    delete entries;
    length = in_string.size();
    entries = new char(length+1);
    const char* rem = in_string.c_str();
    strcpy(entries, rem);
}

void String::operator=(const char* in_string){
    delete entries;
    length = strlen(in_string);
    entries = new char(length+1);
    strcpy(entries, in_string);
}

const char* String::c_str()const{
    return (const char*)entries;
}

bool operator==(const String &first, const String &second){
    return strcmp(first.c_str(), second.c_str()) == 0;
}

bool operator>(const String &first, const String &second){
    return strcmp(first.c_str(), second.c_str()) > 0;
}

bool operator<(const String &first, const String &second){
    return strcmp(first.c_str(), second.c_str()) < 0;
}

bool operator>=(const String &first, const String &second){
    return strcmp(first.c_str(), second.c_str()) >= 0;
}

bool operator<=(const String &first, const String &second){
    return strcmp(first.c_str(), second.c_str()) <= 0;
}

bool operator!=(const String &first, const String &second){
    return strcmp(first.c_str(), second.c_str()) != 0;
}

void strcat(String& add_to, const String& add_on){
    const char* cfirst = add_to.c_str();
    const char* csecond = add_on.c_str();
    char* copy = new char[strlen(cfirst) + strlen(csecond) +1];
    strcpy(copy, cfirst);
    strcat(copy, csecond);
    add_to = copy;
    delete [] copy;
}

String read_in(istream &input){
    List<char>temp;
    int size = 0;
    char c;
    while((c = input.peek()) != EOF && (c = input.get() != '\n'))
        temp.insert(size++, c);
    String answer(temp);
    return answer;
}

void write(String &s){
    cout << s.c_str() <<endl;
}
















