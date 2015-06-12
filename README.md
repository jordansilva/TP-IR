# Information Retrieval Project
This is a very cheap and basic search engine, which has a indexer and boolean query processor.
Language: C++11

---
## Compilation

```bash
cmake -G "Unix Makefiles"
make
```

## Execution

```bash
./bin/index <directory> <index>
./bin/searcher -vsm -at -pr minha consulta aqui
./bin/server
```

## Methods
* ./indexer <directory> <index> - initializes the index
* ./searcher [-vsm|-at|-pr] <query> - search a query (need run indexer first) 
* ./server - initializes the web-server at port 8080

