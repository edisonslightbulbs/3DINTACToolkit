#include <thread>

#include "intact.h"
#include "kinect.h"

extern const int FAIL = -3;
extern const int PASS = 0;

void work(std::shared_ptr<Kinect> sptr_kinect)
{
    /** segment in separate worker thread */
    std::thread segmenting(intact::segment, std::ref(sptr_kinect));

    /** render in separate worker thread */
    std::thread rendering(intact::render, std::ref(sptr_kinect));

    /** manage worker threads */
    segmenting.join();
    rendering.join();
}

int main(int argc, char* argv[])
{
    logger(argc, argv);
    std::shared_ptr<Kinect> sptr_kinect(new Kinect);
    work(sptr_kinect);
    return PASS;
}
