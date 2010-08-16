//  example/main.cpp  ---------------------------------------------------------//

// 
// Copyright Jens Luedicke 2010
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//----------------------------------------------------------------------------// 

#include <iostream>
#include <map>

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals2/signal.hpp>

namespace dirwalker {

    class dirwalker : public boost::noncopyable {
        typedef boost::signals2::signal<void (const boost::filesystem::path &)> OnDirectoryEnter;
        typedef boost::signals2::signal<void (const boost::filesystem::path &)> OnDirectoryLeaving;
        typedef boost::signals2::signal<void (const boost::filesystem::path &)> OnFile;

    public:
        typedef OnDirectoryEnter::slot_type OnDirectoryEnterSlotType;
        typedef OnDirectoryEnter::slot_type OnDirectoryLeavingSlotType;
        typedef OnDirectoryEnter::slot_type OnFileSlotType;

        dirwalker() {
        }
        ~dirwalker() {
        }

        boost::signals2::connection doOnDirectoryEnter(const OnDirectoryEnterSlotType & slot) {
            return onDirectoryEnter.connect(slot);
        }

        boost::signals2::connection doOnDirectoryLeaving(const OnDirectoryLeavingSlotType & slot) {
            return onDirectoryLeaving.connect(slot);
        }

        boost::signals2::connection doOnFile(const OnFileSlotType & slot) {
            return onFile.connect(slot);
        }

        bool walk(const boost::filesystem::path &path) {
            using namespace boost::filesystem;

            directory_iterator end_itr; // default construction yields past-the-end

            for (directory_iterator itr( path ); itr != end_itr; ++itr) {
                if ( is_symlink( itr->status() ) ) {
                    
                } else if ( is_directory( itr->status() ) ) {
                    onDirectoryEnter( itr->path() );

                    this->walk(itr->path());

                    onDirectoryLeaving( itr->path() );

                } else if ( is_regular_file( itr->status() ) ) {

                    onFile( itr->path() );

                } else {
                    
                }
            }
        }

    private:
        OnDirectoryEnter   onDirectoryEnter;
        OnDirectoryLeaving onDirectoryLeaving;
        OnFile             onFile;
    };
}
