#ifndef _PJM_IMAGELOADER_HPP_
#define _PJM_IMAGELOADER_HPP_

#include <Renderable.hpp>

namespace pjm
{
    struct ImageLoader
    {
        virtual Renderable* loadFromFile(const std::string& iFileName) = 0;

        virtual ~ImageLoader() {}
    };
}

#endif
