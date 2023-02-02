#pragma once
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <list>
#include <stdbool.h>
#include <algorithm>
#include <vector>
///Definicje Funkcji
typedef std::map<std::string, std::set<std::pair<std::string, double>>>Graf;
Graf Get_graph(const std::string& Graph);

std::vector<std::string>All_vertices(const Graf& graph);

std::vector<std::string> get_vertices(const std::string& Vertices);

std::map<std::string, double> Dijkstra(const Graf& graph, std::string node,
	std::map<std::string, std::string>& last_step);

std::vector<std::vector<std::string>>step_by_step(std::map<std::string, double>& result, std::map<std::string, std::string>& last_step,
	std::string start_node);