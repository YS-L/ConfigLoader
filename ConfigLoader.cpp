#include <cctype>
#include <algorithm>
#include <utility>

#include "ConfigLoader.h"

using namespace std;

#define MAX_BUF_SIZE 10000
#define CONFIG_LOADER_VERBOSE 0

ConfigLoader::ConfigLoader(const std::string& ConfigFileName): mParsed(false)
{
	ifstream fin(ConfigFileName.c_str());
	if(!fin.good()){
		throw FileError();
	}
	take_content_snapshot(fin);
}

ConfigLoader::ConfigLoader(const std::ifstream& FileInStream): mParsed(false)
{
	take_content_snapshot(FileInStream);
}

void ConfigLoader::take_content_snapshot(const std::istream& input)
{
	ostringstream oss;
	oss << input.rdbuf();
	mContent = oss.str();
}

void ConfigLoader::parse()
{
	istringstream iss(mContent);
	char line_buf[MAX_BUF_SIZE];	
	while(iss.getline(line_buf, MAX_BUF_SIZE)){
		string line(line_buf);
#if CONFIG_LOADER_VERBOSE
		cout << "Processing line: " << line << endl;
#endif
		size_t comment_pos = line.find('#');
		if(comment_pos == 0){
#if CONFIG_LOADER_VERBOSE
			cout << "Ignoring comment line: " << line << endl;
#endif
			continue;
		}
		if(comment_pos != string::npos){
			line.resize(comment_pos);
#if CONFIG_LOADER_VERBOSE
			cout << "Stripped comments: " << line << endl;
#endif
		}
		line = line.substr(0, comment_pos);
		size_t eq_pos = line.find('=');
		if(eq_pos == string::npos){
#if CONFIG_LOADER_VERBOSE
			cout << "Skipping invalid line: " << line << endl;
#endif
			continue;
		}
#if CONFIG_LOADER_VERBOSE
		cout << "After stripping comments: " << line << endl;
#endif
		string key = line.substr(0, eq_pos);
		string value = line.substr(eq_pos + 1, string::npos);
		// Strip off whitespace for keys and values
		// TODO: Let value have spaces, strip off only trailing and leading spaces.
		key.erase(remove_if(key.begin(), key.end(), ::isspace), key.end());
		value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
#if CONFIG_LOADER_VERBOSE
		cout << "Extracted key = " << key << ", value = " << value << endl;
#endif

		if(key.size() == 0){
			cout << "Ignoring orphaned value: " << value << endl;
			continue;
		}
		if(value.size() == 0){
			cout << "Ignoring invalid value for key [" << key << "]!" << endl;
			continue;
		}

		mVarMap.insert(make_pair(key, value));
	}
	mParsed = true;
}
