//  example/dirwalker.cpp  ----------------------------------------------------//

// 
// Copyright Jens Luedicke 2010
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------------------------// 

#include "dirwalker.h"

struct FilePolicy {
    void action(const boost::filesystem::path &path) {
        std::cout << "file: " << path.string() << std::endl;
    }
};

struct DirectoryPolicy {
    void action(const boost::filesystem::path &path) {
        std::cout << "dir: " << path.string() << std::endl;
    }
};

int main(int argc, char *argv[]) {
    dirwalk::dirwalker<FilePolicy, DirectoryPolicy> dw;

    if (argc > 1) {
        dw.walk(boost::filesystem::path(argv[1]));
    }
    
    return 0;
}
