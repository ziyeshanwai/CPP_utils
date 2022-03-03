// ReadObj.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>  
#include <sstream>
#include <string>
#include <Vector>
#include <io.h>
#include <algorithm>

using namespace std;

struct vertice
{
	float x;
	float y;
	float z;
};

struct uv
{
	float u;
	float v;
};

void ReadObj(string path, std::vector<vertice> &OutVertices, std::vector<uv> &OutUvs, std::vector<vertice>& OutNormals, std::vector<int> &OutFace, std::vector<int>& Outgcounts)
{
	string s, str, s1, s2, s3, s4, s5, s6;
	ifstream inf;
	vertice v;
	vertice normal;
	uv u;
	inf.open(path);

	int vn = 0;
	int vnum = 0;
	int fnum = 0;
	if (inf.is_open())
	{
		while (getline(inf, s))
		{
			
			//std::cout << s << std::endl;
			if (s[0] == 'v')
			{

				if (s[1] == 't')
				{
					istringstream in(s);
					in >> s1 >> s2 >> s3;
					u.u = std::stof(s2);
					u.v = std::stof(s3);
					OutUvs.push_back(u);
				}
				else if (s[1] == 'n')
				{
					istringstream in(s);
					in >> s1 >> s2 >> s3 >> s4;
					normal.x = std::stof(s2);
					normal.y = std::stof(s3);
					normal.z = std::stof(s4);
					OutNormals.push_back(normal);
				}
				else
				{
					istringstream in(s);
					in >> s1 >> s2 >> s3 >> s4;
					v.x = std::stof(s2);
					v.y = std::stof(s3);
					v.z = std::stof(s4);
					OutVertices.push_back(v);
				}
				
			}

			int a = 0, b = 0, c = 0, d=0;
			if (s[0] == 'f')
			{
				istringstream in(s);
				in >> s1 >> s2 >> s3 >> s4 >> s5;
				for (int k = 0; s2[k] != '/'; k++)
				{
					a = a * 10 + (s2[k] - 48);
				}
				OutFace.push_back(a);
				for (int k = 0; s3[k] != '/'; k++)
				{
					b = b * 10 + (s3[k] - 48);
				}
				OutFace.push_back(b);
				for (int k = 0; s4[k] != '/'; k++)
				{
					c = c * 10 + (s4[k] - 48);
				}
				OutFace.push_back(c);
				if (!s5.empty())
				{
					for (int k = 0; s5[k] != '/'; k++)
					{
						d = d * 10 + (s5[k] - 48);
					}
					OutFace.push_back(d);
					Outgcounts.push_back(4);
				}
				else
				{
					Outgcounts.push_back(3);
				}
			
			}
			
		}

	}

	inf.close();

}


void getFiles(string path, std::vector<string>& files)
{
	//文件句柄
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}


int main(int argc, char** argv)
{
	string rootpath = "";
	string objname = "Object000.obj";
	string suffixStr = "obj";
	string path = rootpath + "\\" + objname;
	std::vector<vertice> Vertices;
	std::vector<vertice> Normals;
	std::vector<int> face;
	std::vector<string> filenames;
	std::vector<int> g_counts;
	std::vector<uv> Uvs;
	ReadObj(path, Vertices, Uvs, Normals, face, g_counts);
	getFiles(rootpath, filenames);
	for (auto name : filenames)
	{
		Vertices.clear();
		face.clear();
		Uvs.clear();
		g_counts.clear();
		Normals.clear();
		string filetype = name.substr(name.find_last_of(".") + 1);
		transform(filetype.begin(), filetype.end(), filetype.begin(), ::tolower);
		
		if (filetype == suffixStr )
		{
			
			ReadObj(name, Vertices, Uvs, Normals, face, g_counts);
		}
		printf("result\n");
		std::cout << "read name " << name << std::endl;
		std::cout << "verteice size " << Vertices.size() << std::endl;
		std::cout << "face count " << face.size() << std::endl;
		std::cout << "Normal count " << Normals.size() << std::endl;
		std::cout << "uv count " << Uvs.size() << std::endl;
		std::cout << "g_counts " << g_counts.size() << std::endl;
		
		
	}

	


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
