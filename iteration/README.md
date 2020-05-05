# Iterate over a Range of things

## Range 

see cxxFP/range

## Roll my own iterator 

there are various examples:

```text
cxxTemplate/conditional/conditional_t.cpp
custom_iterator*
```

see also: master c++ stl P/29

the common pattern is:

- define the container template;

- define the iterator template which is a friend of the container;

- define those 5 necessary iterator traits;

## Save time when rolling my own iterator

take a look at boost iterator facade (not the same as the deprecated std::iterator base class!)

mentioned in master c++ stl P/33

see iterator_facade.cpp
