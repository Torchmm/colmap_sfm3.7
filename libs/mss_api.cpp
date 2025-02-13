#include "mss_api.h"

void InitMultiCamSFMSystem(const char* log_dir)
{
	mSys = new colmap::MultiCamSFM(log_dir);
}

bool SetCameraCalibrationFile(const char* cam_file)
{
	return mSys->SetCameraCalibrationFile(cam_file);
}

bool SetImageDirectory(const char* image_dir)
{
	return mSys->SetImageDir(image_dir);
}

void RunMultiCamSFM()
{
	mSys->Run();
}

void GetMultiCamSFMVersion(char*& version)
{
	std::string ver = mSys->GetMSSVersion();
	version = (char*)malloc(sizeof(ver));
	memcpy(version, ver.c_str(), sizeof(ver));
}

bool SetWorkSpaceDirectory(const char* work_space)
{
	return mSys->SetWorkSpaceDirectory(work_space);
}

void SetSkipImageNum(const int skipNum)
{

}