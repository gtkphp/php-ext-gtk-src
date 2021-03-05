# TODO

This file show all technical debt.
By continuously improving the design of code, we make it easier and easier to work with.

## Priority
Implemente g_hash_table, g_hash_table_iter, g_hash_func/g_equal_func
Compatibility PHP5 -> PHP8

// maybe is better to Z_ADDREF_P();
zval *val = emalloc(sizeof(zval));
ZVAL_COPY(val, data);
// efree();

create config.nice


## Refactoring
- Readability
- Code smell
- Code pooling
- Reduced complexity
- Performance
- Algoritme
- Less memory

## Design Pattern
- SOLID
- GANG4
- Injection

## Namaing
- standardized
- concise, well-named, single-purpose methods.

## Architecture 

- Server-Cache
- Client-Cache
- Seperate responsability

## Bugs
Potential bugs

## Vulnerabilities 
Potential hacks


## Testing
Add tests
- Unit
- Fonctional




