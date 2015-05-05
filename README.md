# Information Retrieval Project @ Assignment 1
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
./bin/ir
```

## Methods
* index \<directory\> \<index\> [output] - initializes the index
* search [directory] [inverted-index] [vocabulary] [documents] - initializes the search program

