#ifndef _PJM_IMAGELOADER_HPP_
#define _PJM_IMAGELOADER_HPP_

#include <Renderable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

namespace pjm
{
    struct ImageLoader
    {
        virtual boost::shared_ptr<Renderable> loadFromFile(const std::string& iFilePath) = 0;

        virtual ~ImageLoader() {}
    };
}

#endif
