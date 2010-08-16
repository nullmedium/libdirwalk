//  example/main.cpp  ---------------------------------------------------------//

// 
// Copyright Jens Luedicke 2010
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------------------------// 

#include "dirwalker.h"

void printFilename(const boost::filesystem::path &path) {
    std::cout << path.string() << std::endl;
}

int main(int argc, char *argv[]) {
    dirwalker::dirwalker dw;

    dw.doOnFile(&printFilename);
    
    dw.walk(boost::filesystem::path("/Users/jens"));
    
    return 0;
}
