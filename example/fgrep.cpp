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

    Grepper() {
    }

    Grepper(const std::string &pattern) : str(pattern) {
    }

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
    using namespace dirwalk;

    if (argc > 2) {
        const std::string grep_pattern(argv[1]);
        const boost::filesystem::path path(argv[2]);

        Grepper grepper(grep_pattern);

        dirwalker<Grepper> dw(grepper);

        dw.walk(path);
    } else {
        std::cout << "usage: fgrep <pattern> <directory>" << std::endl;
    }
    
    return 0;
}
