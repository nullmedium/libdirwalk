//  example/fgrep.cpp  -------------------------------------------------------//

// 
// Copyright Jens Luedicke 2010
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------------------------// 

#include <iostream>
#include <fstream>

#include "dirwalker.h"

struct Grepper {
    void action(const boost::filesystem::path &path) {
        std::ifstream in(path.string().c_str(), std::ios::in);

        int lineNum = 0;

        while (in.good()) {
            char line[1024];
            in.getline(line, 1024);

            ++lineNum;

            if (std::string(line).find(str) != std::string::npos) {
                std::cout << path.string() << ":" << lineNum << std::endl;
            }
        }
    }

    std::string str;
};


int main(int argc, char *argv[]) {
    dirwalk::dirwalker<Grepper> dw;

    if (argc > 2) {
        dw.walk(boost::filesystem::path(argv[2]));
    } else {
        std::cout << "usage: fgrep <pattern> <directory>" << std::endl;
    }
    
    return 0;
}
