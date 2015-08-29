#ifndef _PJM_SCREEN_INFO_HPP_
#define _PJM_SCREEN_INFO_HPP_

namespace pjm
{
    struct ScreenInfo
    {
        ScreenInfo(const std::string iTitle,
                   int iWidth,
                   int iHeight)
            : title(iTitle),
              width(iWidth),
              height(iHeight)
        {}

        std::string title;
        int width;
        int height;
    };
}

#endif
