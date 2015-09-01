#ifndef _PJM_TESTIMAGELOADER_HPP_
#define _PJM_TESTIMAGELOADER_HPP_

#include <Renderable.hpp>
#include <ImageLoader.hpp>

struct TestImageLoader : public pjm::ImageLoader
{
    TestImageLoader()
        : loadSuccess(true),
          renderable(NULL)
    {}

    pjm::Renderable* loadFromFile(const std::string& iFilePath)
    {
        if (loadSuccess)
        {
            return renderable;
        }
        return NULL;
    }

    bool loadSuccess;
    pjm::Renderable* renderable;
};

#endif
