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

	//get datum
	Datum datum;
	if (!ReadImageToDatum("C:\\Users\\Philipp\\Documents\\git\\caffe-brewer\\vstestproject\\x64\\Debug\\cat.jpg", 1, 227, 227, &datum)) {
		LOG(ERROR) << "Error during file reading";
	}

	// get the blob
	Blob<float>* blob = new Blob<float>(1, datum.channels(), datum.height(), datum.width());

	// get the blobproto
	BlobProto blob_proto;
	blob_proto.set_num(1);
	blob_proto.set_channels(datum.channels());
	blob_proto.set_height(datum.height());
	blob_proto.set_width(datum.width());
	const int data_size = datum.channels() * datum.height() * datum.width();
	int size_in_datum = std::max<int>(datum.data().size(),
		datum.float_data_size());
	for (int i = 0; i < size_in_datum; ++i) {
		blob_proto.add_data(0.);
	}
	const string& data = datum.data();
	if (data.size() != 0) {
		for (int i = 0; i < size_in_datum; ++i) {
			blob_proto.set_data(i, blob_proto.data(i) + (uint8_t)data[i]);
		}
	}

	// set data into blob
	blob->FromProto(blob_proto);

	// fill the vector
	vector<Blob<float>*> bottom;
	bottom.push_back(blob);
	float type = 0.0;

	const vector<Blob<float>*>& result = test_net.Forward(bottom, &type);

	// Here I can use the argmax layer, but for now I do a simple for :)
	float max = 0;
	float max_i = 0;
	for (int i = 0; i < 1000; ++i) {
		float value = result[0]->cpu_data()[i];
		if (max < value)
		{
			max = value;
			max_i = i;
		}
	}

	LOG(ERROR) << "max: " << max << " i " << max_i;

	getchar();
	return 0;
}