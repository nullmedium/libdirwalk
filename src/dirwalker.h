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
#include <boost/signals2/signal.hpp>

//! \namespace dirwalk
//! \brief C++ Namespace of Library
namespace dirwalk {

    //! 
    //! \brief Response-code
    //! 
    enum ResponseCode {
        Success,
        Failed,
        Aborted,
        Prune
    };

    //! \class dirwalker
    //! \brief Dirwalker class
    class dirwalker : public boost::noncopyable {
        typedef boost::signals2::signal<void (const boost::filesystem::path &)> OnDirectoryEnter;
        typedef boost::signals2::signal<void (const boost::filesystem::path &)> OnDirectoryLeaving;
        typedef boost::signals2::signal<void (const boost::filesystem::path &)> OnFile;

    public:
        //! Type-definition for callback/slot function.
        typedef OnDirectoryEnter::slot_type   OnDirectoryEnterSlotType;

        //! Type-definition for callback/slot function.
        typedef OnDirectoryLeaving::slot_type OnDirectoryLeavingSlotType;

        //! Type-definition for callback/slot function.
        typedef OnFile::slot_type             OnFileSlotType;

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

        /// \addtogroup Signals
        /// @{

        //! 
        //! Connect slot to be called when entering a directory
        //! 
        boost::signals2::connection doOnDirectoryEnter(const OnDirectoryEnterSlotType & slot) {
            return onDirectoryEnter.connect(slot);
        }

        //! 
        //! Connect slot to be called when leaving a directory
        //! 
        boost::signals2::connection doOnDirectoryLeaving(const OnDirectoryLeavingSlotType & slot) {
            return onDirectoryLeaving.connect(slot);
        }

        //! 
        //! Connect slot to be called on regular files.
        //! 
        boost::signals2::connection doOnFile(const OnFileSlotType & slot) {
            return onFile.connect(slot);
        }

        /// @}

        //! 
        //! Walking method.
        //! 
        bool walk(const boost::filesystem::path &path, std::string globPattern = "*") {
            using namespace boost::filesystem;

            directory_iterator end_itr; // default construction yields past-the-end

            for (directory_iterator itr( path ); itr != end_itr; ++itr) {

                if ( is_symlink( itr->status() ) ) {
                    
                } else if ( is_directory( itr->status() ) ) {

                    onDirectoryEnter( itr->path() );

                    //! \todo Fix this!
                    std::ifstream check( itr->path().string().c_str(), std::ios::in );

                    if ( check.good() ) {
                        this->walk( itr->path() );
                    }

                    onDirectoryLeaving( itr->path() );

                } else if ( is_regular_file( itr->status() ) ) {

                    onFile( itr->path() );

                } else {
                    
                }
            }
        }

    private:
        //! @{
        OnDirectoryEnter   onDirectoryEnter;
        OnDirectoryLeaving onDirectoryLeaving;
        OnFile             onFile;
        //! @}
    };
}
