// embree_toy.cc
// Copyright Laurence Emms 2021

// A toy embree tracer

#include <iostream>

#include <embree3/rtcore.h>

namespace embree_toy {

void errorFunction(void* user_ptr, enum RTCError error, const char* str) {

    std::cerr << "Error " << error << ": " << str << std::endl;
}

RTCDevice initialize_device() {

    RTCDevice device = rtcNewDevice(nullptr);

    if (!device) {
        std::cerr << "Error " << rtcGetDeviceError(nullptr) << " cannot create device" << std::endl;
    }

    return device;
}

RTCScene initialize_scene(RTCDevice device) {

    RTCScene scene = rtcNewScene(device);

    RTCGeometry geometry = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);
    float* vertices = reinterpret_cast<float*>(
            rtcSetNewGeometryBuffer(
                geometry,
                RTC_BUFFER_TYPE_VERTEX,
                0,
                RTC_FORMAT_FLOAT3,
                3 * sizeof(float),
                3));

    unsigned int* indices = reinterpret_cast<unsigned int*>(
            rtcSetNewGeometryBuffer(
                geometry,
                RTC_BUFFER_TYPE_INDEX,
                0,
                RTC_FORMAT_UINT3,
                3 * sizeof(unsigned int),
                1));

    if (vertices != nullptr && indices != nullptr) {
        vertices[0] = 0.0f;
        vertices[1] = 0.0f;
        vertices[2] = 0.0f;
        vertices[3] = 1.0f;
        vertices[4] = 0.0f;
        vertices[5] = 0.0f;
        vertices[6] = 0.0f;
        vertices[7] = 1.0f;
        vertices[8] = 0.0f;

        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
    }

    rtcCommitGeometry(geometry);

    rtcAttachGeometry(scene, geometry);
    rtcReleaseGeometry(geometry);
    rtcCommitScene(scene);

    return scene;
}

void cast_ray(RTCScene scene, 
              float ox, float oy, float oz,
              float dx, float dy, float dz) {

    struct RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    struct RTCRayHit ray_hit;
    ray_hit.ray.org_x = ox;
    ray_hit.ray.org_y = oy;
    ray_hit.ray.org_z = oz;
    ray_hit.ray.dir_x = dx;
    ray_hit.ray.dir_y = dy;
    ray_hit.ray.dir_z = dz;
    ray_hit.ray.tnear = 0;
    ray_hit.ray.tfar = std::numeric_limits<float>::infinity();
    ray_hit.ray.mask = -1;
    ray_hit.ray.flags = 0;
    ray_hit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
    ray_hit.hit.instID[0] = RTC_INVALID_GEOMETRY_ID;

    rtcIntersect1(scene, &context, &ray_hit);

    std::cout << ox << ", " << oy << ", " << oz << std::endl;
    if (ray_hit.hit.geomID != RTC_INVALID_GEOMETRY_ID) {
        std::cout << "Found intersection on geometry " 
            << ray_hit.hit.geomID
            << " primitive "
            << ray_hit.hit.primID
            << " at tfar="
            << ray_hit.ray.tfar
            << std::endl;
    } else {
        std::cout << "Did not find any intersection." << std::endl;
    }
}

void run_trace() {

    RTCDevice device = initialize_device();
    RTCScene scene = initialize_scene(device);

    cast_ray(scene, 0, 0, -1, 0, 0, 1);

    cast_ray(scene, 1, 1, 1, 0, 0, 1);

    rtcReleaseScene(scene);
    rtcReleaseDevice(device);
}

} // namespace embree_toy
