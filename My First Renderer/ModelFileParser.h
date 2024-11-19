#ifndef MODELFILEPARSER_H
#define MODELFILEPARSER_H

#include <string>
#include <vector>

class ModelFileParser {
    public:
        virtual ~ModelFileParser() = default;
        virtual void parse(const char* objectPath) = 0;
        virtual std::vector<float> getVertexData() = 0;
        virtual std::vector<int> getIndices() = 0;
};


#endif