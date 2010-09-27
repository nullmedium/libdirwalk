//! \file dirwalker.h
//! \brief C++ Library (header-only).

//  dirwalker.h  -------------------------------------------------------------//

// 
// Copyright Jens Luedicke 2010
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------------------------// 

#include <iostream>
#include <fstream>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/filesystem.hpp>

//! \namespace dirwalk
//! \brief C++ Namespace of Library
namespace dirwalk {

    struct default_policy {
        void action(const boost::filesystem::path &p) {
        }
    };

    //! \class dirwalker
    //! \brief Dirwalker class
    template <
        class FilePolicy = default_policy,
        class DirectoryPolicy = default_policy,
        class SymlinkPolicy = default_policy
        >
    class dirwalker : public boost::noncopyable {
    public:
        //! \fn dirwalker
        //! \brief Default ctor.
        //! 
        dirwalker() {
        }

        //! \fn ~dirwalker
        //! \brief Default dtor.
        //! 
        ~dirwalker() {
        }

        //! 
        //! Walking method.
        //! 
        bool walk(const boost::filesystem::path &path) {
            using namespace boost::filesystem;

            directory_iterator end_itr; // default construction yields past-the-end

            for (directory_iterator itr( path ); itr != end_itr; ++itr) {

                if ( is_symlink( itr->status() ) ) {
                    
                    symlinkPolicy.action( itr->path() );
                    
                } else if ( is_directory( itr->status() ) ) {

                    directoryPolicy.action( itr->path() );

                    //! \todo Fix this!
                    const std::string &path = itr->path().string();
                    std::ifstream check( path.c_str(), std::ios::in );

                    if ( check.good() ) {
                        this->walk( itr->path() );
                    }

                } else if ( is_regular_file( itr->status() ) ) {

                    filePolicy.action( itr->path() );

                } else {
                    
                }
            }
        }

    private:
        //! @{
        FilePolicy      filePolicy;
        DirectoryPolicy directoryPolicy;
        SymlinkPolicy   symlinkPolicy;
        //! @}
    };
}
