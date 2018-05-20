Ismail Kheir
Assignment 5 README

Which Parts were completed?
-All parts of the assignment were completed and output is largely consistent
with examples given in the assignment pdf.

Any bugs you encountered?
-I had many bugs before I used a Graph struct to contain the vertex structs
I had created for every vertex. After creating the graph class to contain
the vertices the project was much more straight forward. I did however
get slightly different output for topological sorting when running this
input -./TopologicalSort Graph3.txt. Other than that, I did not pick up
on any other bugs.

To Run the programs:
-Use make all and the commands to compile will run sequentially
	for part 1
	./CreateAndTestGraph <graph_file.txt> <query_file.txt>
	for part 2
	./FindPaths <graph_file.txt> <start_vertex id>
	for part 3
	./TopologicalSort <graph_file.txt>

Input Files
-input files are included with the folder
	Query files:
	AdjacencyQueries1.txt
	AdjacencyQueries2.txt
	Graph1.txt
	Graph2.txt
	Graph3.txt
