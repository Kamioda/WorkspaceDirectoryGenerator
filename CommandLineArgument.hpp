#if !defined COMMAND_LINE_ARGUMENT_HPP
#define COMMAND_LINE_ARGUMENT_HPP
#include "ConverterClass.hpp"
#include <algorithm>
#include <string>
#include <vector>
 
class CommandLineArgument {
private:
    std::vector<std::string> Args;
    static std::vector<std::string> atov(char* arr[]) {
        std::vector<std::string> vec;
        for (char** it = arr; *it != nullptr; ++it) vec.push_back(*it);
        return vec;
    }
public:
    CommandLineArgument(char* argv[]) : Args(atov(argv)) {}
    template<typename ParameterType, ConverterClass<ParameterType> Converter>
    ParameterType get(const std::string& Key) const {
        return this->get<ParameterType, Converter>(std::make_pair("--" + Key, ""));
    }
    template<typename ParameterType, ConverterClass<ParameterType> Converter>
    ParameterType get(const std::string& Key, const std::string& Alias) const {
        return this->get<ParameterType, Converter>(std::make_pair("--" + Key, "-" + Alias));
    }
private:
    std::vector<std::string>::const_iterator find(const std::string& Key) const {
		return std::find(this->Args.begin(), this->Args.end(), Key);
	}
    template<typename ParameterType, ConverterClass<ParameterType> Converter>
    ParameterType get(const std::pair<std::string, std::string>& KeyAndAlias) const {
        const auto KeyIt = this->find(KeyAndAlias.first);
        if (KeyIt >= this->Args.end() - 1) {
            if (KeyAndAlias.second.empty()) return {};
            const auto AliasIt = this->find(KeyAndAlias.second);
            if (this->find(KeyAndAlias.second) >= this->Args.end() - 1) return {};
            return Converter()(*(AliasIt + 1));
        }
        return Converter()(*(KeyIt + 1));
	}
public:
    bool exists(const std::string& Key) const {
		return this->exists(std::make_pair("--" + Key, ""));
	}
    bool exists(const std::string& Key, const std::string& Alias) const {
        return this->exists(std::make_pair("--" + Key, "-" + Alias));
    }
private:
    bool exists(const std::pair<std::string, std::string>& KeyAndAlias) const {
        return this->find(KeyAndAlias.first) != this->Args.end() || this->find(KeyAndAlias.second) != this->Args.end();
	}
};
#endif
