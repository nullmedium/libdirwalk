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
        //! No-op action. Calling this method does nothing.
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
        //! \brief Default constructor.
        //! 
        dirwalker()
            : filePolicy(),
              directoryPolicy(),
              symlinkPolicy() {
        }

        //! \brief Constructor to pass user-specific Policy objects to dirwalker class.
        //!
        //! \param fp FilePolicy object
        dirwalker(FilePolicy &fp)
            : filePolicy(fp),
              directoryPolicy(),
              symlinkPolicy() {
        }

        //! \brief Default desctructor.
        //! 
        ~dirwalker() {
        }

        //! 
        //! This method iterates over \e path and uses user-specified Policy objects to
        //! handle regular files, directories and symlinks.
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
