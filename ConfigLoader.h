#ifndef __INCLUDED_ConfigLoader_H
#define __INCLUDED_ConfigLoader_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
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
		T getVal(const std::string& key)
		{
			if(!mParsed){
				parse();
			}
			container_iter it = mVarMap.find(key);
			if(it == mVarMap.end()){
				throw KeyError();
			}
			std::istringstream iss(it->second);
			T val;
			iss >> val;
			return val;
		};

		/// Read the value associated with key, if key not found return default_val
		template<class T>
		T getVal(T default_val, const std::string& key)
		{
			try{
				return getVal<T>(key);
			}
			catch(KeyError){
				return default_val;
			}
		};

		/// Read the values associated with key as a vector
		template<class T>
		std::vector<T> getVector(const std::string& key)
		{
			if(!mParsed){
				parse();
			}
			container_iter it = mVarMap.find(key);
			if(it == mVarMap.end()){
				throw KeyError();
			}
			std::istringstream iss(it->second);
			std::vector<T> vec;
			T val;
			while(iss >> val){
				vec.push_back(val);
			}
			return vec;
		};

		/// Read strings with spaces
		std::string getString(const std::string& key)
		{	
			if(!mParsed){
				parse();
			}
			container_iter it = mVarMap.find(key);
			if(it == mVarMap.end()){
				throw KeyError();
			}
			return it->second;
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
		typedef std::map<std::string, std::string> container_type;
		typedef container_type::iterator container_iter;

		void take_content_snapshot(const std::istream& input);
		std::string strip_head_tail(const std::string& str);

		std::string mContent;
		container_type mVarMap;
		bool mParsed;
};

#endif
