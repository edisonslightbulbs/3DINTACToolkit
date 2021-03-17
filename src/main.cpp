#include <vector>

#include "dbscan.h"
#include "io.h"
#include "knn.h"
#include "point.h"
#include "lda.h"
#include "sampler.h"
#include "elbow.h"
#include "svd.h"
#include "area.h"
#include "segmenter.h"

extern const int FAIL = -3;
extern const int PASS = 0;
const int tweak = 60;

static std::vector<Point> segment(std::vector<Point> points){
    Timer timer;
    /** do linear analysis */
    std::vector<Point> refined = lda::analyze(points);

    /** grow course segment  */
    std::vector<Point> roi = svd::segment(refined);

    /** segment tabletop interaction context */
    std::vector<Point> context = roi::segment(roi);
    LOG(INFO) << "..........................................................";
    LOG(INFO) << timer.getDuration() << " ms: total segmentation runtime (!unoptimized!)";

    return context;
}

int main(int argc, char* argv[])
{
    /** initialize logger */
    logger(argc, argv);

    /** developer testing point cloud */
    std::vector<Point> points;
    const std::string DATA = io::pwd() + "/resources/inputdata.ply";
    points = io::read(points, DATA.c_str());

    /** segment tabletop interaction context */
    std::vector<Point> context = segment(points);

    return PASS;
}
