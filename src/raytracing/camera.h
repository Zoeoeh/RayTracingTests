#pragma once

#include "ray.h"
#include "utils.h"


class camera {
public:
	camera() {};
	~camera() {};

	virtual ray get_ray(float s, float t) = 0;

	glm::vec3 origin;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;

	std::uniform_real_distribution<double> unif;

	glm::vec3 random_unit_disk()
	{
		glm::vec3 p;

		do {
			p = 2.0f * glm::vec3(unif(Utils::rng), unif(Utils::rng), 0) - glm::vec3(1, 1, 0);
		} while (dot(p, p) >= 1.0);

		return p;
	}
};

class static_cam : public camera
{
public:
	static_cam(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vofx, float aspect);

	ray get_ray(float s, float t);
};

class dof_cam : public camera
{
public:
	dof_cam(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vofx, float aspect, float aperture, float focus_dist);
	ray get_ray(float s, float t);

	float lens_radius;
	glm::vec3 u, v, w;
};