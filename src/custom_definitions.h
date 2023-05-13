#ifndef CUSTOM_DEFINITIONS_H
#define CUSTOM_DEFINITIONS_H
#include <pyclustering/definitions.hpp>
using namespace std;
using pattern_float           = vector<float>;

using pattern_ptr_float       = shared_ptr<pattern_float>;

using pointf                  = vector<float>;

using pointf_ptr              = shared_ptr<float>;

using pointset                = vector<pointf>;

using pointsetset             =vector<pointset>;

using pointset_ptr            = shared_ptr<pointset>;

using stringvec               = vector<string>;

using stringset               =vector<stringvec>;
#endif
