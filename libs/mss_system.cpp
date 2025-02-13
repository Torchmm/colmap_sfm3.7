#include "mss_system.h"
#include <glog/logging.h>
#include <io.h>
#include <opencv2/opencv.hpp>
#include "colmap/util/colmap_version.h"
namespace colmap
{
	MultiCamSFM::MultiCamSFM(const std::string log_dir)
	{
		google::InitGoogleLogging("Muti_Source_Scanner");
		std::string base_name = log_dir + "/MSS-log-";
		google::SetLogDestination(google::GLOG_INFO, base_name.c_str());

		//FLAGS_logtostderr = false; // 将日志输出到标准输出
		FLAGS_alsologtostderr = true;
	}

	void MultiCamSFM::SetSkipNum(const int skipNum)
	{

	}

	bool MultiCamSFM::SetWorkSpaceDirectory(const std::string work_space)
	{
		if (_access(work_space.c_str(), 0) >= 0)
		{
			LOG(INFO) << "SET WORK SPACE #" << work_space;
			options_.workspace_path = work_space;
			return true;
		}
		else
		{
			LOG(ERROR) << "work_space directory do not exsit! ";
			return false;
		}
	}

	bool MultiCamSFM::SetCameraCalibrationFile(const std::string& cam_file)
	{
		LOG(INFO) << "SET CAMERA CALIBRATION FILE #" << cam_file;
		if (_access(cam_file.c_str(), 0) >= 0)
		{
			cv::FileStorage file(cam_file, cv::FileStorage::READ);
			cv::FileNode node;

			
			int camera_numbers = -1;
			file["camera_num"] >> camera_numbers;
			options_.camera_params.resize(camera_numbers);
			options_.extrinsics.resize(camera_numbers);
			int fisheye = -1;
			file["fisheye"] >> fisheye;
			if (fisheye == 1)
			{
				options_.camera_model = "OPENCV_FISHEYE";
				for (int i = 0; i < camera_numbers; i++)
				{
					std::string nodename = "cam" + std::to_string(i);
					std::string param = "";
					double value;
					file[nodename]["fx"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["fy"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["cx"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["cy"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["k2"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["k3"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["k4"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["k5"] >> value;
					param += std::to_string(value);

					cv::Mat extrinsics;
					std::string exnodename = "extrinsics" + std::to_string(i);
					file[exnodename] >> extrinsics;

					options_.camera_params[i] = param;
					options_.extrinsics[i] = extrinsics;

					LOG(INFO) << "camera " << i << " model: " << options_.camera_model;
					LOG(INFO) << "camera" << i << " param: " << param;
				}
			}
			else
			{
				options_.camera_model = "OPENCV";
				for (int i = 0; i < camera_numbers; i++)
				{
					std::string nodename = "cam" + std::to_string(i);
					std::string param = "";
					double value;
					file[nodename]["fx"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["fy"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["cx"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["cy"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["k1"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["k2"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["p1"] >> value;
					param += std::to_string(value);
					param += ",";
					file[nodename]["p2"] >> value;
					param += std::to_string(value);

					cv::Mat extrinsics;
					std::string exnodename = "extrinsics" + std::to_string(i);
					file[exnodename] >> extrinsics;
					
					options_.camera_params[i] = param;
					options_.extrinsics[i] = extrinsics;

					LOG(INFO) << "camera " << i << " model: " << options_.camera_model;
					LOG(INFO) << "camera" << i << " param: " << param;
				}
			}
			return true;

			
		}
		else
		{
			LOG(ERROR) << "camera calibration file do not exsit! ";
			return false;
		}
	}


	bool MultiCamSFM::SetImageDir(const std::string& dir1)
	{
		std::string directory1 = dir1;

		if (_access(directory1.c_str(), 0) >= 0)
		{
			LOG(INFO) << "SET IMAGE DIRECTORY #" << directory1;
			options_.image_path = directory1;
			return true;
		}
		else
		{
			LOG(ERROR) << "image directory do not exsit! ";
			return false;
		}

		return true;
	}

	std::string MultiCamSFM::GetMSSVersion()
	{
		return GetBuildInfo();
	}

	void MultiCamSFM::Run()
	{
		std::shared_ptr<ReconstructionManager> reconstruction_manager_ = std::shared_ptr<ReconstructionManager>(new ReconstructionManager);
		auto_recon_controller_ = std::shared_ptr<AutomaticReconstructionController>(new AutomaticReconstructionController(options_, reconstruction_manager_));
		auto_recon_controller_->Start();
		auto_recon_controller_->Wait();
	}

	MultiCamSFM::~MultiCamSFM()
	{
	}
}