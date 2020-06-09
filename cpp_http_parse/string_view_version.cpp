#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <chrono>

using namespace std;
using namespace std::chrono;

std::tuple<std::string_view,std::string_view,std::string_view> split_http(std::string_view s){

        std::string_view version = "";
        std::string_view status = "";
        std::string_view description = "";

        size_t found = s.find(' ');
        if (found != std::string::npos) {
                version = s.substr(0,found);
        }
        size_t found1 = s.find(' ',found +1);
        if (found1 != std::string::npos) {
                status = s.substr(found+1,found1 - found);
        }
        description = s.substr(found1+1,s.length());
        return std::make_tuple(version,status,description);
}

int main(){

        std::string_view s = std::string("HTTP/1.1 418 I'm a teapot\r\n");

        auto start = high_resolution_clock::now();
        //for (int i = 0 ; i < 100000000 ; i++){
        for (int i = 0 ; i < 1 ; i++){
                auto [version,status,description] = split_http(s);
		std::cout << "Version: "<< version << std::endl;
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

        return 0;
}
