#include <iostream>

#ifndef USITVERSION
#define USITVERSION "v3.0.0"
#endif //USITVERSION

void printVersionString(std::string str, std::string delim="|", std::string fill=" ", int off= 10, int width=55){
    std::string s = "";
    for(auto c=off; c>0;c--)s+=" ";
    s+=delim;
    int fillcount= width-str.length();
    auto c=0;
    for(; c<fillcount/2;c++)s+=fill;
    s+=str;
    for(; c<fillcount;c++)s+=fill;
    s+=delim;
    std::cout<<s<<std::endl;
}
void printVersion(){
    printVersionString("", "+", "-");
    printVersionString("University of Salzburg Iris Toolkit");
    printVersionString("http://wavelab.at/sources/USIT");
    printVersionString("Version " USITVERSION);
    printVersionString("", "+", "-");
}
