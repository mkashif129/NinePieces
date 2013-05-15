/*
Name: Muhammad Kashif
Date: 16 January, 2013
File: mkObj.h (side class)
Desc: Fast obj loader

Status:  80% completed  (bug with higher polygons)
Reviewd: 19 Jan, 2013
	   : 09 Apr, 2013

Pointer Error Removed


Version: 0.1
*/

#ifndef MK_OBJ_H
#define MK_OBJ_H
#pragma once

#include "mk.h"



struct mkFace3
{
	vec3 vert[4];

	mkFace3()  
	{
		vert[0] = vec3(0);
		vert[1] = vec3(0);
		vert[2] = vec3(0);
		vert[3] = vec3(0);
	}

	mkFace3(vec3 v1,vec3 v2,vec3 v3, vec3 norm)  
	{
		vert[0] = v1;
		vert[1] = v2;
		vert[2] = v3;
		vert[3] = norm;
	}

	mkFace3(vec3 v[3], vec3 norm)  
	{
		vert[0] = v[0];
		vert[1] = v[1];
		vert[2] = v[2];
		vert[3] = norm;
	}

};


class mkObjLoader
{
private:
	mkArray <vec3>  *vertices;
	mkArray <ivec3>  *facesIndices;
	mkArray <vec3>  *normals;

	mkArray <mkFace3> *faces;

public:
	mkObjLoader()
	{
		vertices = new mkArray<vec3>();
		facesIndices = new mkArray<ivec3>();
		normals = new mkArray<vec3>();
		faces = new mkArray<mkFace3>();

	}

	mkObjLoader(string filename)
	{

		vertices = new mkArray<vec3>();
		facesIndices = new mkArray<ivec3>();
		normals = new mkArray<vec3>();
		faces = new mkArray<mkFace3>();


		Load(filename);
	}

	void Load(string filename)
	{
		vector<vec3> vert;
		vector<ivec3> face;
		vector<vec3> norm;

		ifstream fs(filename);
		long int size = 0;
		mk::CheckTime.Start(); // checking time

		if(fs.is_open())
		{ 
			fs.seekg(0,ios::end);
			size = fs.tellg();
			fs.seekg(0,ios::beg);


			while(!fs.eof())
			{
				string str;
				getline(fs,str);


				if(str[0] == '#' || str[0] == 'o' || str[0] == 's') // skip comments and others
				{
				}
				else if(str[0] == 'v')
				{
					if(str[1] == ' ')
					{
						vec3 v;
						sscanf(str.c_str(),"v %f %f %f",&v.x,&v.y,&v.z);
						vert.push_back(v);
					}
					else if(str[1] == 'n')
					{
						vec3 v;
						sscanf(str.c_str(),"vn %f %f %f",&v.x,&v.y,&v.z);
						norm.push_back(v);
					}
				}
				else if(str[0] == 'f')
				{
					ivec3 v;
					int i;
					sscanf(str.c_str(),"f %d//%d %d//%d %d//%d",&v.x,&i,&v.y,&i,&v.z,&i);
					v -= 1;

					face.push_back(v);
				}
				else
				{
					// else skip every thing
				}

			}

			cout <<"File: ("<<filename<<") loaded Succesfully..!!\nTime Taken : "<<mk::CheckTime.getSeconds()<<" seconds\n";
			cout <<"File size: "<<(float)size/1024 <<" KB";



			vertices->PushData(&vert[0],vert.size());
			normals->PushData(&norm[0],norm.size());
			facesIndices->PushData(&face[0],face.size());


			cout <<"\n\nVERTICES: "<<vertices->getCount()<<"\n";
			cout <<"NORMALS: "<<normals->getCount()<<"\n";
			cout <<"facesIndices: "<<facesIndices->getCount()<<"\n";

		}
		else
		{
			cout <<"ERROR: ("<<filename<<") cannot be loaded..!!\n";
		}


		fs.close();
	}

	void GenerateFaces()
	{
		vector <mkFace3> tempFace;
		for(int i=0; i<facesIndices->getCount(); i++)
		{
			int ind1 = facesIndices->get()[i].x;
			int ind2 = facesIndices->get()[i].y;
			int ind3 = facesIndices->get()[i].z;



			// creating face
			mkFace3 f = mkFace3();   
			f.vert[0] = vertices->get()[ind1]; // v1
			f.vert[1] = vertices->get()[ind2]; // v2
			f.vert[2] = vertices->get()[ind3]; // v3
			f.vert[3] = normals->get()[i/2]; // and normal
			tempFace.push_back(f);
		}

		// push whole data  to face mkArray
		faces->PushData(&tempFace[0],tempFace.size());

	}

	mkArray <mkFace3>* getFaces()
	{
		return faces;
	}
	mkArray <vec3>* getVertices()
	{
		return vertices;
	}
	mkArray <vec3>* getNormals()
	{
		return normals;
	}
	mkArray <ivec3>* getFacesIndices()
	{
		return facesIndices;
	}



	void DisplayData()
	{
		cout <<"Vertices: "<<vertices->getCount()<<"\n";
		for(int i=0; i<vertices->getCount(); i++)
		{
			cout <<vertices->get()[i].x <<" ";
			cout <<vertices->get()[i].y <<" ";
			cout <<vertices->get()[i].z <<"\n";

		}
		cout <<"Normals: "<<normals->getCount()<<"\n";
		for(int i=0; i<normals->getCount(); i++)
		{
			cout <<normals->get()[i].x <<" ";
			cout <<normals->get()[i].y <<" ";
			cout <<normals->get()[i].z <<"\n";

		}
		cout <<"facesIndices: "<<facesIndices->getCount()<<"\n";
		for(int i=0; i<facesIndices->getCount(); i++)
		{
			cout <<facesIndices->get()[i].x <<" ";
			cout <<facesIndices->get()[i].y <<" ";
			cout <<facesIndices->get()[i].z <<"\n";
		}

		cout <<"Faces: "<<faces->getCount()<<"\n";
		for(int i=0; i<faces->getCount(); i++)
		{
			cout <<"Face "<<i<<": ";
			for(int j=0; j<4; j++)
			{
				cout <<"v "<<j<<": ("<< faces->get()[i].vert[j].x;
				cout <<","<< faces->get()[i].vert[j].y;
				cout <<","<< faces->get()[i].vert[j].z<<")    ";
			}
			cout <<"\n";
		}

	}
	void Clean()
	{
		delete []vertices;
		delete []normals;
		delete []facesIndices;
		delete []faces;
	}
};


#endif