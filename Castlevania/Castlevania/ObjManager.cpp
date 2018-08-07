//#include "ObjManager.h"
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <list>
//
//using namespace std;
//
//
//
//ObjManager::ObjManager()
//{
//}
//
//bool IsNumber2(char c)
//{
//	if (c >= '0' && c <= '9')
//		return true;
//	return false;
//}
//
//void ObjManager::LoadFileInfo(char * fileGameObj)
//{
//	ifstream f;
//	f.open(fileGameObj, ios::in);
//	string line;
//	string strTemp = "";
//	int i = 0;
//	int lTemp[7];
//	while (!f.eof())
//	{
//		int i = 0;
//		strTemp = "";
//		getline(f, line);
//		if (line == "")
//			break;
//		for (int n = 0; n < line.length(); n++)
//		{
//			if (line[i] != '\t' && IsNumber2(line[i]))
//				strTemp += line[i];
//			else
//			{
//				if (IsNumber2(strTemp[0]))
//				{
//					lTemp[i] = atoi(strTemp.c_str());
//					strTemp = "";
//					i++;
//				}
//			}
//			if (i == line.length() - 1)
//				lTemp[i] = atoi(strTemp.c_str());
//		}
//		//add info object
//		InfoObj.push_back(lTemp);
//	}
//}
//
//void ObjManager::Init(char * fileGameObj, char * fileQuadTree)
//{
//	LoadFileInfo(fileGameObj);
//	quadTree->GetQuadTreeFromFile(fileQuadTree);
//}
//
//void ObjManager::GetListObjFromquadTree(RECT rectCamera)
//{
//
//}
//
////list<Object> ObjManager::GetListObj()
////{
////	//return list<Object>();
////}
//
//ObjManager::~ObjManager()
//{
//}
