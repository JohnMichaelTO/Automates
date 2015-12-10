#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

typedef enum s_type
{
    R = 0, I = 1, IT = 2, T = 3, V = 4
} t_type;

// Fonction de d�coupe d'une cha�ne en un tableau par le biais d'un d�limiteur
std::vector<std::string> cut(const std::string &chaine, const std::string &delimiteur);

#endif // STRUCTURES_H
