#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <thread>
#include <torch/script.h>

#include "intact.h"
#include "io.h"

void configTorch(
    std::vector<std::string>& classNames, torch::jit::script::Module& module)
{
    const std::string scriptName = io::pwd() + "/resources/torchscript.pt";
    const std::string cocoNames = io::pwd() + "/resources/coco.names";
    module = torch::jit::load(scriptName);
    std::ifstream f(cocoNames);
    std::string name;
    while (std::getline(f, name)) {
        classNames.push_back(name);
    }
}

void adapt(const int& index, Point& point, const int16_t* ptr_pcl,
    const uint8_t* ptr_img)
{

    int16_t x = ptr_pcl[3 * index + 0];
    int16_t y = ptr_pcl[3 * index + 1];
    int16_t z = ptr_pcl[3 * index + 2];

    uint8_t b = ptr_img[4 * index + 0];
    uint8_t g = ptr_img[4 * index + 1];
    uint8_t r = ptr_img[4 * index + 2];
    uint8_t a = ptr_img[4 * index + 3];

    int16_t xyz[3] = { x, y, z };
    uint8_t rgb[3] = { r, g, b };
    uint8_t bgra[4] = { b, g, r, a };

    point.m_id = index;
    point.setPoint(xyz);
    point.setPixel_GL(rgb);
    point.setPixel_CV(bgra);
}

bool invalid(const int& index, const int16_t* ptr_pcl, const uint8_t* ptr_img)
{
    if (ptr_pcl[3 * index + 0] == 0 && ptr_pcl[3 * index + 1] == 0
        && ptr_pcl[3 * index + 2] == 0) {
        return true;
    }

    if (ptr_img[4 * index + 0] == 0 && ptr_img[4 * index + 1] == 0
        && ptr_img[4 * index + 2] == 0 && ptr_img[4 * index + 3] == 0) {
        return true;
    }
    return false;
}

void addPoint(const int& index, int16_t* ptr_pcl)
{
    ptr_pcl[3 * index + 0] = 0;
    ptr_pcl[3 * index + 1] = 0;
    ptr_pcl[3 * index + 2] = 0;
}

void addPoint(const int& index, int16_t* ptr_pclDest, const int16_t* ptr_pclSrc)
{
    ptr_pclDest[3 * index + 0] = ptr_pclSrc[3 * index + 0];
    ptr_pclDest[3 * index + 1] = ptr_pclSrc[3 * index + 1];
    ptr_pclDest[3 * index + 2] = ptr_pclSrc[3 * index + 2];
}

void addPixel_CV(
    const int& index, uint8_t* ptr_imgDest, const uint8_t* ptr_imgSrc)
{
    ptr_imgDest[4 * index + 0] = ptr_imgSrc[4 * index + 0];
    ptr_imgDest[4 * index + 1] = ptr_imgSrc[4 * index + 1];
    ptr_imgDest[4 * index + 2] = ptr_imgSrc[4 * index + 2];
    ptr_imgDest[4 * index + 3] = ptr_imgSrc[4 * index + 3];
}

void addPixel_GL(
    const int& index, uint8_t* ptr_imgDest, const uint8_t* ptr_imgSrc)
{
    ptr_imgDest[3 * index + 2] = ptr_imgSrc[4 * index + 0];
    ptr_imgDest[3 * index + 1] = ptr_imgSrc[4 * index + 1];
    ptr_imgDest[3 * index + 0] = ptr_imgSrc[4 * index + 2];
}

void addPixel_CV(const int& index, uint8_t* ptr_img)
{
    ptr_img[4 * index + 0] = 0; // blue
    ptr_img[4 * index + 1] = 0; // green
    ptr_img[4 * index + 2] = 0; // red
    ptr_img[4 * index + 3] = 0; // alpha
}

void addPixel_GL(const int& index, uint8_t* ptr_img)
{
    ptr_img[3 * index + 0] = 0; // blue
    ptr_img[3 * index + 1] = 0; // green
    ptr_img[3 * index + 2] = 0; // red
}

bool inSegment(
    const int& index, const short* ptr_pcl, const Point& min, const Point& max)
{
    if (ptr_pcl[3 * index + 2] == 0) {
        return false;
    }

    if (max.m_xyz[2] == SHRT_MAX || min.m_xyz[2] == SHRT_MIN) {
        return false;
    }

    if ((int16_t)ptr_pcl[3 * index + 0] > max.m_xyz[0]
        || (int16_t)ptr_pcl[3 * index + 0] < min.m_xyz[0]
        || (int16_t)ptr_pcl[3 * index + 1] > max.m_xyz[1]
        || (int16_t)ptr_pcl[3 * index + 1] < min.m_xyz[1]
        || (int16_t)ptr_pcl[3 * index + 2] > max.m_xyz[2]
        || (int16_t)ptr_pcl[3 * index + 2] < min.m_xyz[2]) {
        return false;
    }
    return true;
}

#endif /*HELPERS_H */
