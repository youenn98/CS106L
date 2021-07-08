#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;

/*
 * Note that you have to pass in the file as a single string
 * into the findWikiLinks function!
 * So we have to turn the passed-in file into a single string...
 * does that sound familiar at all?
 */
unordered_set<string> findWikiLinks(const string& page_html) {
    // TODO: delete this return statement and implement
    // the function!
    unordered_set<string> link_found;
    const string pattern = "<a href=\"/wiki/";
    const string split = "/\">";
    auto beg = page_html.begin();
    auto found =  page_html.begin();
    while((found = search(beg,page_html.end(),pattern.begin(),pattern.end())) != page_html.end()){
        beg = found;
        char ch = *found;
        while(split.find(ch) != std::string::npos && found!=page_html.end()){
            found++;
        }
        string linkstr(beg,found);
        link_found.insert(linkstr);
    }
    return link_found;
}

int main() {
    /* Note if your file reading isn't working, please go to the
     * projects tab on the panel on the left, and in the run section,
     * uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */

    cout << "Enter a file name: ";
    string filename;
    getline(std::cin, filename);

    // TODO:
    // - create a filestream from the filename, and convert
    //   it into a single string of data
    // - findWikiLinks
    // - print out the links you found, and use the provided
    //   test files under "Other files/res" to check whether
    //   your findWikiLinks function is working correctly!
    //
    // You got this!

    // Write code here
    std::fstream input_file(filename);
    std::string file_str;
    if(input_file.is_open()){
        std::stringstream  ss;
        ss << input_file.rdbuf();
        file_str = ss.str();
    }else{
        printf("Cannot open file %s\n",filename.c_str());
        return -1;
    }
    unordered_set<string> st = findWikiLinks(file_str);
    for(auto &a: st){
        cout << a << endl;
    }
}
