#pragma once
#ifdef MultiCamSFM_EXPORTS
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif // 
#include "mss_system.h"

extern "C"
{
	colmap::MultiCamSFM* mSys = NULL;
	EXPORT void InitMultiCamSFMSystem(const char* log_dir);
	EXPORT bool SetCameraCalibrationFile(const char* cam_file);
	EXPORT bool SetImageDirectory(const char* image_dir);
	EXPORT bool SetWorkSpaceDirectory(const char* work_space);
	EXPORT void SetSkipImageNum(const int skipNum);
	EXPORT void RunMultiCamSFM();
	EXPORT void GetMultiCamSFMVersion(char*& version);
}

