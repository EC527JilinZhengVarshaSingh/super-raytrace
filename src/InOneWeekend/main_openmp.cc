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

/* making new scenes, generation for elements boundaries */
#define XLOWER_SCENE_1 -11
#define ZLOWER_SCENE_1 -11
#define XUPPER_SCENE_1 11
#define ZUPPER_SCENE_1 11

#define XLOWER_SCENE_2 0
#define ZLOWER_SCENE_2 0
#define XUPPER_SCENE_2 11
#define ZUPPER_SCENE_2 11

// world generation
int main() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    /* optimization: this is a small loop, but I wonder if loop unrolling would help. Don't really see a point of accumulators... */
    /* could build a local hittable_list per thread and merge at the end*/
    for (int a = XLOWER_SCENE_2; a < XUPPER_SCENE_2; a++) {
        for (int b = ZLOWER_SCENE_2; b < ZUPPER_SCENE_2; b++) {
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

    camera cam;
    /* different image_width sizes
    320
    640
    800
    1920
    3840*/
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 340;
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
    cam.render(world);
    // stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    // restore after timing
    std::clog.rdbuf(old_clog);
    std::clog << "Elapsed time: " << elapsed.count() << " seconds\n";
}
