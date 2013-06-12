#ifndef __INCLUDED_ConfigLoader_H
#define __INCLUDED_ConfigLoader_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <exception>

/*
 * A minimalistic configuration / parameter reader.
 *
 */

class ConfigLoader
{
public:
		ConfigLoader(const std::string& ConfigFileName);
		ConfigLoader(const std::ifstream& FileInStream);
		void parse();

		/// Read the value associated with key
		template<class T>
		T getVal(std::string key)
		{
			if(!mParsed){
				parse();
			}
			std::map<std::string, std::string>::iterator it = mVarMap.find(key);
			if(it == mVarMap.end()){
				throw KeyError();
			}
			std::string var_str = it->second;
			std::ostringstream oss;
			oss << var_str;
			std::istringstream iss(oss.str());
			T val;
			iss >> val;
			return val;
		};

		/// Read the value associated with key, if key not found return default_val
		template<class T>
		T getVal(T default_val, std::string key)
		{
			try{
				return getVal<T>(key);
			}
			catch(KeyError){
				return default_val;
			}
		};

		class KeyError: public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Invalid key.";
			}
		};

		class ValueError: public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Invalid value.";
			}
		};

		class FileError: public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Invalid file.";
			}
		};

private:
		void take_content_snapshot(const std::istream& input);
		std::string mContent;
		std::map<std::string, std::string> mVarMap;
		bool mParsed;
};

#endif
