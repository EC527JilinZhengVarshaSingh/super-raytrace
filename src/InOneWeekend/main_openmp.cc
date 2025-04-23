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

int get_env_int(const char* env_var, int default_value) {
    const char* env_value = std::getenv(env_var);
    if (env_value) {
        try {
            return std::stoi(env_value);
        } catch (...) {
            std::cerr << "Invalid " << env_var << " env var; using default (" << default_value << ")\n";
        }
    }
    return default_value;
}

// world generation
int main(int argc, char* argv[]) {

// create encapsulating timer for entire program
auto start_entire = std::chrono::high_resolution_clock::now();
// default values
int scene_id = get_env_int("SCENE_ID", 1);
std::string schedule_type = "static"; // default scheduling type

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
                    auto choose_mat = random_double();
                    point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;

                        if (choose_mat < 0.8) {
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                        } else if (choose_mat < 0.95) {
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
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
                    auto choose_mat = random_double();
                    point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;

                        if (choose_mat < 0.8) {
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                        } else if (choose_mat < 0.95) {
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
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
                    auto choose_mat = random_double();
                    point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;

                        if (choose_mat < 0.8) {
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                        } else if (choose_mat < 0.95) {
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
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

    int image_width = get_env_int("WIDTH", 320);
    int samples = get_env_int("SAMPLES", 10);    // samples per pixel (bounces)
    int max_depth = get_env_int("DEPTH", 25);    // ray bounce depth

    if (argc > 4) {
        try { samples = std::stoi(argv[4]); } catch (...) {
            std::cerr << "Invalid sample count in CLI; using default (" << samples << ")\n";
        }
    }
    if (argc > 5) {
        try { max_depth = std::stoi(argv[5]); } catch (...) {
            std::cerr << "Invalid depth in CLI; using default (" << max_depth << ")\n";
        }
    }

    camera cam;
    /* different image_width sizes
    320
    640
    800
    1920
    3840*/
    cam.aspect_ratio      = 5.0 / 3.0;
    cam.image_width       = image_width;
    cam.samples_per_pixel = samples;
    cam.max_depth         = max_depth;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    int num_threads = get_env_int("THREADS", omp_get_max_threads());
    if (argc > 3) {
        try {
            num_threads = std::stoi(argv[3]);
        } catch (...) {
            std::cerr << "Invalid thread count in CLI; using current value (" << num_threads << ")\n";
        }
    }
    
    omp_set_num_threads(num_threads);
    std::clog << "Using " << num_threads << "OPENMP threads\n";

    // redirect clog to /dev/null to avoid console I/O time
    std::ofstream nullstream("/dev/null");
    std::streambuf* old_clog = std::clog.rdbuf(nullstream.rdbuf());
    // start the timer
    auto start = std::chrono::high_resolution_clock::now();
    cam.render(world, scene_id, schedule_type);
    // stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    auto end_entire = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::chrono::duration<double> elapsed_entire = end_entire - start_entire;
    // restore after timing
    std::clog.rdbuf(old_clog);
    std::clog << "Render time: " << elapsed.count() << " seconds\n";
    std::clog << "Total time: " << elapsed_entire.count() << " seconds\n";

    return 0;
}
