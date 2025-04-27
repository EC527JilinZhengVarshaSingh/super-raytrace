//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"
#include <fstream>
#include "camera_openmp.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <omp.h>
#include <chrono>


// world generation
int main(int argc, char* argv[]) {

// default values
int scene_id = 1;
std::string schedule_type = "static";

// get SCENE_ID from env if available
if (const char* env_scene = std::getenv("SCENE_ID")) {
    try {
        scene_id = std::stoi(env_scene);
    } catch (...) {
        std::cerr << "Invalid SCENE_ID env var; using default (1)\n";
    }
}

// override with CLI args if passed
if (argc > 1) {
    scene_id = std::stoi(argv[1]);
}
if (argc > 2) {
    schedule_type = argv[2];
}
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    std::clog << "Generating scene with ID: " << scene_id << "\n";
    switch (scene_id) {
        case 1: {
            for (int a = -11; a < 11; a++) {
                for (int b = -11; b < 11; b++) {
                    auto choose_mat = random_float();
                    point3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;

                        if (choose_mat < 0.8) {
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                        } else if (choose_mat < 0.95) {
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_float(0, 0.5);
                            sphere_material = make_shared<metal>(albedo, fuzz);
                        } else {
                            sphere_material = make_shared<dielectric>(1.5);
                        }
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    }
                }
            }
            // Shared spheres in all scenes
            auto material1 = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

            auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
            world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

            auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
            world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
            break;
        }
        case 2: {
            for (int a = 5; a < 11; a++) {
                for (int b = 5; b < 11; b++) {
                    auto choose_mat = random_float();
                    point3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;

                        if (choose_mat < 0.8) {
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                        } else if (choose_mat < 0.95) {
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_float(0, 0.5);
                            sphere_material = make_shared<metal>(albedo, fuzz);
                        } else {
                            sphere_material = make_shared<dielectric>(1.5);
                        }
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    }
                }
            }
            // Shared spheres in all scenes
            auto material1 = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

            auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
            world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

            auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
            world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
            break;
        }
        default: {
            for (int a = -11; a < 0; a++) {
                for (int b = -11; b < 0; b++) {
                    auto choose_mat = random_float();
                    point3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;

                        if (choose_mat < 0.8) {
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                        } else if (choose_mat < 0.95) {
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_float(0, 0.5);
                            sphere_material = make_shared<metal>(albedo, fuzz);
                        } else {
                            sphere_material = make_shared<dielectric>(1.5);
                        }
                        world.add(make_shared<sphere>(center, 0.2, sphere_material));
                    }
                }
            }

            // Shared spheres in all scenes
            auto material1 = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

            auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
            world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

            auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
            world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
            break;
        }
    }
    camera cam;
    /* different image_width sizes
    320
    640
    800
    1920
    3840*/
    int image_width = 340; //default
    if (const char* env_width = std::getenv("WIDTH")) {
        try {
            image_width = std::stoi(env_width);
        } catch (...) {
            std::cerr << "Invalid WIDTH env variable; using default (340)\n";
        }
    }
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = image_width;
    cam.samples_per_pixel = 10;
    cam.max_depth         = 20;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;
    
    std::clog << "Using " << omp_get_max_threads() << "OPENMP threads\n";
    // redirect clog to /dev/null to avoid console I/O time
    std::ofstream nullstream("/dev/null");
    std::streambuf* old_clog = std::clog.rdbuf(nullstream.rdbuf());
    // start the timer
    auto start = std::chrono::high_resolution_clock::now();
    cam.render(world, scene_id, schedule_type);
    // stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    // restore after timing
    std::clog.rdbuf(old_clog);
    std::clog << "Elapsed time: " << elapsed.count() << " seconds\n";
}
