/** \file dirwalker.h
*  dirwalker
*/

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

        boost::signals2::connection doOnFile(const OnFileSlotType & slot) {
            return onFile.connect(slot);
        }

        bool walk(const boost::filesystem::path &path) {
            using namespace boost::filesystem;

            directory_iterator end_itr; // default construction yields past-the-end

            for (directory_iterator itr( path ); itr != end_itr; ++itr) {
                if ( is_directory(itr->status()) ) {

                    onDirectoryEnter( itr->path() );

                    this->walk(itr->path());

                    onDirectoryLeaving( itr->path() );

                } else {
                    onFile( itr->path() );
                }
            }
        }

    private:
        OnDirectoryEnter   onDirectoryEnter;
        OnDirectoryLeaving onDirectoryLeaving;
        OnFile             onFile;
    };
}