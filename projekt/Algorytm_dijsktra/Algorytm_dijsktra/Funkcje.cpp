#include "Funkcje.h"

typedef std::map<std::string, std::set<std::pair<std::string, double>>>Graf;
Graf Get_graph(const std::string& Graph) {
	Graf graph;
	std::ifstream in(Graph);
	if (in) {
		std::string line;
		while (std::getline(in, line)) {///zapomoca getline zczytuje z kazdej linii i przy pomocy istringstream przypisuje do odpowiednich zmiennych
			std::replace(line.begin(), line.end(), ':', ' ');
			std::istringstream ss(line);
			std::string start_vertex, end_vertex, sign;
			double weight;
			if (!(ss >> start_vertex))continue;
			if (!(ss >> sign))continue;///sign wskazuje czy polaczenie jest skierowane czy dziala w dwie strony
			if (!(ss >> end_vertex))continue;
			if (!(ss >> weight))continue;
			
			if (sign == "-") {///polaczenie nieskierowane
				graph[start_vertex].insert({ end_vertex,weight });
				graph[end_vertex].insert({ start_vertex,weight });
			}
			if (sign == "->") {///polaczenie 
				graph[start_vertex].insert({ end_vertex, weight });
			}
		}
		in.close();
	}
	return graph;
}
std::vector<std::string>All_vertices(const Graf& graph) {///pozyskanie wszystkich wierzcholkow 
	std::vector<std::string>all_vertices;
	///zmienna bierze kazdy wierzcholek z grafu i dodaje go do vektora all_vertices(potrzebne do
	///stwierdzenia czy podany wierzcholek znajduje sie w Grafie - za pomoc  operatora ->
	for (auto i = graph.begin(); i != graph.end(); i++) {
		std::string key = i->first;
		all_vertices.push_back(key);
	}
	return all_vertices;
}

///funkcja wstawiajaca do vektora first_vertices wierzcholki startowe z pliku tekstowego Vertices.txt
std::vector<std::string> get_vertices(const std::string& Vertices) {
	std::vector<std::string> first_vertices;
	std::ifstream w(Vertices);
	if (w) {
		std::string one_less;
		while (std::getline(w, one_less)) {	
			first_vertices.push_back(one_less);
		}
		w.close();
	}
	return first_vertices;
}
///Dijkstra
std::map<std::string, double> Dijkstra(const Graf& graph, std::string node,
	std::map<std::string, std::string>& last_step) {
	std::map<std::string, double>result;///mapa result przechowuje najkrotsze odleglosci od startowego wierzcholka do kazdego innego
	std::set<std::string>visited;///visited - wierzcholki odwiedzone ale jeszcze nie przeanalizowane
	for (const auto& el : graph) {
		///dla kazdego wierzcholka ustawiam odleglosc na nieskonczonosc z wyjatkiem node czyli tego w ktorym jestesmy
		result[el.first] = std::numeric_limits<double>::infinity();
	}
	if (graph.find(node) == graph.end())return result;
	result[node] = 0.0;
	while (true) {
		for (const auto& el : graph.at(node)) {
			///porownanie odleglosci od wierzcholka w ktorym sie znajdujemy(node)
			if (result[el.first] > result[node] + el.second) {
				result[el.first] = result[node] + el.second;
				visited.insert(el.first);
				///mapa last_step przechowuje dla kazdego wierzch. ostatni odwiedzony wierzch - potrzebne do odzyskania sciezki
				last_step[el.first] = node;
			}
		}
		visited.erase(node);
		if (visited.empty())break;
		/// ustawia node(wlasnie analizowany wierzcholek) na najblizszego sasiada wierzcholka w ktorym jestesmy(node)
		node = *std::min_element(visited.begin(), visited.end(),
			[&result](const auto& l, const auto& r) {return result[l] < result[r]; });
	}
	return result;
}
///Przywracanie sciezki
std::vector<std::vector<std::string>>step_by_step(std::map<std::string, double>& result, std::map<std::string, std::string>& last_step,
	std::string start_node) {
	///zmienna path bedzie tablica string w odwiedzonych podczas funkcji Dijkstra
	std::vector<std::string>path;
	std::vector<std::vector<std::string>>paths;
	std::vector<std::string>result_ki;
	///dla kazdego wierzcholka z Dijkstry
	for (auto i = result.begin(); i != result.end(); i++) {
		std::string ki = i->first;
		result_ki.push_back(ki);
	}
	///current_vertex - na ostatni wierzcholek odwiedzony w Dijkstrze
	for (const auto& s : result_ki) {
		std::string current_vertex = s;///wez ostatni wierzcholek odwiedzony w result i dla niego
		while (current_vertex != start_node) {
			path.push_back(current_vertex);
			current_vertex = last_step.at(current_vertex);
		}
		///odwracam tablice path tak aby wskazywala droge od pierwszego do ostatniego, a nie na odwrot
		if (size(path) > 0) {
			std::reverse(path.begin(), path.end());
			///dodaje do vektora paths vektor path
			paths.push_back(path);
			path.clear();
		}
	}
	return paths;
}
