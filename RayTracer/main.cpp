#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Source.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"

using namespace std;

struct RGBType {

	double r;
	double g;
	double b;

};

void savebmp(const char *filename, int w, int h, int dpi, RGBType *data) {

	FILE *f;
	int k = w * h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi * m;

	unsigned char bmpfileheader[14] = {
		'B', 'M', 
		0,0,0,0,
		0,0,0,0,
		54,0,0,0
	};

	unsigned char bmpinfoheader[40] = {
		40,0,0,0,
		0,0,0,0,
		0,0,0,0,
		1,0,24,0
	};

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize>>8);
	bmpfileheader[4] = (unsigned char)(filesize>>16);
	bmpfileheader[5] = (unsigned char)(filesize>>24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w>>8);
	bmpinfoheader[6] = (unsigned char)(w>>16);
	bmpinfoheader[7] = (unsigned char)(w>>24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++) {
		RGBType rgb = data[i];

		double red = (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue = (data[i].b) * 255;

		unsigned char color[3] = {(int)floor(blue), (int)floor(green), (int)floor(red)};

		fwrite(color, 1, 3, f);
	}

	fclose(f);

}

int findClosestObject(vector<double> objectIntersections) {
	int minValIndex;

	if (objectIntersections.size() == 0) {
		return -1;
	}

	else if (objectIntersections.size() == 1) {
		if (objectIntersections.at(0) > 0) {
			return 0;
		}
		else {
			return -1;
		}
	}

	else {
		double max = 0;
		for (int i = 0; i < objectIntersections.size(); i++) {
			if (max < objectIntersections.at(i)) {
				max = objectIntersections.at(i);
			}
		}

		if (max > 0) {
			for (int index = 0; index < objectIntersections.size(); index++) {
				if (objectIntersections.at(index) > 0 && objectIntersections.at(index) <= max) {
					max = objectIntersections.at(index);
					minValIndex = index;
				}
			}

			return minValIndex;
		}
		else {
			return -1;
		}
	}

}

Color getColorAt(Vect intersectionPos, Vect intersectingRayDir, vector<Object*> sceneObjects, int closestObjIndex, vector<Source*> lightSources, double accuracy, double ambientLight) {

	//Get the color and normal of the current fragment
	Color closestObjColor = sceneObjects.at(closestObjIndex)->getColor();
	Vect closestObjNormal = sceneObjects.at(closestObjIndex)->getNormalAt(intersectionPos);

	//tiled floor
	if (closestObjColor.getSpecial() == 2) {
		int square = (int)floor(intersectionPos.getX()) + (int)floor(intersectionPos.getZ());

		if ((square % 2) == 0) {
			closestObjColor.setRed(0);
			closestObjColor.setGreen(0);
			closestObjColor.setBlue(0);
		}
		else {
			closestObjColor.setRed(1);
			closestObjColor.setGreen(1);
			closestObjColor.setBlue(1);
		}
	}

	//Begin by accounting only for ambient light
	Color finalColor = closestObjColor.colorScalar(ambientLight);

	//REFLECTIONS
	//Special values over 0 and under 1 indicate reflectivity
	if (closestObjColor.getSpecial() > 0 && closestObjColor.getSpecial() <= 1) {
		//Calculate the ray being reflected off the current fragment
		double dot1 = closestObjNormal.dot(intersectingRayDir.negative());
		Vect scalar1 = closestObjNormal.multiply(dot1);
		Vect add1 = scalar1.add(intersectingRayDir);
		Vect scalar2 = add1.multiply(2);
		Vect add2 = intersectingRayDir.negative().add(scalar2);
		Vect reflectionDir = add2.normalize();

		Ray reflectionRay(intersectionPos, reflectionDir);

		//For every object in the scene, test whether it intersects with the new ray
		vector<double> reflectionIntersections;

		for (int reflectionIndex = 0; reflectionIndex < sceneObjects.size(); reflectionIndex++) {
			reflectionIntersections.push_back(sceneObjects.at(reflectionIndex)->findIntersection(reflectionRay));
		}

		//Find the closest of the intersected objects to the ray's origin (z-buffer)
		int indexOfClosestObjectWithReflection = findClosestObject(reflectionIntersections);

		//If there is a closest object, modify the color at the current fragment
		if (indexOfClosestObjectWithReflection != -1) {
			//Accuracy check
			if (reflectionIntersections.at(indexOfClosestObjectWithReflection) > accuracy) {
				//Find where the reflected ray intersects the object
				Vect reflectionIntersectionPos = intersectionPos.add(reflectionDir.multiply(reflectionIntersections.at(indexOfClosestObjectWithReflection)));
				reflectionIntersections.clear();

				//Calculate the color at the fragment where the reflected ray hits
				Color reflectionIntersectionColor = getColorAt(reflectionIntersectionPos, reflectionDir, sceneObjects, indexOfClosestObjectWithReflection, lightSources, accuracy, ambientLight);

				//Add this color
				finalColor = finalColor.colorAdd(reflectionIntersectionColor.colorScalar(closestObjColor.getSpecial()));
			}
		}
	}

	//SHADOWS
	for (int lightIndex = 0; lightIndex < lightSources.size(); lightIndex++) {
		Vect lightDir = lightSources.at(lightIndex)->getLightPos().add(intersectionPos.negative()).normalize();
		
		double cosAngle = closestObjNormal.dot(lightDir);

		if (cosAngle > 0) {
			bool shadowed = false;

			Vect distToLight = lightSources.at(lightIndex)->getLightPos().add(intersectionPos.negative()).normalize();
			double distToLightMag = distToLight.magnitude();

			Ray shadowRay(intersectionPos, lightSources.at(lightIndex)->getLightPos().add(intersectionPos.negative()).normalize());

			vector<double> secondaryIntersections;

			for (int objectIndex = 0; objectIndex < sceneObjects.size() && shadowed == false; objectIndex++) {
				secondaryIntersections.push_back(sceneObjects.at(objectIndex)->findIntersection(shadowRay));
			}

			for (int c = 0; c < secondaryIntersections.size(); c++) {
				if (secondaryIntersections.at(c) > accuracy) {
					if (secondaryIntersections.at(c) <= distToLightMag) {
						shadowed = true;
					}
				}
				break;
			}

			if (!shadowed) {
				finalColor = finalColor.colorAdd(closestObjColor.colorMultiply(lightSources.at(lightIndex)->getLightColor()).colorScalar(cosAngle));

				if (closestObjColor.getSpecial() > 0 && closestObjColor.getSpecial() <= 1) {
					double dot1 = closestObjNormal.dot(intersectingRayDir.negative());
					Vect scalar1 = closestObjNormal.multiply(dot1);
					Vect add1 = scalar1.add(intersectingRayDir);
					Vect scalar2 = add1.multiply(2);
					Vect add2 = intersectingRayDir.negative().add(scalar2);
					Vect reflectionDir = add2.normalize();

					double specular = reflectionDir.dot(lightDir);
					if (specular > 0) {
						specular = pow(specular, 10);
						finalColor = finalColor.colorAdd(lightSources.at(lightIndex)->getLightColor().colorScalar(specular*closestObjColor.getSpecial()));
					}
				}
			}
		}
	}

	return finalColor.clip();

}

int main(int argc, char *argv[])
{
	cout << "Beginning render..." << endl;

	clock_t t1, t2;
	t1 = clock();

	int dpi = 72;
	int width = 1280;
	int height = 720;
	int n = width * height;
	RGBType *pixels = new RGBType[n];

	const int aadepth = 16;
	double aathreshold = 0.1f;

	double aspectRatio = (double)width / (double)height;
	double ambientLight = 0.2f;
	double accuracy = 0.000001f;

	Vect O(0, 0, 0);
	Vect X(1, 0, 0);
	Vect Y(0, 1, 0);
	Vect Z(0, 0, 1);

	Vect newSpherePos(2, 0, 0);
	Vect camPos(3, 1.5, -4);

	Vect lookAt(0, 0, 0);
	Vect diff_btw(camPos.getX() - lookAt.getX(), camPos.getY() - lookAt.getY(), camPos.getZ() - lookAt.getZ());

	Vect camDir = diff_btw.negative().normalize();
	Vect camRight = Y.cross(camDir).normalize();
	Vect camUp = Y;
	Camera scene_cam(camPos, camDir, camRight, camUp);

	Color white_light(1.0, 1.0, 1.0, 0.0);
	Color prettyBlue(0.5, 0.75, 1.0, 0.3);
	Color gray(0.5, 0.5, 0.5, 0);
	Color black(0.0, 0.0, 0.0, 0.0);
	Color maroon(0.5, 0.25, 0.25, 0.2);
	Color checkerboard(0, 0, 0, 2);

	Vect lightPos(-7, 10, -10);
	Light sceneLight(lightPos, white_light);
	vector<Source*> lightSources;
	lightSources.push_back(dynamic_cast<Source*>(&sceneLight));


	//scene objects
	Sphere scene_sphere(O, 1, prettyBlue);
	Sphere scene_sphere2(newSpherePos, 0.5, maroon);
	Plane scene_plane(Y, -1, checkerboard);

	vector<Object*> sceneObjects;
	sceneObjects.push_back(dynamic_cast<Object*>(&scene_sphere));
	sceneObjects.push_back(dynamic_cast<Object*>(&scene_sphere2));
	sceneObjects.push_back(dynamic_cast<Object*>(&scene_plane));

	double xamnt, yamnt;
	double tempRed, tempGreen, tempBlue;

	int pixelIndex;
	int aa_index;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pixelIndex = y*width + x;


			//anti-aliasing
			//start with blank pixel
			double tempRed[aadepth*aadepth];
			double tempGreen[aadepth*aadepth];
			double tempBlue[aadepth*aadepth];

			for (int aax = 0; aax < aadepth; aax++) {
				for (int aay = 0; aay < aadepth; aay++) {

					aa_index = aay * aadepth + aax;

					srand(time(0));

					if (aadepth == 1) {
						//no anti-aliasing
						if (width > height) {
							xamnt = ((x + 0.5f) / width)*aspectRatio - (((width - height) / (double)height) / 2);
							yamnt = ((height - y) + 0.5f) / height;
						}
						else if (height > width) {
							xamnt = (x + 0.5f) / width;
							yamnt = (((height - y) + 0.5f) / height) / aspectRatio - (((height - width) / (double)width) / 2);
						}
						else {
							xamnt = (x + 0.5f) / width;
							yamnt = ((height - y) + 0.5f) / height;
						}
					}
					else {
						//anti-aliasing
						if (width > height) {
							xamnt = ((x + (double)aax/((double)aadepth - 1)) / width)*aspectRatio - (((width - height) / (double)height) / 2);
							yamnt = ((height - y) + (double)aax / ((double)aadepth - 1)) / height;
						}
						else if (height > width) {
							xamnt = (x + (double)aax / ((double)aadepth - 1)) / width;
							yamnt = (((height - y) + (double)aax / ((double)aadepth - 1)) / height) / aspectRatio - (((height - width) / (double)width) / 2);
						}
						else {
							xamnt = (x + (double)aax / ((double)aadepth - 1)) / width;
							yamnt = ((height - y) + (double)aax / ((double)aadepth - 1)) / height;
						}
					}

					//Send ray for the current pixel
					Vect camRayOrigin = scene_cam.getCameraPos();
					Vect camRayDir = camDir.add(camRight.multiply(xamnt - 0.5)).add(camUp.negative().multiply(yamnt - 0.5)).normalize();
					Ray camRay = Ray(camRayOrigin, camRayDir);

					vector<double> intersections;

					for (int index = 0; index < sceneObjects.size(); index++) {
						intersections.push_back(sceneObjects.at(index)->findIntersection(camRay));
					}

					int closestObjIndex = findClosestObject(intersections);

					if (closestObjIndex == -1) {
						tempRed[aa_index] = 0;
						tempGreen[aa_index] = 0;
						tempBlue[aa_index] = 0;
					}
					else {
						if (intersections.at(closestObjIndex) > accuracy) {

							Vect intersectionPos = camRayOrigin.add(camRayDir.multiply(intersections.at(closestObjIndex)));
							Vect intersectingRayDir = camRayDir;

							Color color = getColorAt(intersectionPos, intersectingRayDir, sceneObjects, closestObjIndex, lightSources, accuracy, ambientLight);

							tempRed[aa_index] = color.getRed();
							tempGreen[aa_index] = color.getGreen();
							tempBlue[aa_index] = color.getBlue();
						}
					}
				}
			}

			double totalRed = 0;
			double totalGreen = 0;
			double totalBlue = 0;

			for (int iRed = 0; iRed < aadepth * aadepth; iRed++) {
				totalRed += tempRed[iRed];
			}
			for (int iGreen = 0; iGreen < aadepth * aadepth; iGreen++) {
				totalGreen += tempGreen[iGreen];
			}
			for (int iBlue = 0; iBlue < aadepth * aadepth; iBlue++) {
				totalBlue += tempBlue[iBlue];
			}

			double avgRed = (double)(totalRed / (aadepth * aadepth));
			double avgGreen = (double)(totalGreen / (aadepth * aadepth));
			double avgBlue = (double)(totalBlue / (aadepth * aadepth));

			pixels[pixelIndex].r = avgRed;
			pixels[pixelIndex].g = avgGreen;
			pixels[pixelIndex].b = avgBlue;

		}
	}



	savebmp("../image.bmp", width, height, dpi, pixels);

	delete pixels, tempRed, tempGreen, tempBlue;

	t2 = clock();
	double diff = ((double)t2 - (double)t1)/1000;

	cout << "Render complete!" << endl;
	cout << diff << " seconds" << endl;
}