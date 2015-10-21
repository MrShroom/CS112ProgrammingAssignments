/**************************
a small program to genrate a sphere's polygons in a format I can use 
the base of this code was taken from http://www.andrewnoske.com/wiki/Generating_a_sphere_as_a_3D_mesh
Edits and improve ments made by Shaun Mcthomas

Notes: right now Noramals are same as vertices, need to  corrrect for postion and radius
****************************/


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>
#include <vector>

typedef struct{
	double x;
	double y;
	double z;
}  Point;

typedef struct{
	double x;
	double y;
}  TDPoint;

#define PI 3.14159265358979323846264338327950288419716939937510
int numVertices = 0;    // Tallies the number of vertex points added.
int nPoly = 0;			// Tallies the number of triangles added.
double sphereColor[4] = { 0.0, 0.0, 1.0, 0.3 };

//------------------------
//-- Prints a sphere as a "standard sphere" triangular mesh with the specified
//-- number of latitude (nLatitude) and longitude (nLongitude) lines and
//-- writes results to the specified output file (fout).

void printStandardSphere(Point pt, double radius, int nLatitude, int nLongitude, FILE *fout, FILE *fout2, FILE *fout3, FILE *fout4, FILE *fout5)
{
	int p, s, i, j;
	double x, y, z, out;
	int nPitch = nLongitude + 1;
	

	double pitchInc = ( PI / (double)nPitch);
	double rotInc = (2.0 * PI / (double)nLatitude);
	 

	//## PRINT VERTICES:
	std::vector<Point> myverts;
	std::vector<TDPoint> myUV;

	Point temp;
	TDPoint temTD;


	temp.x = pt.x;			// Top vertex.
	temp.y = pt.y + radius;
	temp.z = pt.z;
	myverts.push_back(temp);

	temTD.x = 0.5;			// Top vertex.
	temTD.y = 0.0;
	myUV.push_back(temTD);

	temp.x = pt.x;			// Bottom vertex.
	temp.y = pt.y - radius;
	temp.z = pt.z;
	myverts.push_back(temp);

	temTD.x = 0.5;			// Bottom vertex.
	temTD.y = 1.0;
	myUV.push_back(temTD);

	fprintf(fout, "v %g %g %g\n", pt.x, pt.y + radius, pt.z);    // Top vertex.
	fprintf(fout, "v %g %g %g\n", pt.x, pt.y - radius, pt.z);    // Bottom vertex.
	numVertices = numVertices + 2;
	

	int fVert = numVertices;    // Record the first vertex index for intermediate vertices.
	for (p = 1; p<nPitch; p++)     // Generate all "intermediate vertices":
	{
		out = radius * sin((double)p * pitchInc);
		if (out < 0) out = -out;    // abs() command won't work with all compilers
		y = radius * cos(p * pitchInc);
		printf("OUT = %g\n", out);    // bottom vertex
		printf("nPitch = %d\n", nPitch);    // bottom vertex
		for (s = 0; s<nLatitude; s++)
		{
			x = out * cos(s * rotInc);
			z = out * sin(s * rotInc);

			fprintf(fout, "v %g %g %g\n", x + pt.x, y + pt.y, z + pt.z);
			temp.x = x + pt.x;
			temp.y = y + pt.y;
			temp.z = z + pt.z;
			myverts.push_back(temp);

			temTD.x = double(s) / double(nLatitude);
			temTD.y = double(p) / double(nPitch);
			myUV.push_back(temTD);
		
			numVertices++;
		}
	}

	//## PRINT SQUARE FACES BETWEEN INTERMEDIATE POINTS:

	for (p = 1; p<nPitch - 1; p++) {
		for (s = 0; s<nLatitude; s++) {
			i = p*nLatitude + s;
			j = (s == nLatitude - 1) ? i - nLatitude : i;
			fprintf(fout, "f %d %d %d %d\n",
				(i + 1 - nLatitude) + fVert, (j + 2 - nLatitude) + fVert, (j + 2) + fVert, (i + 1) + fVert);

			fprintf(fout2, "\n%.15ff, %.15ff, %.15ff,\n",
				myverts[(i  - nLatitude) + fVert].x, myverts[(i  - nLatitude) + fVert].y, myverts[(i  - nLatitude) + fVert].z);
			fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
				myverts[(j + 1 - nLatitude) + fVert].x, myverts[(j + 1 - nLatitude) + fVert].y, myverts[(j + 1 - nLatitude) + fVert].z);
			fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
				myverts[(j + 1) + fVert].x, myverts[((j + 1) + fVert)].y, myverts[(j + 1) + fVert].z);

			fprintf(fout5, "\n%.15ff, %.15ff, %.15ff,\n",
				myverts[(i - nLatitude) + fVert].x, myverts[(i - nLatitude) + fVert].y, myverts[(i - nLatitude) + fVert].z);
			fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
				myverts[(j + 1 - nLatitude) + fVert].x, myverts[(j + 1 - nLatitude) + fVert].y, myverts[(j + 1 - nLatitude) + fVert].z);
			fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
				myverts[(j + 1) + fVert].x, myverts[((j + 1) + fVert)].y, myverts[(j + 1) + fVert].z);

			fprintf(fout3, "\n%.15ff, %.15ff,\n",
				myUV[(i - nLatitude) + fVert].x, myUV[(i - nLatitude) + fVert].y);
			fprintf(fout3, "%.15ff, %.15ff,\n",
				myUV[(j + 1 - nLatitude) + fVert].x, myUV[(j + 1 - nLatitude) + fVert].y);
			fprintf(fout3, "%.15ff, %.15ff,\n",
				myUV[(j + 1) + fVert].x, myUV[((j + 1) + fVert)].y);


			fprintf(fout2, "\n%.15ff, %.15ff, %.15ff,\n",
				myverts[(i - nLatitude) + fVert].x, myverts[(i - nLatitude) + fVert].y, myverts[(i - nLatitude) + fVert].z);
			fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
				myverts[(j + 1) + fVert].x, myverts[((j + 1) + fVert)].y, myverts[(j + 1) + fVert].z);			
			fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
				myverts[i + fVert].x, myverts[i + fVert].y, myverts[i + fVert].z);

			fprintf(fout5, "\n%.15ff, %.15ff, %.15ff,\n",
				myverts[(i - nLatitude) + fVert].x, myverts[(i - nLatitude) + fVert].y, myverts[(i - nLatitude) + fVert].z);
			fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
				myverts[(j + 1) + fVert].x, myverts[((j + 1) + fVert)].y, myverts[(j + 1) + fVert].z);
			fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
				myverts[i + fVert].x, myverts[i + fVert].y, myverts[i + fVert].z);


			fprintf(fout3, "\n%.15ff, %.15ff,\n",
				myUV[(i - nLatitude) + fVert].x, myUV[(i - nLatitude) + fVert].y);
			fprintf(fout3, "%.15ff, %.15ff,\n",
				myUV[(j + 1) + fVert].x, myUV[(j + 1) + fVert].y);
			fprintf(fout3, "%.15ff, %.15ff,\n",
				myUV[i + fVert].x, myUV[i + fVert].y);

			for (int i = 0; i < 6; i++)
				fprintf(fout4, "%.15ff, %.15ff, %.15ff, %.15ff,\n",
				sphereColor[0], sphereColor[1], sphereColor[2], sphereColor[3]);
			nPoly += 2;

		}
	}

	//## PRINT TRIANGLE FACES CONNECTING TO TOP AND BOTTOM VERTEX:

	int offLastVerts = fVert + (nLatitude * (nLongitude - 1));
	for (s = 0; s<nLatitude; s++)
	{
		j = (s == nLatitude - 1) ? -1 : s;
		fprintf(fout, "f %d %d %d\n", fVert - 1, (j + 2) + fVert, (s + 1) + fVert);

		//vertices
		fprintf(fout2, "\n%.15ff, %.15ff, %.15ff,\n",
			myverts[fVert - 2].x, myverts[fVert - 2].y, myverts[fVert - 2].z);
		fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(j + 1) + fVert].x, myverts[(j + 1) + fVert].y, myverts[(j + 1) + fVert].z);
		fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(s ) + fVert].x, myverts[((s ) + fVert)].y, myverts[(s  ) + fVert].z);
		
		//Normals
		fprintf(fout5, "\n%.15ff, %.15ff, %.15ff,\n",
			myverts[fVert - 2].x, myverts[fVert - 2].y, myverts[fVert - 2].z);
		fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(j + 1) + fVert].x, myverts[(j + 1) + fVert].y, myverts[(j + 1) + fVert].z);
		fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(s)+fVert].x, myverts[((s)+fVert)].y, myverts[(s)+fVert].z);
		//UV
		fprintf(fout3, "\n%.15ff, %.15ff,\n",
			(myUV[(j + 1) + fVert].x + myUV[(s)+fVert].x)/2.0, myUV[fVert - 2].y);
		fprintf(fout3, "%.15ff, %.15ff,\n",
			myUV[(j + 1) + fVert].x, myUV[(j + 1) + fVert].y);
		fprintf(fout3, "%.15ff, %.15ff,\n",
			myUV[(s)+fVert].x, myUV[(s)+fVert].y);

		fprintf(fout, "f %d %d %d\n", fVert, (s + 1) + offLastVerts, (j + 2) + offLastVerts);
		
		//vertices
		fprintf(fout2, "\n%.15ff, %.15ff, %.15ff,\n",
			myverts[fVert-1].x, myverts[fVert-1].y, myverts[fVert-1].z);
		fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(s ) + offLastVerts].x, myverts[(s ) + offLastVerts].y, myverts[(s ) + offLastVerts].z);
		fprintf(fout2, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(j + 1) + offLastVerts].x, myverts[(j + 1) + offLastVerts].y, myverts[(j + 1) + offLastVerts].z);
		
		//Normals
		fprintf(fout5, "\n%.15ff, %.15ff, %.15ff,\n",
			myverts[fVert - 1].x, myverts[fVert - 1].y, myverts[fVert - 1].z);
		fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(s)+offLastVerts].x, myverts[(s)+offLastVerts].y, myverts[(s)+offLastVerts].z);
		fprintf(fout5, "%.15ff, %.15ff, %.15ff,\n",
			myverts[(j + 1) + offLastVerts].x, myverts[(j + 1) + offLastVerts].y, myverts[(j + 1) + offLastVerts].z);
		
		//UV
		fprintf(fout3, "\n%.15ff, %.15ff,\n",
			(myUV[(s)+offLastVerts].x + myUV[(j + 1) + offLastVerts].x)/2.0 , myUV[fVert - 1].y);
		fprintf(fout3, "%.15ff, %.15ff,\n",
			myUV[(s)+offLastVerts].x, myUV[(s)+offLastVerts].y);
		fprintf(fout3, "%.15ff, %.15ff,\n",
			myUV[(j + 1) + offLastVerts].x, myUV[(j + 1) + offLastVerts].y);

		for (int i = 0; i < 6; i++)
			fprintf(fout4, "%.15ff, %.15ff, %.15ff, %.15ff,\n",
			sphereColor[0], sphereColor[1], sphereColor[2], sphereColor[3]);
		nPoly += 2;
	}
	
	
}




//------------------------
//-- Entry point. This main() function demonstrates how you can
//-- use "printStandardSphere()", but you probably won't
//-- want/need to copy it in your own code.

int main(int argc, char *argv[])
{
	int nLatitude = 256;                  // Number vertical lines.
	int nLongitude = nLatitude/ 2;      // Number horizontal lines.
	// NOTE: for a good sphere use ~half the number of longitude lines than latitude.
	double radius = 1.0;
	Point centerPt;            // Position the center of out sphere at (0,0,0).
	centerPt.x = 0;
	centerPt.y = 0;
	centerPt.z = 0;

	FILE *fout = fopen("Sphere.txt", "w");
	FILE *fout2 = fopen("GlobeVertices.h", "w");
	fprintf(fout2, "float vertices1[] = {\n");

	FILE *fout3 = fopen("GlobeTextureMap.h", "w");
	fprintf(fout3, "float texture1[] = {\n");

	FILE *fout4 = fopen("GlobeColors.h", "w");
	fprintf(fout4, "float colors1[] = {\n");

	FILE *fout5 = fopen("GlobeNormals.h", "w");
	fprintf(fout5, "float normals1[] = {\n");

	if (fout == NULL || fout2 == NULL || fout3 == NULL || fout4 == NULL) {
		printf("Couldn't open output file.\n");
		return (-1);
	}
	printStandardSphere(centerPt, radius, nLatitude, nLongitude, fout, fout2, fout3, fout4, fout5);      // Print sphere with radius 1.0 into file.
	fclose(fout);

	fprintf(fout2, "};\n");
	fclose(fout2);
	fprintf(fout3, "};\n");
	fclose(fout3);
	fprintf(fout4, "};\n");
	fclose(fout4);
	fprintf(fout5, "};\n");
	fclose(fout5);

	fprintf(stdout, "  # vertices:   %d\n", numVertices);
	fprintf(stdout, "  # triangles:   %d\n", nPoly);
	return (0);
}