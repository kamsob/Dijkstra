#include "Funkcje.h"

int main(int argc, char* argv[])
{
	///tutaj do lini polecen tak zeby po - g czyta o plik z grafem, po - w plik z wierzcholkami i po - o tworzy o plik z wynikami
	///np. Algorytm_dijkstra -g Graf.txt -w Vertices.txt -o Result.txt
	std::string Graph, Vertices, Results;
	for (int i = 0; i < argc; i++) {
		std::string a = argv[i];
		if (a == "-g") {
			Graph = argv[i + 1];
			i++;
		}
		if (a == "-w") {
			Vertices = argv[i + 1];
			i++;
		}
		if (a == "-o") {
			Results = argv[i + 1];
			i++;
		}
	}
	auto graph = Get_graph(Graph);///Graf - plik wejsciowy
	auto first_vertices = get_vertices(Vertices);///Wierzcholki startowe - plik wejsciowy
	std::string end_node;
	std::map<std::string, std::string> last_step;///mapa przechowujaca ostatni odwiedzony wierzcholek dla kazdego wierzcholka
	auto all_vertices = All_vertices(graph);///tablica przechowujaca wszystkie wierzcholki
	std::ofstream results(Results);///wyniki - plik wyjsciowy
	results << "W tym pliku zostaną zapisane najkrótsze trasy do pozostałych wierzchołków z punktów podanych w pliku: Vertices.txt" << std::endl;
	results << "jeśli danego wierzchołka nie ma w grafie zostanie przekazany komunikat o tym" << std::endl;
	///dla kazdego wierzcholka startowego
	for (const auto& v : first_vertices) {
		///warunek jesli wierzcholka v nie ma w grafie
		///bierze vektor all_vertices i sprawdza czy jest w nim v
		if (std::find(all_vertices.begin(), all_vertices.end(), v) == all_vertices.end()) {
			results << "Brak wierzcholka " << v << " w grafie" << std::endl;
			continue;
		};
		results << "najkrotsze ścieżki dla wierzchołka  " << v << " :  " << std::endl;
		auto result = Dijkstra(graph, v, last_step);
		auto paths = step_by_step(result, last_step, v);
		for (const auto& o : paths) {
			results << v;
			for (const auto& t : o) {
				results << "-> " << t;
			}
			///results dla ostatniego wierzcholka z vektora path
			results << " : " << result[o.back()]<<std::endl;
		}
	}

}


