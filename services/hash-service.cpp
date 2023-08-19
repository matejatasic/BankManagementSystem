#include <cmath>
#include "hash-service.h"

using namespace std;

HashService::HashService() {};

int HashService::hash (string text) {
    int result = 0;

    for(size_t i = 0; i < text.length(); ++i) {
        result += text[i] * pow(31, i);
    }

    return result;
}