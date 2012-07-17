
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

double test(float* instance);

void clearinstance(float* instance, int numfeatures) {
    for (int f=0; f<numfeatures; f++)
        instance[f] = 0.f;
}

bool parseFeatureValue(string &cfeature, string &cvalue) {
    // get token
    char* tok;
    if (not (tok = strtok(NULL, " \n"))) // line stored in state from previous call to strtok
        return false;
    
    // tok is feature:value
	string bit = tok;
	int colon_index = bit.find(":");
	cfeature = bit.substr(0, colon_index);
	cvalue = bit.substr(colon_index+1,bit.length()-colon_index-1);
	
    return true;
}

bool readinstance(int numfeatures, float* instance) {
    // get line from stdin
    string strline;
	getline(cin, strline);
	char* line = strdup(strline.c_str());

	// extract and ignore label (first item)
	strtok(line, " ");

	// get qid, if present, and ignore
	string cfeature, cvalue;
    string qidstr ("qid");
    if (not parseFeatureValue(cfeature, cvalue)) return true;
    if (qidstr.compare(cfeature)) // qid is present
        if (not parseFeatureValue(cfeature, cvalue)) return true;
	
	// get feature values
    int feature = -1;
    float value = -1.f;
	do {
	    // parse and check feature index
	    feature = atoi(cfeature.c_str());
        if (feature < 0) return false;  // obviously invalid
        if (feature >= numfeatures) return true;
            // could be invalid, but most likely the trees found no use for features >= numfeatures
            // and we can skip the remaining feature values for this instance since they are expected
            // to be listed in ascending order by feature index
        
        // store feature value
		value = (float) atof(cvalue.c_str());
        instance[feature] = value;
    } while (parseFeatureValue(cfeature, cvalue));

	// clean up
	free(line);
	
	// return
    return true;
}

void driver(int numfeatures) {
    // variables
    float* instance = new float[numfeatures];
    clearinstance(instance, numfeatures);
    
	// evaluate all data instances
	while (readinstance(numfeatures, instance) and not cin.eof()) {
        // test instance
        double result = test(instance);
        
        // print result
        printf("%f\n", result);
        clearinstance(instance, numfeatures);
    }
}
double tree_0(float* instance) {if (instance[12] < 0.500000) {if (instance[1] < 0.500000) {if (instance[2] < 0.500000) {return 0.000000;} else {if (instance[2] < 1.500000) {return 0.000000;} else {return 0.000000;}}} else {if (instance[2] < 1.500000) {if (instance[6] < 0.500000) {return 0.000291;} else {return 0.000682;}} else {if (instance[1] < 1.500000) {return 0.000000;} else {return 0.000000;}}}} else {if (instance[10] < 2.500000) {if (instance[7] < 0.500000) {if (instance[10] < 0.500000) {return 0.001333;} else {return 0.000455;}} else {if (instance[1] < 3.500000) {return 0.002143;} else {return 0.000556;}}} else {if (instance[5] < 0.500000) {if (instance[11] < 0.500000) {return 0.005000;} else {return 0.000000;}} else {if (instance[1] < 0.500000) {return 0.000000;} else {return 0.000000;}}}}}
double test(float* instance) {
	double pred = 0.f;
	pred += tree_0(instance);
	return pred;
}
int main(int argc, char* argv[]) { driver(12); }
