//
// Created by nunol on 8/7/2018.
//

#include <cstdlib>
#include <iostream>

#include <Entity.h>
#include <Subject.hpp>
#include <boost/filesystem.hpp>

int main()
{
    auto e = new Entity();
    auto val = e->description == "My Description";

    std::cout << val << std::endl;

    std::cout << "Application" << std::endl;
    return EXIT_SUCCESS;
}
