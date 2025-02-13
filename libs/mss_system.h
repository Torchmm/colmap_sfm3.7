#pragma once
#include "colmap/controllers/automatic_reconstruction.h"

namespace colmap
{
	class MultiCamSFM
	{
	public:
		MultiCamSFM(const std::string log_dir);
		~MultiCamSFM();

		bool SetCameraCalibrationFile(const std::string& cam_front);
		bool SetImageDir(const std::string& dir1);
		void SetSkipNum(const int skipNum);
		bool SetWorkSpaceDirectory(const std::string work_space);
		void Run();
		std::string GetMSSVersion();
	private:

		std::shared_ptr<AutomaticReconstructionController> auto_recon_controller_;
		AutomaticReconstructionController::Options options_;
	};
}


