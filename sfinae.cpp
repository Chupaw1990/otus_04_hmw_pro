#include <iostream>
#include <vector>
#include "sfinae.h"

int main(){
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip<std::vector<int>>(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    print_ip<std::list<int>>(std::list<int>{400, 300, 200, 100});// 400.300.200.100
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0

    return 0;
}