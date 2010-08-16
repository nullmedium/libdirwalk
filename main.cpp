/*
 *  main.cpp
 *  dirwalk
 *
 *  Created by Jens Luedicke on 7/9/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

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
