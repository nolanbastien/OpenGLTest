#include "SkyBox.h"

SkyBox::SkyBox()
    : ib(
        new unsigned int[] {
                0, 1, 2,
                0, 2, 3,

                4, 2, 1,
                4, 5, 2,

                7, 5, 4,
                7, 4, 6,

                3, 7, 6,
                3, 6, 0,

                5, 7, 3,
                5, 3, 2,

                4, 1, 0,
                4, 0, 6

        }, 3 * 2 * 6)
{
    
}
