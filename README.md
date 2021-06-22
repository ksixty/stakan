# STAKAN

STAKAN interprets a Forth-like language. Uses a somewhat heavy `long double` stack.

## Goals

I am writing STAKAN to:
* learn principles of concatenative languages
* implement something real in C (previously I tried to make a Lisp in C and that didn't go quite well)
* understand how compilers work
* have some fun during the summer

## Progress

[X] Read words
[X] Parse words into tokens
[X] Evaluate words
[X] Implement some primeops
[X] Implement `:` and `;`
[ ] Implement `branch` and `branch?`
[ ] Implement `if`, `then`, `else`
[ ] Implement the `until` loop
[ ] Implement all Forth primitives
[ ] Write a useful standard library (maybe, some web server stuff)
[ ] Get the code reviewed by someone who is proficient in C
[ ] ...

## Custom words

You can define your own words both in run-time or at compile-time.

Run-time words are defined in STAKAN itself by using `: (...) ;` construction:
```forth
: double 2 * ;
: quad double double ;
```

Compile-time native words are defined in C language using convenience macros defined in [`nwords.h`](tree/master/src/nwords.h):
```c
NWORD(double) {
  PUSH(2);
  MUL();
}

NWORD(quad) {
  DOUBLE();
  DOUBLE();
}
```

## Try it out

To compile and run:

```git clone https://github.com/ksixty/stakan && cd stakan && make run```
