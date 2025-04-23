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

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
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

int main(int argc, char* argv[]) {
    /* entire timer for program */
    auto start_entire = std::chrono::high_resolution_clock::now();
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    /* get scene ID from env variable */
    int scene_id = get_env_int("SCENE_ID", 1);

    /* switch statement for different world generations*/
    switch (scene_id) {
        case 1: {
            std::clog << "Using scene 1: standard random scene\n";
            for (int a = -11; a < 11; a++) {
                for (int b = -11; b < 11; b++) {
                    auto choose_mat = random_double();
                    point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
        
                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;
        
                        if (choose_mat < 0.8) {
                            // diffuse
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        } else if (choose_mat < 0.95) {
                            // metal
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
                            sphere_material = make_shared<metal>(albedo, fuzz);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        } else {
                            // glass
                            sphere_material = make_shared<dielectric>(1.5);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        }
                    }
                }
            }
        
            auto material1 = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
        
            auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
            world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));
        
            auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
            world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
            break;
        }
        case 2: {
            std::clog << "Using scene 2\n";
            for (int a = 5; a < 11; a++) {
                for (int b = 5; b < 11; b++) {
                    auto choose_mat = random_double();
                    point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
        
                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;
        
                        if (choose_mat < 0.8) {
                            // diffuse
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        } else if (choose_mat < 0.95) {
                            // metal
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
                            sphere_material = make_shared<metal>(albedo, fuzz);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        } else {
                            // glass
                            sphere_material = make_shared<dielectric>(1.5);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        }
                    }
                }
            }
        
            auto material1 = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
        
            auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
            world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));
        
            auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
            world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
            break;
        }
        default: {
            std::cerr << "Using scene 3\n";
            for (int a = -11; a < 0; a++) {
                for (int b = -11; b < 0; b++) {
                    auto choose_mat = random_double();
                    point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
        
                    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                        shared_ptr<material> sphere_material;
        
                        if (choose_mat < 0.8) {
                            // diffuse
                            auto albedo = color::random() * color::random();
                            sphere_material = make_shared<lambertian>(albedo);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        } else if (choose_mat < 0.95) {
                            // metal
                            auto albedo = color::random(0.5, 1);
                            auto fuzz = random_double(0, 0.5);
                            sphere_material = make_shared<metal>(albedo, fuzz);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        } else {
                            // glass
                            sphere_material = make_shared<dielectric>(1.5);
                            world.add(make_shared<sphere>(center, 0.2, sphere_material));
                        }
                    }
                }
            }
        
            auto material1 = make_shared<dielectric>(1.5);
            world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
        
            auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
            world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));
        
            auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
            world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
            break;
        }
    }

    // Read image configuration from environment
    int image_width       = get_env_int("WIDTH", 320);
    int samples_per_pixel = get_env_int("SAMPLES", 10);
    int max_depth         = get_env_int("BOUNCES", 20);
    
    std::clog << "Image width: " << image_width << "\n";
    std::clog << "Samples per pixel: " << samples_per_pixel << "\n";
    std::clog << "Max depth (bounces): " << max_depth << "\n";

    camera cam;
    
    /* aspect ratio for warps */
    cam.aspect_ratio      = 5.0 / 3.0;
    cam.image_width       = image_width;
    cam.samples_per_pixel = samples_per_pixel;
    cam.max_depth         = max_depth;
    

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;
    
   
    // start the timer
    auto start = std::chrono::high_resolution_clock::now();
    cam.render(world, scene_id);
    // stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    auto end_entire = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::chrono::duration<double> elapsed_entire = end_entire - start_entire;
    std::clog<< "Render time: " << elapsed.count() << " seconds\n";
    std::clog<< "Total elapsed time: " << elapsed_entire.count() << " seconds\n";

    std::clog << "Done.                 \n";
    return 0;
}
