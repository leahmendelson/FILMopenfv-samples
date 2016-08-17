#include "openfv.h"

using namespace cv;
using namespace std;

DEFINE_bool(live, false, "live refocusing");
DEFINE_bool(fhelp, false, "show config file options");

DEFINE_bool(dump_stack, false, "dump stack");
DEFINE_string(save_path, "", "stack save path");
DEFINE_string(config_file, "/home/ab9/projects/hf_data/config.cfg", "config file");
DEFINE_string(filename, "", "name of file to save image to");
DEFINE_double(zmin, 0, "zmin");
DEFINE_double(zmax, 100, "zmax");
DEFINE_double(dz, 0.1, "dz");
DEFINE_double(thresh, 0, "thresholding level");

int main(int argc, char** argv) {

    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr=1;

    refocus_settings settings;
    parse_refocus_settings(FLAGS_config_file, settings, FLAGS_fhelp);

    double t1, t2, t3, t4;
    vector<Mat> stack1, stack2, stack3, stack4;

    settings.use_gpu = 1;
    settings.hf_method = 1;
    {
        saRefocus refocus(settings);
        refocus.return_stack(FLAGS_zmin, FLAGS_zmax, FLAGS_dz, FLAGS_thresh, 0, stack1, t1);
    }

    settings.use_gpu = 0;
    settings.hf_method = 1;
    {
        saRefocus refocus(settings);
        refocus.return_stack(0, 0.9, FLAGS_dz, FLAGS_thresh, 0, stack2, t2);
    }

    settings.use_gpu = 1;
    settings.hf_method = 0;
    {
        saRefocus refocus(settings);    
        refocus.return_stack(0, 0.9, FLAGS_dz, FLAGS_thresh, 0, stack3, t3);
    }

    settings.use_gpu = 0;
    settings.hf_method = 0;
    {
        saRefocus refocus(settings);
        refocus.return_stack(0, 0.01, FLAGS_dz, FLAGS_thresh, 0, stack4, t4);
    }

    LOG(INFO)<<"\t\t\t"<<"Original Method"<<"\t"<<"HF Method";
    LOG(INFO)<<"CPU only:"<<"\t\t"<<(t4*1000/60)<<" mins"<<"\t"<<t2*100<<" s";
    LOG(INFO)<<"CPU + GPU:"<<"\t"<<(t3*100)<<" s"<<"\t"<<t1<<" s";

    vector<int> params;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(100);
    imwrite(FLAGS_filename, stack4[0], params);

    // ProfilerStart("bench.prof");    

    // ProfilerStop();

    return 0;

}
