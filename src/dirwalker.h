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

    //! \brief Default no-op policy.
    //!
    //! A policy needs to implement an action method.
    struct default_policy {
        void action(const boost::filesystem::path &p) {
        }
    };

    //! \class dirwalker
    //! \brief dirwalker class
    template
    <
        class FilePolicy,
        class DirectoryPolicy = default_policy,
        class SymlinkPolicy = default_policy
    >
    class dirwalker : public boost::noncopyable {
    public:
        //! \fn dirwalker
        //! \brief Default ctor.
        //! 
        dirwalker()
            : filePolicy(),
              directoryPolicy(),
              symlinkPolicy() {
        }

        //! \fn dirwalker
        //! \brief ctor
        //!
        //! Constructor to pass user-specific Policy objects to dirwalker class.
        //!
        //! \param fp FilePolicy object
        //! \param dp DirectoryPolicy object
        //! \param sp SymlinkPolicy object
        dirwalker(FilePolicy &fp,
                  DirectoryPolicy &dp = DirectoryPolicy(),
                  SymlinkPolicy &sp = SymlinkPolicy())
            : filePolicy(fp),
              directoryPolicy(dp),
              symlinkPolicy(sp) {
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

    template
    <
        class FilePolicy,
        class DirectoryPolicy = default_policy,
        class SymlinkPolicy = default_policy
    >
    void walk_directory_tree(const boost::filesystem::path &path) {
        dirwalker<FilePolicy,DirectoryPolicy,SymlinkPolicy> dw;
        dw.walk(path);
    }
}
