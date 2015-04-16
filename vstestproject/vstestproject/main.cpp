#include <stdio.h>
#include "caffe\caffe.hpp"
#include "caffe\blob.hpp"

using namespace caffe;

int main(int argc, const char* argv[])
{
	Caffe::set_mode(Caffe::Brew::CPU);
	int device_id = 0;
	Caffe::SetDevice(device_id);
	LOG(ERROR) << "Using GPU #" << device_id;

	std::string deploy_file = "C:\\Users\\Philipp\\Documents\\git\\caffe-brewer\\caffe-framework\\models\\bvlc_reference_caffenet\\deploy.prototxt";
	std::string model_file = "C:\\Users\\Philipp\\Documents\\git\\caffe-brewer\\caffe-framework\\models\\bvlc_reference_caffenet\\bvlc_reference_caffenet.caffemodel";


	Net<float> test_net(deploy_file, Phase::TEST);
	test_net.CopyTrainedLayersFrom(model_file);
	
	double test_accuracy = 0;

	const vector<Blob<float>*> &result = test_net.ForwardPrefilled();
	test_accuracy += result[0]->cpu_data()[0];

	LOG(ERROR) << "Batch " << 0 << ", accuracy: " << result[0]->cpu_data()[0];

	getchar();
	return 0;
}