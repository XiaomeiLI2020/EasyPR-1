#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

void getFiles(string path, vector<string>& files)
{
    DIR *dp;
    string dir = path, filepath;
    struct dirent *dirp;
    struct stat filestat;
    dp = opendir( path.c_str() );
    while ((dirp=readdir(dp))) {
        filepath=dir+"/" +dirp->d_name;
        //if the file is directory , skip the file
        if (stat(filepath.c_str(),&filestat)) {
            continue;
        }
        if (S_ISDIR(filestat.st_mode)) {
            continue;
        }
        files.push_back(filepath);  
    }

}

//C++的spilt函数
void SplitString(const string& s, vector<string>& v, const string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while(std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2-pos1));
 
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
}


//! 通过文件夹名称获取文件名，不包括后缀
void getFileName(const string& filepath, string& name)
{
	vector<string> spilt_path;
	SplitString(filepath, spilt_path, "\\");

	int spiltsize = (int)spilt_path.size();
	string filename = "";
	if (spiltsize != 0)
	{
		filename = spilt_path[spiltsize-1];

		vector<string> spilt_name;
		SplitString(filename, spilt_name, ".");

		int name_size = (int)spilt_name.size();
		if (name_size != 0)
		{
			name = spilt_name[0];
		}
	}
}

