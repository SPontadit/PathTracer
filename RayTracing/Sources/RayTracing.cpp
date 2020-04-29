// RayTracing.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"
#include "MovingSphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "MathUtility.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "BVHNode.h"
#include "ConstantTexture.h"
#include "CheckerTexture.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "XYZRectangle.h"
#include "DiffuseLight.h"
#include "FlipNormals.h"
#include "Box.h"
#include "Translate.h"
#include "Rotation.h"
#include "ConstantMedium.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include <limits>


#define WIDTH  600
#define HEIGHT 400
#define SAMPLE 10
#define BOUNCE 4

Vector3 DeNaN(Vector3 const& color)
{
	Vector3 temp = color;

	if (!(temp[0] == temp[0]))
		temp[0] = 0.f;

	if (!(temp[1] == temp[1]))
		temp[1] = 0.f;

	if (!(temp[2] == temp[2]))
		temp[2] = 0.f;

	return temp;
}

Vector3 Color(Ray const& ray, Hitable* world, int depth)
{
	HitRecord hitRecord;

	if (world->Hit(ray, 0.001f, std::numeric_limits<float>::max(), hitRecord))
	{
		Ray rayScattered;
		Vector3 attenuation;
		Vector3 emitted = hitRecord.material->Emitted(hitRecord.u, hitRecord.v, hitRecord.point);

		if (depth < BOUNCE && hitRecord.material->Scatter(ray, hitRecord, attenuation, rayScattered))
		{
			return emitted + attenuation * Color(rayScattered, world, depth + 1);
		}
		else
		{
			return emitted;
		}
	}

	//return Vector3(0.f, 0.f, 0.f);

	Vector3 direction = GetUnit(ray.direction);
	float time = 0.5f *(direction.y() + 1.0f);
	return (1.0f - time) * Vector3(1.0f, 1.0f, 1.0f) + time * Vector3(0.5f, 0.7f, 1.0f);
}

Hitable* RandomScene()
{
	int count = 500;

	Hitable** list = new Hitable*[count + 1];

	Texture* checker = new CheckerTexture(new ConstantTexture(Vector3(0.f, 0.f, 0.f)), new ConstantTexture(Vector3(1.f, 1.f, 1.f)));

	list[0] = new Sphere(Vector3(0.f, -1000.f, 0.f), 1000.f, new Lambertian(new ConstantTexture(Vector3(0.5f, 0.5f, 0.5f))));

	int i = 1;

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float randomMaterial = drand48();
			Vector3 center(a + 0.9f + drand48(), 0.2f, b + 0.9f + drand48());
			
			if ((center - Vector3(4.f, 0.2f, 0.f)).Length() > 0.9f)
			{
				if (randomMaterial < 0.8f)
				{
					list[i++] = new Sphere(center, 0.2f,
						new Lambertian(new ConstantTexture(Vector3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48()))));
				}
				else if (randomMaterial < 0.95f)
				{
					list[i++] = new Sphere(center, 0.2f,
						new Metal(Vector3(0.5f * (1.f + drand48()), 0.5f * (1.f - drand48()), 0.5f * (1.f - drand48())), 0.5f * drand48()));
				}
				else
				{
					list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
				}
			}
		}
	}

	list[i++] = new Sphere(Vector3(0.f, 1.f, 0.f), 1.0f, new Dielectric(1.5f));
	list[i++] = new Sphere(Vector3(-4.f, 1.f, 0.f), 1.0f, new Lambertian(new ConstantTexture(Vector3(0.4f, 0.2f, 0.1f))));
	list[i++] = new Sphere(Vector3(4.f, 1.f, 0.f), 1.0f, new Metal(Vector3(0.7f, 0.6f, 0.5f), 0.0f));

	//return new HitableList(list, i);
	return new BVHNode(list, i, 0.f, 1.f);
}

Hitable* TwoSphere()
{
	Texture* checker = new CheckerTexture(new ConstantTexture(Vector3(0.f, 0.f, 0.f)), new ConstantTexture(Vector3(1.f, 1.f, 1.f)));

	int count = 50;

	Hitable** list = new Hitable*[count + 1];

	list[0] = new Sphere(Vector3(0.f, -10.f, 0.f), 10.f, new Lambertian(checker));
	list[1] = new Sphere(Vector3(0.f, 10.f, 0.f), 10.f, new Lambertian(checker));

	return new HitableList(list, 2);
}

Hitable* TwoPerlinSphere()
{
	Texture* perlinTexture = new NoiseTexture(4.f);
	
	Hitable** list = new Hitable*[2];

	list[0] = new Sphere(Vector3(0.f, -1000.f, 0.f), 1000.f, new Lambertian(perlinTexture));
	list[1] = new Sphere(Vector3(0.f, 2.f, 0.f), 2.f, new Lambertian(perlinTexture));

	return new HitableList(list, 2);
}

Hitable* SimpleLight()
{
	Texture* perlinTexture = new NoiseTexture(4.f);

	Hitable** list = new Hitable*[4];

	list[0] = new Sphere(Vector3(0.f, -1000.f, 0.f), 1000.f, new Lambertian(perlinTexture));
	list[1] = new Sphere(Vector3(0.f, 2.f, 0.f), 2.f, new Lambertian(perlinTexture));
	list[2] = new Sphere(Vector3(0.f, 7.f, 0.f), 2.f, new DiffuseLight(new ConstantTexture(Vector3(4.f, 4.f, 4.f))));
	list[3] = new XYRectangle(3.f, 5.f, 1.f, 3.f, -2.f, new DiffuseLight(new ConstantTexture(Vector3(4.f, 4.f, 4.f))));

	return new HitableList(list, 4);
}

Hitable* CornellBox()
{
	Hitable** list = new Hitable*[8];
	int i = 0;

	Material* red = new Lambertian(new ConstantTexture(Vector3(0.65f, 0.05f, 0.05f)));
	Material* white = new Lambertian(new ConstantTexture({ 0.73f, 0.73f, 0.73f }));
	Material* green = new Lambertian(new ConstantTexture({ 0.12f, 0.45f, 0.15f }));
	Material* light = new DiffuseLight(new ConstantTexture({ 15.f, 15.f, 15.f }));

	list[i++] = new FlipNormals(new YZRectangle(0.f, 555.f, 0.f, 555.f, 555.f, green));
	list[i++] = new YZRectangle(0.f, 555.f, 0.f, 555.f, 0.f, red);
	list[i++] = new XZRectangle(213.f, 343.f, 227.f, 332.f, 554.f, light);
	list[i++] = new FlipNormals(new XZRectangle(0.f, 555.f, 0.f, 555.f, 555.f, white));
	list[i++] = new XZRectangle(0.f, 555.f, 0.f, 555.f, 0.f, white);
	list[i++] = new FlipNormals(new XYRectangle(0.f, 555.f, 0.f, 555.f, 555.f, white));
	list[i++] = new Translate(new RotationY(new Box(Vector3(0.f, 0.f, 0.f), Vector3(165.f, 165.f, 165.f), white), -18.f), Vector3(130.f, 0.f, 65.f));
	list[i++] = new Translate(new RotationY(new Box(Vector3(0.f, 0.f, 0.f), Vector3(165.f, 330.f, 165.f), white), 15.f), Vector3(265.f, 0.f, 295.f));

	return new HitableList(list, i);
}

Hitable* CornellSmock()
{
	Hitable** list = new Hitable*[8];
	int i = 0;

	Material* red = new Lambertian(new ConstantTexture(Vector3(0.65f, 0.05f, 0.05f)));
	Material* white = new Lambertian(new ConstantTexture({ 0.73f, 0.73f, 0.73f }));
	Material* green = new Lambertian(new ConstantTexture({ 0.12f, 0.45f, 0.15f }));
	Material* light = new DiffuseLight(new ConstantTexture({ 15.f, 15.f, 15.f }));

	list[i++] = new FlipNormals(new YZRectangle(0.f, 555.f, 0.f, 555.f, 555.f, green));
	list[i++] = new YZRectangle(0.f, 555.f, 0.f, 555.f, 0.f, red);
	list[i++] = new XZRectangle(213.f, 343.f, 227.f, 332.f, 554.f, light);
	list[i++] = new FlipNormals(new XZRectangle(0.f, 555.f, 0.f, 555.f, 555.f, white));
	list[i++] = new XZRectangle(0.f, 555.f, 0.f, 555.f, 0.f, white);
	list[i++] = new FlipNormals(new XYRectangle(0.f, 555.f, 0.f, 555.f, 555.f, white));
	
	Hitable* box1 = new Translate(new RotationY(new Box(Vector3(0.f, 0.f, 0.f), Vector3(165.f, 165.f, 165.f), white), -18.f), Vector3(130.f, 0.f, 65.f));
	Hitable* box2 = new Translate(new RotationY(new Box(Vector3(0.f, 0.f, 0.f), Vector3(165.f, 330.f, 165.f), white), 15.f), Vector3(265.f, 0.f, 295.f));

	list[i++] = new ConstantMedium(box1, 0.01f, new ConstantTexture(Vector3(1.f, 1.f, 1.f)));
	list[i++] = new ConstantMedium(box2, 0.15f, new ConstantTexture(Vector3(0.f, 0.f, 0.f)));

	return new HitableList(list, i);
}

Hitable* Earth()
{
	int nx, ny, nn;

	unsigned char* textureData = stbi_load("earth.jpg", &nx, &ny, &nn, 0);

	Material* material = new Lambertian(new ImageTexture(textureData, nx, ny));

	return new Sphere(Vector3(0.f, 0.f, 0.f), 2.f, material);
}

Hitable* Final()
{
	int nb = 20;
	Hitable** list = new Hitable*[30];
	Hitable** boxList1 = new Hitable*[10000];
	Hitable** boxList2 = new Hitable*[10000];

	Material* white = new Lambertian(new ConstantTexture({ 0.73f, 0.73f, 0.73f }));
	Material* ground = new Lambertian(new ConstantTexture({ 0.48f, 0.83f, 0.53f }));

	int b = 0;

	for (int i = 0; i < nb; i++)
	{
		for (int j = 0; j < nb; j++)
		{
			float w = 100.f;
			float x0 = -1000.f + i * w;
			float y0 = 0.f;
			float z0 = -1000.f + j * w;
			float x1 = x0 + w;
			float y1 = 100.f * (drand48() + 0.01f);
			float z1 = z0 + w;

			boxList1[b++] = new Box({ x0, y0, z0 }, { x1, y1, z1 }, ground);
		}
	}

	int l = 0;

	list[l++] = new BVHNode(boxList1, b, 0.f, 1.f);

	Material* light = new DiffuseLight(new ConstantTexture({ 7.f, 7.f, 7.f }));

	list[l++] = new XZRectangle(123.f, 423.f, 147.f, 412.f, 554.f, light);

	Vector3 center(400.f, 400.f, 200.f);

	list[l++] = new MovingSphere(center, center + Vector3(30.f, 0.f, 0.f), 0.f, 1.f, 50.f, new Lambertian(new ConstantTexture({ 0.7f, 0.3f, 0.1f })));

	list[l++] = new Sphere({ 260.f, 150.f, 45.f }, 50.f, new Dielectric(1.5f));
	list[l++] = new Sphere({ 0.f, 150.f, 145.f }, 50.f, new Metal({ 0.8f, 0.8f, 0.9f }, 10.f));

	Hitable* boundary = new Sphere({ 360.f, 150.f, 145.f }, 70.f, new Dielectric(1.5f));
	list[l++] = boundary;
	list[l++] = new ConstantMedium(boundary, 0.2f, new ConstantTexture({ 0.2f, 0.4f, 0.9f }));

	boundary = new Sphere({ 0.f, 0.f, 0.f }, 5000.f, new Dielectric(1.5f));
	list[l++] = new ConstantMedium(boundary, 0.0001f, new ConstantTexture({ 1.f, 1.f, 1.f }));

	int nx, ny, nn;
	unsigned char* textureData = stbi_load("earth.jpg", &nx, &ny, &nn, 0);

	Material* earthMaterial = new Lambertian(new ImageTexture(textureData, nx, ny));
	list[l++] = new Sphere({ 400.f, 200.f, 400.f }, 100.f, earthMaterial);

	Texture* perlinTexture = new NoiseTexture(0.1f);
	list[l++] = new Sphere({ 220.f, 280.f, 300.f }, 80.f, new Lambertian(perlinTexture));

	int ns = 1000;

	for (int j = 0; j < ns; j++)
	{
		boxList2[j] = new Sphere(Vector3(165.f * drand48(), 165.f * drand48(), 165.f * drand48()), 10.f, white);
	}

	list[l++] = new Translate(new RotationY(new BVHNode(boxList2, ns, 0.f, 1.f), 15.f), { -100.f, 270.f, 395.f });

	return new HitableList(list, l);
}

int main()
{
	std::ofstream file;

	file.open("RayTrace.ppm");

	file << "P3\n" << WIDTH << " " << HEIGHT<< "\n255\n";

	Hitable* world = RandomScene();

	//Vector3 lookFrom(478.f, 278.f, -600.f);
	//Vector3 lookAt(278.f, 278.f, 0.f);
	//float FOV = 40.f;

	Vector3 lookFrom(13.f, 2.f, 3.f);
	Vector3 lookAt(0.f, 0.f, 0.f);

	//int texture[WIDTH][HEIGHT][3];
	unsigned char* data;
	data = (unsigned char*)malloc(WIDTH * HEIGHT * 3);

	float distanceToFocus = 10.f;
	float aperture = 0.f;
	float FOV = 20.f;

	Camera camera(lookFrom, lookAt, Vector3(0.f, 1.f, 0.f), FOV, float(WIDTH) / float(HEIGHT), aperture, distanceToFocus, 0.f, 1.f);

	for (int j = HEIGHT - 1; j >= 0; j--)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			Vector3 color(0.f, 0.f, 0.f);

			for (int s = 0; s < SAMPLE; s++)
			{
				float u = float(i + drand48()) / float(WIDTH);
				float v = float(j + drand48()) / float(HEIGHT);

				Ray ray = camera.GetRay(u, v);
				color += DeNaN(Color(ray, world, 0));
			}


			color /= float(SAMPLE);

			color = Vector3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2])); // Gamma correction

			if (color[0] > 1.f)
				color[0] = 1.f;

			if (color[1] > 1.f)
				color[1] = 1.f;

			if (color[2] > 1.f)
				color[2] = 1.f;


			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);

			//texture[HEIGHT][WIDTH][0] = ir;
			//texture[HEIGHT][WIDTH][1] = ig;
			//texture[HEIGHT][WIDTH][2] = ib;

			data[HEIGHT * j + WIDTH * i + 0] = (unsigned char)ir;
			data[HEIGHT * j + WIDTH * i + 1] = (unsigned char)ig;
			data[HEIGHT * j + WIDTH * i + 2] = (unsigned char)ib;

			file << ir << " " << ig << " " << ib << "\n";
		}
	}

	file.close();

	//stbi_write_tga("Ray.tga", WIDTH, HEIGHT, 4, data);

	delete world;

    return 0;
}