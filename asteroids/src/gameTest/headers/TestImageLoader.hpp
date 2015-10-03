#ifndef _PJM_TESTIMAGELOADER_HPP_
#define _PJM_TESTIMAGELOADER_HPP_

#include <Renderable.hpp>
#include <ImageLoader.hpp>
#include <boost/shared_ptr.hpp>

struct TestImageLoader : public pjm::ImageLoader
{
    TestImageLoader()
        : loadSuccess(true)
    {}

    boost::shared_ptr<pjm::Renderable> loadFromFile(const std::string& iFilePath)
    {
        if (loadSuccess)
        {
            return renderable;
        }
        return boost::shared_ptr<pjm::Renderable>();
    }

    bool loadSuccess;
    boost::shared_ptr<pjm::Renderable> renderable;
};

#endif
