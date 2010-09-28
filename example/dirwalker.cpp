//  example/dirwalker.cpp  ----------------------------------------------------//

// 
// Copyright Jens Luedicke 2010
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------------------------// 

#include "dirwalker.h"

using namespace dirwalk;
using namespace boost::filesystem;

struct FilePolicy {
    void action(const path &path) {
        std::cout << "file: " << path.string() << std::endl;
    }
};

struct DirectoryPolicy {
    void action(const path &path) {
        std::cout << "dir: " << path.string() << std::endl;
    }
};

int main(int argc, char *argv[]) {

    if (argc > 1) {
        dirwalker<FilePolicy, DirectoryPolicy> dw;

        path p(argv[1]);

        dw.walk(p);
    }
    
    return 0;
}
